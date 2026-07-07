"""
ToolPosePublisherNode
=====================
Continuously publishes the pose (position + orientation) of the Denso VS060
tool on topics, for live display in PlotJuggler.

The pose is obtained via TF2: we look up the transform between the robot
base frame (`base_frame`) and the tool frame (`tool_frame`).
By default the VS060 exposes `base_link` and `tool_link` (the `tool_link` is
attached to `J6` by a fixed joint in the URDF).

Published topics
----------------
  ~/tool_pose   (geometry_msgs/PoseStamped)     -> position (m) + quaternion
  ~/tool_rpy    (geometry_msgs/Vector3Stamped)  -> roll/pitch/yaw in degrees
  ~/tool_dist   (std_msgs/Float64)              -> norm of the position (m)
  ~/tool_speed  (std_msgs/Float64)              -> norm of the TCP velocity (m/s)
  ~/tool_accel  (std_msgs/Float64)              -> norm of the TCP acceleration (m/s^2)


Parameters
----------
  base_frame    (str,   default 'base_link')  reference frame
  tool_frame    (str,   default 'tool_link')  tool frame (TCP)
  publish_rate  (float, default 100.0)        publication frequency (Hz)
  speed_alpha   (float, default 0.3)          low-pass filter coefficient on the
                                             velocity (1.0 = no filtering)
  accel_alpha   (float, default 0.3)          low-pass filter coefficient on the
                                             acceleration (1.0 = no filtering)
"""

import math

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import PoseStamped, Vector3Stamped
from std_msgs.msg import Float64

import tf2_ros
from tf2_ros import TransformException


def quaternion_to_rpy(x: float, y: float, z: float, w: float):
    """Converts a quaternion to Euler angles (roll, pitch, yaw) in radians.

    ZYX convention (yaw-pitch-roll), the same as tf_transformations.
    """
    # roll (rotation about x)
    sinr_cosp = 2.0 * (w * x + y * z)
    cosr_cosp = 1.0 - 2.0 * (x * x + y * y)
    roll = math.atan2(sinr_cosp, cosr_cosp)

    # pitch (rotation about y)
    sinp = 2.0 * (w * y - z * x)
    if abs(sinp) >= 1.0:
        pitch = math.copysign(math.pi / 2.0, sinp)  # clamp at +/-90 deg
    else:
        pitch = math.asin(sinp)

    # yaw (rotation about z)
    siny_cosp = 2.0 * (w * z + x * y)
    cosy_cosp = 1.0 - 2.0 * (y * y + z * z)
    yaw = math.atan2(siny_cosp, cosy_cosp)

    return roll, pitch, yaw


class ToolPosePublisherNode(Node):
    def __init__(self):
        super().__init__('tool_pose_publisher')

        self.declare_parameter('base_frame', 'base_link')
        self.declare_parameter('tool_frame', 'tool_link')
        self.declare_parameter('publish_rate', 100.0)
        self.declare_parameter('speed_alpha', 0.3)
        self.declare_parameter('accel_alpha', 0.3)

        self._base_frame = self.get_parameter('base_frame').get_parameter_value().string_value
        self._tool_frame = self.get_parameter('tool_frame').get_parameter_value().string_value
        rate = self.get_parameter('publish_rate').get_parameter_value().double_value
        if rate <= 0.0:
            rate = 100.0

        self._speed_alpha = self.get_parameter('speed_alpha').get_parameter_value().double_value
        if not (0.0 < self._speed_alpha <= 1.0):
            self._speed_alpha = 0.3

        self._accel_alpha = self.get_parameter('accel_alpha').get_parameter_value().double_value
        if not (0.0 < self._accel_alpha <= 1.0):
            self._accel_alpha = 0.3

        # Listen to the TF buffer
        self._tf_buffer = tf2_ros.Buffer()
        self._tf_listener = tf2_ros.TransformListener(self._tf_buffer, self)

        self._pose_pub = self.create_publisher(PoseStamped, '~/tool_pose', 10)
        self._rpy_pub = self.create_publisher(Vector3Stamped, '~/tool_rpy', 10)
        self._dist_pub = self.create_publisher(Float64, '~/tool_dist', 10)
        self._speed_pub = self.create_publisher(Float64, '~/tool_speed', 10)
        self._accel_pub = self.create_publisher(Float64, '~/tool_accel', 10)

        self._timer = self.create_timer(1.0 / rate, self._on_timer)

        # State for numerical differentiation of the velocity/acceleration
        self._prev_pos = None       # (x, y, z)
        self._prev_vel = None       # (vx, vy, vz)
        self._prev_stamp = None     # seconds (float)
        self._speed_filt = 0.0      # filtered velocity (low-pass)
        self._accel_filt = 0.0      # filtered acceleration (low-pass)

        # To limit warning spam when TF is not yet available
        self._warned = False

        self.get_logger().info(
            f'ToolPosePublisher ready — publishes the pose of "{self._tool_frame}" '
            f'expressed in "{self._base_frame}" at {rate:.1f} Hz '
            f'(topics: ~/tool_pose, ~/tool_rpy, ~/tool_dist, ~/tool_speed, ~/tool_accel)'
        )

    def _on_timer(self):
        try:
            # rclpy.time.Time() (=0) requests the most recent transform
            tf = self._tf_buffer.lookup_transform(
                self._base_frame,
                self._tool_frame,
                rclpy.time.Time(),
            )
        except TransformException as ex:
            if not self._warned:
                self.get_logger().warn(
                    f'Transform {self._base_frame} -> {self._tool_frame} '
                    f'unavailable: {ex}. Waiting for TF...'
                )
                self._warned = True
            return

        if self._warned:
            self.get_logger().info('TF transform available, publishing in progress.')
            self._warned = False

        t = tf.transform.translation
        q = tf.transform.rotation

        # ── PoseStamped: position (m) + orientation (quaternion) ──
        pose = PoseStamped()
        pose.header = tf.header  # stamp + frame_id = base_frame
        pose.pose.position.x = t.x
        pose.pose.position.y = t.y
        pose.pose.position.z = t.z
        pose.pose.orientation.x = q.x
        pose.pose.orientation.y = q.y
        pose.pose.orientation.z = q.z
        pose.pose.orientation.w = q.w
        self._pose_pub.publish(pose)

        # ── Vector3Stamped: roll/pitch/yaw in degrees ──
        roll, pitch, yaw = quaternion_to_rpy(q.x, q.y, q.z, q.w)
        rpy = Vector3Stamped()
        rpy.header = tf.header
        rpy.vector.x = math.degrees(roll)
        rpy.vector.y = math.degrees(pitch)
        rpy.vector.z = math.degrees(yaw)
        self._rpy_pub.publish(rpy)

        # ── Position norm (distance to the base_frame origin) ──
        dist = math.sqrt(t.x * t.x + t.y * t.y + t.z * t.z)
        self._dist_pub.publish(Float64(data=dist))

        # ── Velocity and acceleration ──
        stamp = tf.header.stamp.sec + tf.header.stamp.nanosec * 1e-9
        vel = None
        if self._prev_pos is not None and self._prev_stamp is not None:
            dt = stamp - self._prev_stamp
            if dt > 1e-6:
                vx = (t.x - self._prev_pos[0]) / dt
                vy = (t.y - self._prev_pos[1]) / dt
                vz = (t.z - self._prev_pos[2]) / dt
                vel = (vx, vy, vz)
                speed_raw = math.sqrt(vx * vx + vy * vy + vz * vz)
                # exponential low-pass filter to smooth the differentiation noise
                self._speed_filt = (
                    self._speed_alpha * speed_raw
                    + (1.0 - self._speed_alpha) * self._speed_filt
                )
                self._speed_pub.publish(Float64(data=self._speed_filt))

                if self._prev_vel is not None:
                    ax = (vx - self._prev_vel[0]) / dt
                    ay = (vy - self._prev_vel[1]) / dt
                    az = (vz - self._prev_vel[2]) / dt
                    accel_raw = math.sqrt(ax * ax + ay * ay + az * az)
                    # exponential low-pass filter to smooth the differentiation noise
                    self._accel_filt = (
                        self._accel_alpha * accel_raw
                        + (1.0 - self._accel_alpha) * self._accel_filt
                    )
                    self._accel_pub.publish(Float64(data=self._accel_filt))

        self._prev_pos = (t.x, t.y, t.z)
        if vel is not None:
            self._prev_vel = vel
        self._prev_stamp = stamp


def main(args=None):
    rclpy.init(args=args)
    node = ToolPosePublisherNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()