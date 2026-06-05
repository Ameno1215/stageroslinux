import threading

import rclpy
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from staubli_msgs.srv import WriteSingleIO
from std_msgs.msg import Bool
from std_srvs.srv import SetBool
from std_srvs.srv import Trigger


class StaubliPumpValveNode(Node):
    def __init__(self):
        super().__init__('staubli_pump_valve')

        self.declare_parameter('namespace', 'staubli')
        self.declare_parameter('io_service_name', '/io_interface/write_single_io')
        self.declare_parameter('service_wait_timeout', 1.0)
        self.declare_parameter('command_timeout', 2.0)
        self.declare_parameter('publish_initial_state', False)

        self.declare_parameter('pump_module_id', 4)
        self.declare_parameter('pump_pin', 0)
        self.declare_parameter('valve1_module_id', 2)
        self.declare_parameter('valve1_pin', 0)
        self.declare_parameter('valve2_module_id', 2)
        self.declare_parameter('valve2_pin', 1)

        namespace = self.get_parameter('namespace').get_parameter_value().string_value.strip('/')
        self._io_service_name = self.get_parameter('io_service_name').get_parameter_value().string_value
        self._service_wait_timeout = (
            self.get_parameter('service_wait_timeout').get_parameter_value().double_value
        )
        self._command_timeout = self.get_parameter('command_timeout').get_parameter_value().double_value
        publish_initial_state = (
            self.get_parameter('publish_initial_state').get_parameter_value().bool_value
        )

        self._callback_group = ReentrantCallbackGroup()
        self._io_client = self.create_client(
            WriteSingleIO,
            self._io_service_name,
            callback_group=self._callback_group,
        )

        self._outputs = {
            'pump': (
                self.get_parameter('pump_module_id').get_parameter_value().integer_value,
                self.get_parameter('pump_pin').get_parameter_value().integer_value,
            ),
            'valve1': (
                self.get_parameter('valve1_module_id').get_parameter_value().integer_value,
                self.get_parameter('valve1_pin').get_parameter_value().integer_value,
            ),
            'valve2': (
                self.get_parameter('valve2_module_id').get_parameter_value().integer_value,
                self.get_parameter('valve2_pin').get_parameter_value().integer_value,
            ),
        }

        service_prefix = f'/{namespace}' if namespace else ''
        self._states = {name: None for name in self._outputs}
        self._state_publishers = {
            name: self.create_publisher(Bool, f'{service_prefix}/{name}/state', 10)
            for name in self._outputs
        }
        self._services = [
            self.create_service(
                SetBool,
                f'{service_prefix}/pump/set',
                self._make_set_handler('pump'),
                callback_group=self._callback_group,
            ),
            self.create_service(
                SetBool,
                f'{service_prefix}/valve1/set',
                self._make_set_handler('valve1'),
                callback_group=self._callback_group,
            ),
            self.create_service(
                SetBool,
                f'{service_prefix}/valve2/set',
                self._make_set_handler('valve2'),
                callback_group=self._callback_group,
            ),
            self.create_service(
                Trigger,
                f'{service_prefix}/pump/get',
                self._make_get_handler('pump'),
                callback_group=self._callback_group,
            ),
            self.create_service(
                Trigger,
                f'{service_prefix}/valve1/get',
                self._make_get_handler('valve1'),
                callback_group=self._callback_group,
            ),
            self.create_service(
                Trigger,
                f'{service_prefix}/valve2/get',
                self._make_get_handler('valve2'),
                callback_group=self._callback_group,
            ),
        ]

        if publish_initial_state:
            for output_name in self._states:
                self._states[output_name] = False
                self._publish_state(output_name)

        self.get_logger().info(
            'Ready for Staubli IO commands through '
            f'{self._io_service_name}. Services: '
            f'{service_prefix}/pump/set, '
            f'{service_prefix}/valve1/set, '
            f'{service_prefix}/valve2/set'
        )

    def _make_set_handler(self, output_name: str):
        def _handler(request: SetBool.Request, response: SetBool.Response):
            module_id, pin = self._outputs[output_name]
            state = bool(request.data)

            if not self._io_client.wait_for_service(timeout_sec=self._service_wait_timeout):
                response.success = False
                response.message = (
                    f'Staubli IO service not available: {self._io_service_name}. '
                    'Launch staubli_val3_driver robot_interface_streaming first.'
                )
                self.get_logger().warn(response.message)
                return response

            io_request = WriteSingleIO.Request()
            io_request.module.id = int(module_id)
            io_request.pin = int(pin)
            io_request.state = state

            future = self._io_client.call_async(io_request)
            if not self._wait_for_future(future):
                response.success = False
                response.message = (
                    f'Timeout while setting {output_name} '
                    f'(module_id={module_id}, pin={pin}, state={int(state)})'
                )
                self.get_logger().error(response.message)
                return response

            try:
                io_response = future.result()
            except Exception as exc:
                response.success = False
                response.message = (
                    f'Failed to set {output_name} '
                    f'(module_id={module_id}, pin={pin}, state={int(state)}): {exc}'
                )
                self.get_logger().error(response.message)
                return response

            response.success = io_response.code.val == 1
            if response.success:
                self._states[output_name] = state
                self._publish_state(output_name)
                response.message = (
                    f'{output_name} set to {int(state)} '
                    f'(module_id={module_id}, pin={pin})'
                )
                self.get_logger().info(response.message)
            else:
                response.message = (
                    f'Staubli IO service rejected {output_name} command '
                    f'(module_id={module_id}, pin={pin}, state={int(state)}, '
                    f'code={io_response.code.val})'
                )
                self.get_logger().error(response.message)

            return response

        return _handler

    def _make_get_handler(self, output_name: str):
        def _handler(request: Trigger.Request, response: Trigger.Response):
            del request

            state = self._states[output_name]
            if state is None:
                response.success = False
                response.message = (
                    f'{output_name} state unknown: no successful command sent '
                    'through this wrapper yet'
                )
                return response

            response.success = True
            response.message = f'state={str(state).lower()}'
            return response

        return _handler

    def _publish_state(self, output_name: str) -> None:
        state = self._states[output_name]
        if state is None:
            return

        msg = Bool()
        msg.data = bool(state)
        self._state_publishers[output_name].publish(msg)

    def _wait_for_future(self, future) -> bool:
        done_event = threading.Event()
        future.add_done_callback(lambda _: done_event.set())

        if done_event.wait(timeout=self._command_timeout):
            return True

        future.cancel()
        return False


def main(args=None):
    rclpy.init(args=args)
    node = StaubliPumpValveNode()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)

    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info('Shutting down Staubli pump/valve node.')
        executor.remove_node(node)
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
