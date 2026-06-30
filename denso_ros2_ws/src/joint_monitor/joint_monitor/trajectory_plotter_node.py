"""
TrajectoryPlotterNode
=====================
Subscribes to /display_planned_path (moveit_msgs/DisplayTrajectory), i.e. the
trajectory PLANNED by MoveIt (Pilz PTP/LIN/CIRC, or any other pipeline).

Unlike joint_monitor_node (which watches the EXECUTED motion on /joint_states
and differentiates position), this node reads the velocities that the planner
itself computed: each JointTrajectoryPoint already carries
``velocities[j]`` and ``time_from_start``. No differentiation needed.

For every received plan it produces one figure with a subplot per joint:
velocity vs trajectory time, plus the +/- max_velocity limit lines read from
``joint_limits.yaml``. If a joint exceeds its limit the node logs a warning
and the offending curve is highlighted.

This is exactly the data you see in the PlotJuggler tree
(``...points[i].velocities[j]`` / ``...points[i].time_from_start``), read
cleanly and plotted against the trajectory's own time axis.

Parameters:
  ~display_topic      (str)  topic to listen on   [/display_planned_path]
  ~joint_limits_file  (str)  path to joint_limits.yaml. If empty, the plot is
                             produced without limit lines.
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

import yaml
import rclpy
from rclpy.node import Node
from moveit_msgs.msg import DisplayTrajectory
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


def _load_velocity_limits(path: str, logger) -> dict:
    """Return {joint_name: max_velocity} from a MoveIt joint_limits.yaml.

    Joints with has_velocity_limits == false (or no max_velocity) are skipped.
    """
    if not path:
        return {}
    if not os.path.isfile(path):
        logger.warn(f'joint_limits_file not found: {path} (plotting without limits)')
        return {}

    with open(path, 'r') as f:
        data = yaml.safe_load(f) or {}

    limits = {}
    for name, props in _find_joint_limits_block(data).items():
        if not isinstance(props, dict):
            continue
        if props.get('has_velocity_limits', False) and 'max_velocity' in props:
            limits[name] = float(props['max_velocity'])
    return limits


class TrajectoryPlotterNode(Node):
    def __init__(self):
        super().__init__('trajectory_plotter')

        self.declare_parameter('display_topic', '/display_planned_path')
        self.declare_parameter('joint_limits_file', '')
        self.declare_parameter('output_dir', os.path.expanduser('~'))
        self.declare_parameter('show', False)   # deprecated alias of 'live'
        self.declare_parameter('live', False)
        self.declare_parameter('accumulate', True)

        topic = self.get_parameter('display_topic').get_parameter_value().string_value
        limits_file = self.get_parameter('joint_limits_file').get_parameter_value().string_value
        show = self.get_parameter('show').get_parameter_value().bool_value
        self._live = self.get_parameter('live').get_parameter_value().bool_value or show
        self._accumulate = self.get_parameter('accumulate').get_parameter_value().bool_value

        self._limits = _load_velocity_limits(limits_file, self.get_logger())

        # Persistent figure reused by the live window (created lazily).
        self._fig = None
        self._live_axes = None
        if self._live:
            # Live window needs an interactive backend + a display (WSLg / X).
            matplotlib.use('TkAgg', force=True)
            plt.ion()

        self._plan_count = 0
        self._reset_accumulator()

        self._sub = self.create_subscription(
            DisplayTrajectory, topic, self._on_display_trajectory, 10)
        self.create_service(Trigger, '~/reset', self._srv_reset)

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
        if self._limits:
            self.get_logger().info(
                f'Velocity limits loaded for {len(self._limits)} joints: '
                + ', '.join(f'{k}={v:.4g}' for k, v in self._limits.items()))
        else:
            self.get_logger().info(
                'No velocity limits loaded — set ~joint_limits_file to draw limit lines.')

    def _reset_accumulator(self):
        # joint_name -> {'t': [...], 'v': [...]} spanning all plans so far
        self._acc = {}
        self._acc_offset = 0.0       # running time offset for the next plan
        self._acc_boundaries = []    # x position of each plan start (for separators)

    def _srv_reset(self, _req, resp):
        self._reset_accumulator()
        self.get_logger().info('Accumulated timeline RESET — next plan starts a fresh image.')
        resp.success = True
        resp.message = 'Accumulator cleared.'
        return resp

    def _on_display_trajectory(self, msg: DisplayTrajectory):
        if not msg.trajectory:
            self.get_logger().warn('Received DisplayTrajectory with no trajectory, ignoring.')
            return

        series, duration = self._extract_series(msg)
        if not series:
            self.get_logger().warn('Trajectory had no joint points, nothing to plot.')
            return

        self._plan_count += 1

        if self._accumulate:
            self._append_to_accumulator(series, duration)
            plot_series, boundaries, accumulated = self._acc, self._acc_boundaries, True
            filename = 'planned_velocity_accumulated.png'
        else:
            plot_series, boundaries, accumulated = series, [], False
            stamp = datetime.now().strftime('%Y%m%d_%H%M%S')
            filename = f'planned_velocity_{self._plan_count:03d}_{stamp}.png'

        self._render(plot_series, boundaries, filename, accumulated)
        if self._live:
            self._update_live(plot_series, boundaries, accumulated)

    def _extract_series(self, msg: DisplayTrajectory):
        """Read one plan into {joint: {'t', 'v'}} plus its total duration.

        A plan may contain several RobotTrajectory segments (e.g. a Pilz
        MoveGroupSequence); they are concatenated on a continuous time axis.
        """
        series = {}
        time_offset = 0.0
        for robot_traj in msg.trajectory:
            jt = robot_traj.joint_trajectory
            if not jt.points:
                continue
            for n in jt.joint_names:
                series.setdefault(n, {'t': [], 'v': []})
            for pt in jt.points:
                t = time_offset + pt.time_from_start.sec + pt.time_from_start.nanosec * 1e-9
                for j, name in enumerate(jt.joint_names):
                    vel = pt.velocities[j] if j < len(pt.velocities) else 0.0
                    series[name]['t'].append(t)
                    series[name]['v'].append(vel)
            last = jt.points[-1].time_from_start
            time_offset += last.sec + last.nanosec * 1e-9
        return series, time_offset

    def _append_to_accumulator(self, series: dict, duration: float):
        """Append one plan to the running timeline, shifted by the offset."""
        self._acc_boundaries.append(self._acc_offset)
        for name, sv in series.items():
            acc = self._acc.setdefault(name, {'t': [], 'v': []})
            acc['t'].extend(self._acc_offset + t for t in sv['t'])
            acc['v'].extend(sv['v'])
        self._acc_offset += duration

    def _draw_axes(self, fig, axes, names, series, boundaries, accumulated):
        """Draw all subplots onto the given axes; return the list of violations.

        Axes are cleared first so this works both for a fresh figure (PNG) and
        for the reused persistent figure (live window).
        """
        violations = []
        for ax, name in zip(axes, names):
            ax.cla()
            t = series[name]['t']
            v = series[name]['v']
            ax.plot(t, v, color='tab:blue', linewidth=1.5, label='vitesse planifiée')
            ax.axhline(0.0, color='gray', linewidth=0.6)

            # Dashed vertical separators between successive plans.
            for b in boundaries[1:]:
                ax.axvline(b, color='gray', linestyle=':', linewidth=0.8)

            limit = self._limits.get(name)
            if limit is not None:
                ax.axhline(limit, color='red', linestyle='--', linewidth=1.0,
                           label=f'±max_velocity ({limit:.4g})')
                ax.axhline(-limit, color='red', linestyle='--', linewidth=1.0)
                peak = max(abs(min(v)), abs(max(v))) if v else 0.0
                if peak > limit + 1e-9:
                    violations.append((name, peak, limit))
                    ax.set_facecolor('#fff0f0')

            ax.set_ylabel(f'{name}\n[rad/s]')
            ax.grid(True, alpha=0.3)
            ax.legend(loc='upper right', fontsize=7)

        axes[-1].set_xlabel('temps [s]')
        title = 'Vitesses articulaires planifiées (Pilz / MoveIt)'
        if accumulated:
            title += f'  —  {len(boundaries)} plan(s) cumulé(s)'
        if violations:
            title += '  —  ⚠ DÉPASSEMENT DÉTECTÉ'
        fig.suptitle(title)
        return violations

    def _render(self, series: dict, boundaries: list, filename: str, accumulated: bool):
        """Render to a fresh figure and save it as a PNG (always)."""
        names = list(series.keys())
        n = len(names)
        fig, axes = plt.subplots(n, 1, figsize=(10, 2.2 * n), sharex=True, squeeze=False)
        axes = axes[:, 0]

        violations = self._draw_axes(fig, axes, names, series, boundaries, accumulated)
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

        if violations:
            for name, peak, limit in violations:
                self.get_logger().warn(
                    f'  {name}: peak |v| = {peak:.4g} rad/s > max_velocity {limit:.4g} rad/s')
        elif self._limits:
            self.get_logger().info('  All joints within velocity limits.')

    def _ensure_live_fig(self, n: int):
        """Create/resize the persistent live figure to hold n subplots."""
        if self._fig is None or self._live_axes is None or len(self._live_axes) != n:
            if self._fig is not None:
                plt.close(self._fig)
            self._fig, axes = plt.subplots(
                n, 1, figsize=(10, 2.2 * n), sharex=True, squeeze=False)
            self._live_axes = axes[:, 0]
        return self._fig, self._live_axes

    def _update_live(self, series: dict, boundaries: list, accumulated: bool):
        """Redraw the persistent window in place (no new file)."""
        names = list(series.keys())
        fig, axes = self._ensure_live_fig(len(names))
        self._draw_axes(fig, axes, names, series, boundaries, accumulated)
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
