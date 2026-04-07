import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState


class JointStateRelay(Node):
    def __init__(self) -> None:
        super().__init__('joint_state_relay')

        self.declare_parameter('input_topic', '/joint_states_raw')
        self.declare_parameter('output_topic', '/joint_states')
        self.declare_parameter('restamp', True)

        input_topic = self.get_parameter('input_topic').get_parameter_value().string_value
        output_topic = self.get_parameter('output_topic').get_parameter_value().string_value
        self._restamp = self.get_parameter('restamp').get_parameter_value().bool_value

        self._pub = self.create_publisher(JointState, output_topic, 50)
        self._sub = self.create_subscription(JointState, input_topic, self._on_joint_state, 50)

        self.get_logger().info(
            f'JointState relay ready: {input_topic} -> {output_topic} (restamp={self._restamp})'
        )

    def _on_joint_state(self, msg: JointState) -> None:
        out = JointState()
        out.header = msg.header
        if self._restamp or (out.header.stamp.sec == 0 and out.header.stamp.nanosec == 0):
            out.header.stamp = self.get_clock().now().to_msg()
        out.name = list(msg.name)
        out.position = list(msg.position)
        out.velocity = list(msg.velocity)
        out.effort = list(msg.effort)
        self._pub.publish(out)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = JointStateRelay()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
