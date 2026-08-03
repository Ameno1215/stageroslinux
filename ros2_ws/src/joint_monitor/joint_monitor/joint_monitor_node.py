"""
JointMonitorNode
================
Subscribes to /joint_states (sensor_msgs/JointState).
Computes velocity and acceleration from position via finite differences.

NOTE: The Gazebo position controller (GazeboSystem) calls SetVelocity(0)
every cycle, so msg.velocity is always ~0. We MUST compute velocity from
position changes ourselves.

Services (all std_srvs/Trigger):
  ~/start_recording   - begin recording (resets history, keeps stats)
  ~/stop_recording    - pause recording (stats preserved)
  ~/reset             - clear all accumulated stats
  ~/get_stats         - returns JSON with all min/max data
"""

import json
import math
import os
import csv
from datetime import datetime
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger


class JointStats:
    """Min/max tracker for a single joint.

    Velocity and acceleration are computed from position via finite
    differences, because the Gazebo plugin resets velocity to 0 each cycle.
    A simple exponential moving average (EMA) is used to smooth out the
    high-frequency noise inherent in numerical differentiation.
    """
    __slots__ = (
        'pos_min', 'pos_max',
        'vel_min', 'vel_max',
        'acc_min', 'acc_max',
        'prev_pos', 'prev_vel', 'prev_stamp',
        'filtered_vel', 'filtered_acc',
        'acc_prev_vel', 'acc_prev_stamp',
        'acc_counter',
        'sample_count',
    )

    # EMA smoothing factor for velocity (0 = no smoothing, 1 = no update).
    # 0.2 gives a good balance between responsiveness and noise rejection
    # at ~1000 Hz publish rate.
    VEL_ALPHA = 0.2

    # For acceleration: compute every N samples to increase dt and reduce noise.
    # At 1000 Hz, decimation of 10 → effective 100 Hz → dt ~ 10ms.
    ACC_DECIMATION = 10

    # EMA smoothing factor for acceleration (stronger than velocity).
    ACC_ALPHA = 0.3

    def __init__(self):
        self.reset()

    def reset(self):
        self.pos_min = math.inf
        self.pos_max = -math.inf
        self.vel_min = math.inf
        self.vel_max = -math.inf
        self.acc_min = math.inf
        self.acc_max = -math.inf
        self.prev_pos = None
        self.prev_vel = None
        self.prev_stamp = None
        self.filtered_vel = 0.0
        self.filtered_acc = 0.0
        self.acc_prev_vel = None
        self.acc_prev_stamp = None
        self.acc_counter = 0
        self.sample_count = 0

    def update(self, position: float, stamp_sec: float):
        self.sample_count += 1

        # ── Position ──
        if position < self.pos_min:
            self.pos_min = position
        if position > self.pos_max:
            self.pos_max = position

        if self.prev_pos is None or self.prev_stamp is None:
            # First sample: just store and return
            self.prev_pos = position
            self.prev_stamp = stamp_sec
            return

        dt = stamp_sec - self.prev_stamp
        if dt < 1e-9:
            # Duplicate timestamp — skip to avoid division by zero
            return

        # ── Velocity (computed from position) ──
        raw_vel = (position - self.prev_pos) / dt

        # EMA filter to reduce differentiation noise
        self.filtered_vel = (
            self.VEL_ALPHA * self.filtered_vel
            + (1.0 - self.VEL_ALPHA) * raw_vel
        )

        velocity = self.filtered_vel

        if velocity < self.vel_min:
            self.vel_min = velocity
        if velocity > self.vel_max:
            self.vel_max = velocity

        # ── Acceleration (decimated + filtered) ──
        # Only compute every ACC_DECIMATION samples to increase effective dt
        # and reduce noise from double-differentiation at 1000 Hz.
        self.acc_counter += 1
        if self.acc_counter >= self.ACC_DECIMATION:
            self.acc_counter = 0
            if self.acc_prev_vel is not None and self.acc_prev_stamp is not None:
                acc_dt = stamp_sec - self.acc_prev_stamp
                if acc_dt > 1e-9:
                    raw_acc = (velocity - self.acc_prev_vel) / acc_dt
                    # EMA filter on acceleration
                    self.filtered_acc = (
                        self.ACC_ALPHA * self.filtered_acc
                        + (1.0 - self.ACC_ALPHA) * raw_acc
                    )
                    if self.filtered_acc < self.acc_min:
                        self.acc_min = self.filtered_acc
                    if self.filtered_acc > self.acc_max:
                        self.acc_max = self.filtered_acc
            self.acc_prev_vel = velocity
            self.acc_prev_stamp = stamp_sec

        self.prev_pos = position
        self.prev_vel = velocity
        self.prev_stamp = stamp_sec

    def to_dict(self) -> dict:
        def _safe(v):
            return None if math.isinf(v) else round(v, 6)

        return {
            'position': {'min': _safe(self.pos_min), 'max': _safe(self.pos_max)},
            'velocity': {'min': _safe(self.vel_min), 'max': _safe(self.vel_max)},
            'acceleration': {'min': _safe(self.acc_min), 'max': _safe(self.acc_max)},
            'sample_count': self.sample_count,
        }


class JointMonitorNode(Node):
    def __init__(self):
        super().__init__('joint_monitor')

        self.declare_parameter('joint_states_topic', '/joint_states')
        self.declare_parameter('csv_output_dir', '/home/antonin/workspace')
        topic = self.get_parameter('joint_states_topic').get_parameter_value().string_value

        self._recording = False
        self._stats: dict[str, JointStats] = {}

        self._sub = self.create_subscription(JointState, topic, self._on_joint_state, 10)

        self.create_service(Trigger, '~/start_recording', self._srv_start)
        self.create_service(Trigger, '~/stop_recording', self._srv_stop)
        self.create_service(Trigger, '~/reset', self._srv_reset)
        self.create_service(Trigger, '~/get_stats', self._srv_get_stats)

        self.get_logger().info(
            f'JointMonitor ready — listening on {topic} '
            f'(recording paused until start_recording is called)'
        )
        self.get_logger().info(
            'Velocity/acceleration computed from POSITION differences '
            '(msg.velocity ignored — Gazebo resets it to 0 each cycle)'
        )

    # ---- subscription callback ----
    def _on_joint_state(self, msg: JointState):
        if not self._recording:
            return

        stamp_sec = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9

        for i, name in enumerate(msg.name):
            pos = msg.position[i] if i < len(msg.position) else 0.0

            if name not in self._stats:
                self._stats[name] = JointStats()
            self._stats[name].update(pos, stamp_sec)

    # ---- service callbacks ----
    def _srv_start(self, _req, resp):
        if self._recording:
            resp.success = True
            resp.message = 'Already recording.'
            return resp

        # Clear history to avoid bogus derivatives across a pause gap
        for s in self._stats.values():
            s.prev_pos = None
            s.prev_vel = None
            s.prev_stamp = None
            s.filtered_vel = 0.0

        self._recording = True
        self.get_logger().info('Recording STARTED')
        resp.success = True
        resp.message = 'Recording started.'
        return resp

    def _srv_stop(self, _req, resp):
        self._recording = False
        self.get_logger().info('Recording STOPPED')
        resp.success = True
        resp.message = 'Recording stopped.'
        return resp

    def _srv_reset(self, _req, resp):
        self._stats.clear()
        self.get_logger().info('Stats RESET')
        resp.success = True
        resp.message = 'Stats cleared.'
        return resp

    def _srv_get_stats(self, _req, resp):
        payload = {
            'recording': self._recording,
            'joints': {name: s.to_dict() for name, s in self._stats.items()},
        }
        resp.success = True
        resp.message = json.dumps(payload)

        # Export CSV
        self._export_csv()

        return resp

    def _export_csv(self):
        if not self._stats:
            self.get_logger().info('No data recorded yet, CSV not exported.')
            return

        out_dir = self.get_parameter('csv_output_dir').get_parameter_value().string_value
        os.makedirs(out_dir, exist_ok=True)

        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        path = os.path.join(out_dir, f'joint_stats_{timestamp}.csv')

        with open(path, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([
                'joint', 'pos_min', 'pos_max',
                'vel_min', 'vel_max',
                'acc_min', 'acc_max',
                'sample_count',
            ])
            for name in sorted(self._stats.keys()):
                d = self._stats[name].to_dict()
                p, v, a = d['position'], d['velocity'], d['acceleration']
                writer.writerow([
                    name,
                    p['min'], p['max'],
                    v['min'], v['max'],
                    a['min'], a['max'],
                    d['sample_count'],
                ])

        self.get_logger().info(f'CSV exported: {path}')


def main(args=None):
    rclpy.init(args=args)
    node = JointMonitorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()