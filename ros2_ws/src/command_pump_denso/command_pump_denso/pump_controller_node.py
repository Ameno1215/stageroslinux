"""
ROS2 Node for the DENSO Pump Controller.

Exposes services:
  - /{model}/pump/grab      (std_srvs/SetBool)  → data=true to grab
  - /{model}/pump/release   (std_srvs/SetBool)  → data=true to release
  - /{model}/pump/is_grabbed (std_srvs/SetBool) → response.success = grabbed state

Parameters:
  - pump_pin (int, default=25): Mini I/O port number for the pump
  - valve_pin (int, default=26): Mini I/O port number for the valve
  - vacuum_sensor_pin (int, default=-1): Mini I/O port for vacuum sensor (-1 = disabled)
  - model (string, default="vs060"): Robot model namespace
"""

import rclpy
from rclpy.node import Node
from std_srvs.srv import SetBool

from command_pump_denso.denso_pump_controller import DensoPumpController


class PumpControllerNode(Node):
    def __init__(self):
        super().__init__('pump_controller')

        # Declare parameters
        self.declare_parameter('pump_pin', 25)
        self.declare_parameter('valve_pin', 26)
        self.declare_parameter('vacuum_sensor_pin', -1)
        self.declare_parameter('model', 'vs060')

        # Read parameters
        pump_pin = self.get_parameter('pump_pin').get_parameter_value().integer_value
        valve_pin = self.get_parameter('valve_pin').get_parameter_value().integer_value
        vacuum_sensor_pin_raw = self.get_parameter('vacuum_sensor_pin').get_parameter_value().integer_value
        model = self.get_parameter('model').get_parameter_value().string_value

        vacuum_sensor_pin = vacuum_sensor_pin_raw if vacuum_sensor_pin_raw >= 0 else None

        # Create the pump controller
        self._controller = DensoPumpController(
            node=self,
            pump_pin=pump_pin,
            valve_pin=valve_pin,
            vacuum_sensor_pin=vacuum_sensor_pin,
            model=model,
        )

        # Create services
        self._grab_srv = self.create_service(
            SetBool,
            f'/{model}/pump/grab',
            self._handle_grab,
        )

        self._release_srv = self.create_service(
            SetBool,
            f'/{model}/pump/release',
            self._handle_release,
        )

        self._is_grabbed_srv = self.create_service(
            SetBool,
            f'/{model}/pump/is_grabbed',
            self._handle_is_grabbed,
        )

        self.get_logger().info(
            f"[PumpControllerNode] Ready — services: "
            f"/{model}/pump/grab, /{model}/pump/release, /{model}/pump/is_grabbed"
        )

    def _handle_grab(self, request: SetBool.Request, response: SetBool.Response):
        if not request.data:
            response.success = False
            response.message = "Send data=true to grab"
            return response

        success = self._controller.grab()
        response.success = success
        response.message = "Grab command sent" if success else "Not initialized — no Read_MiniIO received yet"
        return response

    def _handle_release(self, request: SetBool.Request, response: SetBool.Response):
        if not request.data:
            response.success = False
            response.message = "Send data=true to release"
            return response

        success = self._controller.release()
        response.success = success
        response.message = "Release command sent" if success else "Not initialized — no Read_MiniIO received yet"
        return response

    def _handle_is_grabbed(self, request: SetBool.Request, response: SetBool.Response):
        grabbed = self._controller.is_grabbed()
        response.success = grabbed
        response.message = "Object detected" if grabbed else "No object detected"
        return response

    @property
    def controller(self) -> DensoPumpController:
        """Access the underlying DensoPumpController instance."""
        return self._controller


def main(args=None):
    rclpy.init(args=args)
    node = PumpControllerNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info("[PumpControllerNode] Shutting down.")
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
