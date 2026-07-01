"""
TrajectoryPlotterNode
=====================
Subscribes to /display_planned_path (moveit_msgs/DisplayTrajectory), i.e. the
trajectory PLANNED by MoveIt (Pilz PTP/LIN/CIRC, or any other pipeline).

Unlike joint_monitor_node (which watches the EXECUTED motion on /joint_states
and differentiates position), this node reads the velocities AND accelerations
that the planner itself computed: each JointTrajectoryPoint already carries
``velocities[j]``, ``accelerations[j]`` and ``time_from_start``. No
differentiation needed for the joint quantities.

For every received plan it produces one figure. The joints are plotted with ONE
ROW PER JOINT and TWO COLUMNS:
  * left column  : joint velocity     vs time, with +/- max_velocity lines
  * right column : joint acceleration vs time, with +/- max_acceleration lines
Limit lines come from ``joint_limits.yaml``.

If a URDF is provided (via ~robot_description) the node also computes, by
FORWARD KINEMATICS on each trajectory point, the Cartesian TCP position of the
~tcp_link frame, then numerically differentiates it along the trajectory's own
(non-uniform) time axis to obtain:
  * TCP Cartesian speed        ‖dp/dt‖   [m/s]
  * TCP Cartesian acceleration ‖d²p/dt²‖ [m/s²]
These are shown on an EXTRA BOTTOM ROW (speed left, acceleration right) with NO
limit lines. FK uses pinocchio; if pinocchio or the URDF is unavailable the TCP
row is simply omitted and the joint plots are produced as usual.

If a joint exceeds a limit the node logs a warning and highlights the subplot.

Parameters:
  ~display_topic      (str)  topic to listen on   [/display_planned_path]
  ~joint_limits_file  (str)  path to joint_limits.yaml. If empty, the plot is
                             produced without limit lines.
  ~robot_description  (str)  URDF XML string. If empty, the node instead
                             listens on the /robot_description topic (latched by
                             RViz/MoveIt) to obtain the URDF automatically. If
                             neither is available, the TCP row is omitted.
  ~tcp_link           (str)  URDF link to track for the TCP  [tool_link]
  ~output_dir         (str)  where PNGs are written
  ~live               (bool) open a window that updates on every plan (needs
                             a display: WSLg or an X server). The PNG is still
                             written. ~show is kept as a deprecated alias.
  ~accumulate         (bool) when true (default), every received plan is
                             appended to ONE continuous timeline and a single
                             PNG is rewritten on each plan. Call ~/reset to
                             start a fresh image. When false, one timestamped
                             PNG is written per plan.

Services:
  ~/reset  (std_srvs/Trigger)  clear the accumulated timeline and start over.
"""

import os
from datetime import datetime

import numpy as np
import yaml
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSReliabilityPolicy, QoSHistoryPolicy
from moveit_msgs.msg import DisplayTrajectory
from std_msgs.msg import String
from std_srvs.srv import Trigger

# Use a headless backend by default so the node works over SSH / WSL without
# an X display. Switched to an interactive backend only if ~show is true.
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt  # noqa: E402


def _find_joint_limits_block(data):
    """Locate the 'joint_limits' mapping inside a parsed YAML tree.

    Handles both the flat MoveIt Setup Assistant layout (joint_limits at the
    root, e.g. Staubli) and the nested ros__parameters layout used by the
    DENSO configs (move_group/ros__parameters/robot_description_planning/
    joint_limits). Returns the first 'joint_limits' dict found, or {}.
    """
    if not isinstance(data, dict):
        return {}
    if isinstance(data.get('joint_limits'), dict):
        return data['joint_limits']
    for value in data.values():
        found = _find_joint_limits_block(value)
        if found:
            return found
    return {}


def _load_limits(path: str, logger):
    """Return (velocity_limits, acceleration_limits) from a joint_limits.yaml.

    Each is a {joint_name: max_value} dict. Joints whose corresponding
    has_*_limits flag is false (or that lack the max_* key) are skipped.
    """
    if not path:
        return {}, {}
    if not os.path.isfile(path):
        logger.warn(f'joint_limits_file not found: {path} (plotting without limits)')
        return {}, {}

    with open(path, 'r') as f:
        data = yaml.safe_load(f) or {}

    vel_limits = {}
    acc_limits = {}
    for name, props in _find_joint_limits_block(data).items():
        if not isinstance(props, dict):
            continue
        if props.get('has_velocity_limits', False) and 'max_velocity' in props:
            vel_limits[name] = float(props['max_velocity'])
        if props.get('has_acceleration_limits', False) and 'max_acceleration' in props:
            acc_limits[name] = float(props['max_acceleration'])
    return vel_limits, acc_limits


class _TcpKinematics:
    """Forward kinematics for the TCP link, backed by pinocchio.

    Builds a pinocchio model from a URDF XML string and exposes tcp_positions()
    which maps a matrix of joint configurations to the 3D positions of the TCP
    frame. Construction raises if pinocchio is missing or the URDF/link is bad;
    the caller catches that and disables the TCP row.
    """

    def __init__(self, urdf_xml: str, tcp_link: str):
        import pinocchio as pin  # imported lazily; may be absent
        self._pin = pin
        self._model = pin.buildModelFromXML(urdf_xml)
        self._data = self._model.createData()
        if not self._model.existFrame(tcp_link):
            frames = [f.name for f in self._model.frames]
            raise ValueError(
                f"TCP link '{tcp_link}' not found in URDF. Available frames: {frames}")
        self._frame_id = self._model.getFrameId(tcp_link)
        # Order of the actuated joints as pinocchio expects them in q.
        self._joint_order = list(self._model.names[1:])  # names[0] == 'universe'

    @property
    def joint_order(self):
        return self._joint_order

    def tcp_positions(self, q_matrix: np.ndarray) -> np.ndarray:
        """q_matrix: (N, nq) configurations -> (N, 3) TCP positions."""
        pin = self._pin
        out = np.empty((q_matrix.shape[0], 3), dtype=float)
        for i in range(q_matrix.shape[0]):
            q = q_matrix[i]
            pin.forwardKinematics(self._model, self._data, q)
            pin.updateFramePlacement(self._model, self._data, self._frame_id)
            out[i] = self._data.oMf[self._frame_id].translation
        return out

    def tcp_linear_velocity(self, q_matrix: np.ndarray,
                            qd_matrix: np.ndarray) -> np.ndarray:
        """Analytic TCP linear velocity: v = J(q)·q̇, world-aligned frame.

        q_matrix, qd_matrix: (N, nv) joint positions/velocities.
        Returns (N, 3) linear velocity of the TCP frame, expressed in the
        LOCAL_WORLD_ALIGNED frame (i.e. world axes at the TCP origin) so it is
        directly comparable to d(world position)/dt. No differentiation, so the
        result is exact — in particular it is exactly zero wherever q̇ is zero
        (start/end of every plan).
        """
        pin = self._pin
        ref = pin.ReferenceFrame.LOCAL_WORLD_ALIGNED
        n = q_matrix.shape[0]
        out = np.empty((n, 3), dtype=float)
        for i in range(n):
            q = q_matrix[i]
            qd = qd_matrix[i]
            J = pin.computeFrameJacobian(self._model, self._data, q,
                                         self._frame_id, ref)   # (6, nv)
            twist = J @ qd                                      # (6,)
            out[i] = twist[:3]                                  # linear part
        return out

    def tcp_linear_kinematics(self, q_matrix: np.ndarray, qd_matrix: np.ndarray,
                              qdd_matrix: np.ndarray):
        """Fully analytic TCP linear velocity AND acceleration.

        q/qd/qdd_matrix: (N, nv) joint positions / velocities / accelerations.

        Returns (vel (N,3), acc (N,3)) linear velocity and linear acceleration
        of the TCP frame, both in the LOCAL_WORLD_ALIGNED frame. The
        acceleration is the CLASSICAL frame acceleration, i.e. it already
        includes the full a = J·q̈ + J̇·q̇ (the J̇·q̇ centripetal/Coriolis term
        is handled internally by pinocchio's forward kinematics), so it matches
        d²(world position)/dt². No numerical differentiation anywhere: both are
        exactly zero wherever q̇ and q̈ are zero (plan endpoints).
        """
        pin = self._pin
        ref = pin.ReferenceFrame.LOCAL_WORLD_ALIGNED
        n = q_matrix.shape[0]
        vel = np.empty((n, 3), dtype=float)
        acc = np.empty((n, 3), dtype=float)
        for i in range(n):
            q = q_matrix[i]
            qd = qd_matrix[i]
            qdd = qdd_matrix[i]
            # Full forward kinematics to 2nd order populates the frame's spatial
            # velocity and (classical) acceleration in data.
            pin.forwardKinematics(self._model, self._data, q, qd, qdd)
            pin.updateFramePlacements(self._model, self._data)
            v = pin.getFrameVelocity(self._model, self._data, self._frame_id, ref)
            a = pin.getFrameClassicalAcceleration(
                self._model, self._data, self._frame_id, ref)
            vel[i] = np.asarray(v.linear).ravel()
            acc[i] = np.asarray(a.linear).ravel()
        return vel, acc


class TrajectoryPlotterNode(Node):
    def __init__(self):
        super().__init__('trajectory_plotter')

        self.declare_parameter('display_topic', '/display_planned_path')
        self.declare_parameter('joint_limits_file', '')
        self.declare_parameter('robot_description', '')
        self.declare_parameter('tcp_link', 'tool_link')
        self.declare_parameter('output_dir', os.path.expanduser('~'))
        self.declare_parameter('show', False)   # deprecated alias of 'live'
        self.declare_parameter('live', False)
        self.declare_parameter('accumulate', True)

        topic = self.get_parameter('display_topic').get_parameter_value().string_value
        limits_file = self.get_parameter('joint_limits_file').get_parameter_value().string_value
        urdf_xml = self.get_parameter('robot_description').get_parameter_value().string_value
        tcp_link = self.get_parameter('tcp_link').get_parameter_value().string_value
        show = self.get_parameter('show').get_parameter_value().bool_value
        self._live = self.get_parameter('live').get_parameter_value().bool_value or show
        self._accumulate = self.get_parameter('accumulate').get_parameter_value().bool_value

        self._vel_limits, self._acc_limits = _load_limits(limits_file, self.get_logger())

        # --- Optional TCP forward kinematics ---------------------------------
        self._tcp = None
        self._tcp_link = tcp_link       # remembered for the topic callback
        if urdf_xml.strip():
            self._build_tcp_kinematics(urdf_xml, source='~robot_description parameter')
        else:
            self.get_logger().info(
                'No ~robot_description parameter — will listen on /robot_description '
                'topic instead (RViz/MoveIt publish it there).')

        # Persistent figure reused by the live window (created lazily).
        self._fig = None
        self._live_axes = None       # 2D array of axes: [n_rows, 2]
        if self._live:
            # Live window needs an interactive backend + a display (WSLg / X).
            matplotlib.use('TkAgg', force=True)
            plt.ion()

        self._plan_count = 0
        self._reset_accumulator()

        self._sub = self.create_subscription(
            DisplayTrajectory, topic, self._on_display_trajectory, 10)
        self.create_service(Trigger, '~/reset', self._srv_reset)

        # Listen for the URDF on /robot_description (latched by RViz/MoveIt via
        # transient-local durability). Only needed if the parameter didn't
        # already give us a working kinematics model. Kept subscribed so a late
        # or updated description is still picked up.
        if self._tcp is None:
            desc_qos = QoSProfile(
                depth=1,
                reliability=QoSReliabilityPolicy.RELIABLE,
                durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
                history=QoSHistoryPolicy.KEEP_LAST,
            )
            self._desc_sub = self.create_subscription(
                String, '/robot_description', self._on_robot_description, desc_qos)

        if self._live:
            # Pump the GUI event loop from the ROS executor thread so the
            # window stays responsive between plans.
            self.create_timer(0.05, self._pump_gui)

        self.get_logger().info(f'TrajectoryPlotter ready — listening on {topic}')
        if self._live:
            self.get_logger().info(
                'Live window ON (needs WSLg/X display) — PNG is still saved too.')
        self.get_logger().info(
            'Accumulate mode ON: every plan is appended to one image '
            '(call ~/reset to start over).'
            if self._accumulate else
            'Accumulate mode OFF: one PNG per plan.')
        if self._vel_limits:
            self.get_logger().info(
                f'Velocity limits loaded for {len(self._vel_limits)} joints: '
                + ', '.join(f'{k}={v:.4g}' for k, v in self._vel_limits.items()))
        else:
            self.get_logger().info(
                'No velocity limits loaded — set ~joint_limits_file to draw limit lines.')
        if self._acc_limits:
            self.get_logger().info(
                f'Acceleration limits loaded for {len(self._acc_limits)} joints: '
                + ', '.join(f'{k}={v:.4g}' for k, v in self._acc_limits.items()))
        else:
            self.get_logger().info(
                'No acceleration limits loaded — set ~joint_limits_file to draw limit lines.')

    def _reset_accumulator(self):
        # joint_name -> {'t': [...], 'v': [...], 'a': [...]} spanning all plans
        self._acc = {}
        self._acc_offset = 0.0       # running time offset for the next plan
        self._acc_boundaries = []    # x position of each plan start (for separators)
        # Per-plan TCP segments (already differentiated within each plan),
        # each shifted to the accumulated timeline: {'t','speed','accel'}.
        self._acc_tcp = []

    def _srv_reset(self, _req, resp):
        self._reset_accumulator()
        self.get_logger().info('Accumulated timeline RESET — next plan starts a fresh image.')
        resp.success = True
        resp.message = 'Accumulator cleared.'
        return resp

    def _build_tcp_kinematics(self, urdf_xml: str, source: str) -> bool:
        """Try to (re)build the TCP kinematics from a URDF string.

        Returns True on success. Used both for the ~robot_description parameter
        and for messages arriving on the /robot_description topic. On failure it
        logs why and leaves self._tcp untouched (so a previous good model, if
        any, keeps working).
        """
        try:
            self._tcp = _TcpKinematics(urdf_xml, self._tcp_link)
            self.get_logger().info(
                f"TCP kinematics ready (from {source}) — "
                f"tracking Cartesian motion of '{self._tcp_link}'.")
            return True
        except ImportError:
            self.get_logger().warn(
                'pinocchio not importable — TCP row disabled. '
                'Install it (e.g. `sudo apt install ros-$ROS_DISTRO-pinocchio` '
                'or `pip install pin`) to plot Cartesian TCP speed/acceleration.')
        except Exception as exc:  # bad URDF, missing link, etc.
            self.get_logger().warn(
                f'Could not build TCP kinematics from {source} ({exc}) — '
                'TCP row disabled.')
        return False

    def _on_robot_description(self, msg: String):
        """Build TCP kinematics from the latched /robot_description topic."""
        if self._tcp is not None:
            return  # already have a working model
        if not msg.data.strip():
            return
        self._build_tcp_kinematics(msg.data, source='/robot_description topic')

    def _on_display_trajectory(self, msg: DisplayTrajectory):
        if not msg.trajectory:
            self.get_logger().warn('Received DisplayTrajectory with no trajectory, ignoring.')
            return

        series, duration = self._extract_series(msg)
        if not series:
            self.get_logger().warn('Trajectory had no joint points, nothing to plot.')
            return

        self._plan_count += 1

        # Compute this plan's TCP kinematics once, differentiated within the
        # plan only (its time axis is local, starting near 0).
        tcp_plan = self._tcp_series_for_plan(series)

        if self._accumulate:
            self._append_to_accumulator(series, duration, tcp_plan)
            plot_series, boundaries, accumulated = self._acc, self._acc_boundaries, True
            tcp = self._accumulated_tcp()
            filename = 'planned_velocity_accumulated.png'
        else:
            plot_series, boundaries, accumulated = series, [], False
            tcp = tcp_plan
            stamp = datetime.now().strftime('%Y%m%d_%H%M%S')
            filename = f'planned_velocity_{self._plan_count:03d}_{stamp}.png'

        self._render(plot_series, boundaries, filename, accumulated, tcp)
        if self._live:
            self._update_live(plot_series, boundaries, accumulated, tcp)

    def _extract_series(self, msg: DisplayTrajectory):
        """Read one plan into {joint: {'t', 'v', 'a', 'p'}} plus its duration.

        'p' (joint position) is stored too so the TCP forward kinematics can be
        computed later. A plan may contain several RobotTrajectory segments
        (e.g. a Pilz MoveGroupSequence); they are concatenated on a continuous
        time axis.
        """
        series = {}
        time_offset = 0.0
        for robot_traj in msg.trajectory:
            jt = robot_traj.joint_trajectory
            if not jt.points:
                continue
            for n in jt.joint_names:
                series.setdefault(n, {'t': [], 'v': [], 'a': [], 'p': []})
            for pt in jt.points:
                t = time_offset + pt.time_from_start.sec + pt.time_from_start.nanosec * 1e-9
                for j, name in enumerate(jt.joint_names):
                    pos = pt.positions[j] if j < len(pt.positions) else 0.0
                    vel = pt.velocities[j] if j < len(pt.velocities) else 0.0
                    acc = pt.accelerations[j] if j < len(pt.accelerations) else 0.0
                    series[name]['t'].append(t)
                    series[name]['p'].append(pos)
                    series[name]['v'].append(vel)
                    series[name]['a'].append(acc)
            last = jt.points[-1].time_from_start
            time_offset += last.sec + last.nanosec * 1e-9
        return series, time_offset

    def _append_to_accumulator(self, series: dict, duration: float, tcp_plan=None):
        """Append one plan to the running timeline, shifted by the offset."""
        self._acc_boundaries.append(self._acc_offset)
        for name, sv in series.items():
            acc = self._acc.setdefault(name, {'t': [], 'v': [], 'a': [], 'p': []})
            acc['t'].extend(self._acc_offset + t for t in sv['t'])
            acc['p'].extend(sv['p'])
            acc['v'].extend(sv['v'])
            acc['a'].extend(sv['a'])
        # Store this plan's TCP segment shifted onto the accumulated timeline.
        # Already differentiated within the plan, so nothing crosses the seam.
        if tcp_plan is not None:
            t_local, speed, accel = tcp_plan
            self._acc_tcp.append({
                't': np.asarray(t_local, dtype=float) + self._acc_offset,
                'speed': np.asarray(speed, dtype=float),
                'accel': np.asarray(accel, dtype=float),
            })
        self._acc_offset += duration

    # ------------------------------------------------------------------ TCP --
    def _tcp_series_for_plan(self, series: dict):
        """Compute TCP (t, speed, accel) for ONE plan, or None if unavailable.

        Both the Cartesian velocity and acceleration are obtained FULLY
        ANALYTICALLY from the joint velocities q̇ and accelerations q̈ the planner
        already provides:
            v = J·q̇
            a = J·q̈ + J̇·q̇   (classical frame acceleration)
        There is NO numerical differentiation anywhere, so both curves are exact
        and are exactly zero wherever q̇ and q̈ are zero (start/end of each plan).
        This removes both the endpoint "jumps" and the sawtooth that a numerical
        derivative over sparse waypoints produced.

        The returned time axis is the plan's own local time; callers shift it by
        the accumulate offset if needed.
        """
        if self._tcp is None or not series:
            return None

        # Use the time axis of any joint (all share the same sample times).
        any_joint = next(iter(series.values()))
        t = np.asarray(any_joint['t'], dtype=float)
        n = t.shape[0]
        if n < 2:
            return None

        order = self._tcp.joint_order
        # Build (N, nv) position/velocity/acceleration matrices, column per
        # joint in pinocchio order. Joints absent from the trajectory default 0.
        q = np.zeros((n, len(order)), dtype=float)
        qd = np.zeros((n, len(order)), dtype=float)
        qdd = np.zeros((n, len(order)), dtype=float)
        for col, jname in enumerate(order):
            sv = series.get(jname)
            if sv is None:
                continue
            p_vals = np.asarray(sv['p'], dtype=float)
            v_vals = np.asarray(sv['v'], dtype=float)
            a_vals = np.asarray(sv['a'], dtype=float)
            if p_vals.shape[0] == n:
                q[:, col] = p_vals
            if v_vals.shape[0] == n:
                qd[:, col] = v_vals
            if a_vals.shape[0] == n:
                qdd[:, col] = a_vals

        try:
            vel_vec, acc_vec = self._tcp.tcp_linear_kinematics(q, qd, qdd)
        except Exception as exc:
            self.get_logger().warn(
                f'TCP analytic kinematics failed ({exc}) — skipping TCP row this plan.')
            return None

        speed = np.linalg.norm(vel_vec, axis=1)              # (N,)
        accel = np.linalg.norm(acc_vec, axis=1)              # (N,)
        return t, speed, accel

    def _accumulated_tcp(self):
        """Concatenate all stored per-plan TCP segments for plotting.

        Segments are already computed per plan (no cross-boundary derivative).
        A single NaN sample is inserted between consecutive segments so
        matplotlib lifts the pen at each plan boundary — no fake connecting
        line, no spurious spike. Returns (t, speed, accel) or None.
        """
        if not self._acc_tcp:
            return None
        ts, ss, accs = [], [], []
        for seg in self._acc_tcp:
            ts.append(seg['t'])
            ss.append(seg['speed'])
            accs.append(seg['accel'])
            # NaN gap so the line breaks between plans.
            ts.append(np.array([np.nan]))
            ss.append(np.array([np.nan]))
            accs.append(np.array([np.nan]))
        t = np.concatenate(ts)
        speed = np.concatenate(ss)
        accel = np.concatenate(accs)
        return t, speed, accel

    # --------------------------------------------------------------- drawing --
    def _draw_one(self, ax, name, t, y, unit, limit, boundaries, kind, color):
        """Draw a single quantity on one axis. Returns a violation tuple or None."""
        ax.cla()
        ax.plot(t, y, color=color, linewidth=1.5, label=kind)
        ax.axhline(0.0, color='gray', linewidth=0.6)

        # Dashed vertical separators between successive plans.
        for b in boundaries[1:]:
            ax.axvline(b, color='gray', linestyle=':', linewidth=0.8)

        violation = None
        if limit is not None:
            ax.axhline(limit, color='red', linestyle='--', linewidth=1.0,
                       label=f'±max ({limit:.4g})')
            ax.axhline(-limit, color='red', linestyle='--', linewidth=1.0)
            peak = max(abs(min(y)), abs(max(y))) if len(y) else 0.0
            if peak > limit + 1e-9:
                violation = (name, peak, limit)
                ax.set_facecolor('#fff0f0')

        ax.set_ylabel(f'{name}\n[{unit}]')
        ax.grid(True, alpha=0.3)
        ax.legend(loc='upper right', fontsize=7)
        return violation

    def _draw_axes(self, fig, axes, names, series, boundaries, accumulated, tcp):
        """Draw all subplots onto a [n_rows, 2] axes grid.

        Rows 0..n_joints-1 : joint velocity (col 0) / acceleration (col 1).
        Last row (if tcp)  : TCP Cartesian speed (col 0) / acceleration (col 1),
                             no limits. Returns (vel_violations, acc_violations).
        """
        vel_violations = []
        acc_violations = []
        for row, name in enumerate(names):
            ax_v = axes[row, 0]
            ax_a = axes[row, 1]
            t = series[name]['t']
            v = series[name]['v']
            a = series[name]['a']

            vviol = self._draw_one(
                ax_v, name, t, v, 'rad/s',
                self._vel_limits.get(name), boundaries,
                'vitesse', 'tab:blue')
            if vviol:
                vel_violations.append(vviol)

            aviol = self._draw_one(
                ax_a, name, t, a, 'rad/s²',
                self._acc_limits.get(name), boundaries,
                'accélération', 'tab:orange')
            if aviol:
                acc_violations.append(aviol)

        # Optional TCP row (no limits).
        if tcp is not None:
            t_tcp, speed, accel = tcp
            r = len(names)
            self._draw_one(
                axes[r, 0], 'TCP', t_tcp, speed, 'm/s',
                None, boundaries, 'vitesse TCP', 'tab:green')
            self._draw_one(
                axes[r, 1], 'TCP', t_tcp, accel, 'm/s²',
                None, boundaries, 'accélération TCP', 'tab:red')

        # Column headers and shared x-labels.
        axes[0, 0].set_title('Vitesses [rad/s]', fontsize=10)
        axes[0, 1].set_title('Accélérations [rad/s²]', fontsize=10)
        axes[-1, 0].set_xlabel('temps [s]')
        axes[-1, 1].set_xlabel('temps [s]')

        title = 'Vitesses et accélérations articulaires planifiées (Pilz / MoveIt)'
        if tcp is not None:
            title += ' + TCP cartésien'
        if accumulated:
            title += f'  —  {len(boundaries)} plan(s) cumulé(s)'
        if vel_violations or acc_violations:
            title += '  —  ⚠ DÉPASSEMENT DÉTECTÉ'
        fig.suptitle(title)
        return vel_violations, acc_violations

    def _log_violations(self, vel_violations, acc_violations):
        if vel_violations:
            for name, peak, limit in vel_violations:
                self.get_logger().warn(
                    f'  {name}: peak |v| = {peak:.4g} rad/s > max_velocity {limit:.4g} rad/s')
        elif self._vel_limits:
            self.get_logger().info('  All joints within velocity limits.')

        if acc_violations:
            for name, peak, limit in acc_violations:
                self.get_logger().warn(
                    f'  {name}: peak |a| = {peak:.4g} rad/s² > max_acceleration {limit:.4g} rad/s²')
        elif self._acc_limits:
            self.get_logger().info('  All joints within acceleration limits.')

    def _n_rows(self, names, tcp):
        return len(names) + (1 if tcp is not None else 0)

    def _render(self, series: dict, boundaries: list, filename: str,
                accumulated: bool, tcp):
        """Render to a fresh figure and save it as a PNG (always)."""
        names = list(series.keys())
        n = self._n_rows(names, tcp)
        fig, axes = plt.subplots(
            n, 2, figsize=(16, 2.2 * n), sharex=True, squeeze=False)

        vel_violations, acc_violations = self._draw_axes(
            fig, axes, names, series, boundaries, accumulated, tcp)
        fig.tight_layout(rect=[0, 0, 1, 0.98])

        out_dir = self.get_parameter('output_dir').get_parameter_value().string_value
        os.makedirs(out_dir, exist_ok=True)
        path = os.path.join(out_dir, filename)
        fig.savefig(path, dpi=120)
        plt.close(fig)

        if accumulated:
            self.get_logger().info(
                f'Plan #{self._plan_count} appended — {len(boundaries)} plan(s) in {path}')
        else:
            self.get_logger().info(f'Plan #{self._plan_count}: figure saved to {path}')

        self._log_violations(vel_violations, acc_violations)

    def _ensure_live_fig(self, n: int):
        """Create/resize the persistent live figure to hold n rows x 2 cols."""
        if (self._fig is None or self._live_axes is None
                or self._live_axes.shape[0] != n):
            if self._fig is not None:
                plt.close(self._fig)
            self._fig, axes = plt.subplots(
                n, 2, figsize=(16, 2.2 * n), sharex=True, squeeze=False)
            self._live_axes = axes
        return self._fig, self._live_axes

    def _update_live(self, series: dict, boundaries: list, accumulated: bool, tcp):
        """Redraw the persistent window in place (no new file)."""
        names = list(series.keys())
        n = self._n_rows(names, tcp)
        fig, axes = self._ensure_live_fig(n)
        self._draw_axes(fig, axes, names, series, boundaries, accumulated, tcp)
        fig.tight_layout(rect=[0, 0, 1, 0.98])
        try:
            fig.canvas.draw_idle()
            fig.canvas.flush_events()
        except Exception as exc:  # display gone / backend issue
            self.get_logger().warn(f'Live display update failed: {exc}')

    def _pump_gui(self):
        """Keep the live window responsive between plans."""
        if self._fig is not None:
            try:
                self._fig.canvas.flush_events()
            except Exception:
                pass


def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryPlotterNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()