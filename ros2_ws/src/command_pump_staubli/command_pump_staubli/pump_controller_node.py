"""ROS 2 node for Staubli vacuum pump, valve and vacuum sensor control.

Default mapping comes from the Keolabs VAL3 controller:
  - pump: FastIO/fOut0 -> IOModule BASIC_OUT, pin 0
  - valve: ValveIO/valve1 -> IOModule VALVE_OUT, pin 0
  - vacuum sensor: FastIO/fIn0 -> IOModule BASIC_IN, pin 0
"""

from __future__ import annotations

import threading
import time
import socket
import struct
from typing import Optional

import rclpy
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from staubli_msgs.msg import IOModule, IOStates, ServiceReturnCode, TriState
from staubli_msgs.srv import WriteSingleIO
from std_msgs.msg import Bool
from std_srvs.srv import SetBool


class StaubliPumpController(Node):
    def __init__(self) -> None:
        super().__init__("pump_controller")

        self.declare_parameter("model", "staubli_tx40")
        self.declare_parameter("write_single_io_service", "/io_interface/write_single_io")
        self.declare_parameter("io_states_topic", "/io_states")
        self.declare_parameter("robot_ip_address", "")
        self.declare_parameter("io_port", 11003)
        self.declare_parameter("use_direct_io", False)
        self.declare_parameter("fallback_to_direct_io_on_service_failure", False)
        self.declare_parameter("pump_module_id", IOModule.BASIC_OUT)
        self.declare_parameter("pump_pin", 0)
        self.declare_parameter("valve_module_id", IOModule.VALVE_OUT)
        self.declare_parameter("valve_pin", 0)
        self.declare_parameter("vacuum_module_id", IOModule.BASIC_IN)
        self.declare_parameter("vacuum_pin", 0)
        self.declare_parameter("command_timeout_sec", 2.0)
        self.declare_parameter("service_wait_timeout_sec", 2.0)
        self.declare_parameter("grab_sequence_delay_sec", 0.05)
        self.declare_parameter("state_poll_period_sec", 0.5)

        self._model = self.get_parameter("model").value
        self._write_service = self.get_parameter("write_single_io_service").value
        self._io_states_topic = self.get_parameter("io_states_topic").value
        self._robot_ip_address = self.get_parameter("robot_ip_address").value
        self._io_port = int(self.get_parameter("io_port").value)
        self._use_direct_io = self._as_bool(self.get_parameter("use_direct_io").value)
        self._fallback_to_direct_io = self._as_bool(
            self.get_parameter("fallback_to_direct_io_on_service_failure").value
        )
        self._pump_module_id = int(self.get_parameter("pump_module_id").value)
        self._pump_pin = int(self.get_parameter("pump_pin").value)
        self._valve_module_id = int(self.get_parameter("valve_module_id").value)
        self._valve_pin = int(self.get_parameter("valve_pin").value)
        self._vacuum_module_id = int(self.get_parameter("vacuum_module_id").value)
        self._vacuum_pin = int(self.get_parameter("vacuum_pin").value)
        self._command_timeout_sec = float(self.get_parameter("command_timeout_sec").value)
        self._service_wait_timeout_sec = float(self.get_parameter("service_wait_timeout_sec").value)
        self._grab_sequence_delay_sec = float(self.get_parameter("grab_sequence_delay_sec").value)
        self._state_poll_period_sec = float(self.get_parameter("state_poll_period_sec").value)

        self._cb_group = ReentrantCallbackGroup()
        self._direct_io_lock = threading.Lock()
        self._write_client = self.create_client(
            WriteSingleIO,
            self._write_service,
            callback_group=self._cb_group,
        )

        self._last_io_states: Optional[IOStates] = None
        self._last_grabbed: Optional[bool] = None
        self._state_pub = self.create_publisher(Bool, f"/{self._model}/pump/grabbed", 10)
        self.create_subscription(
            IOStates,
            self._io_states_topic,
            self._on_io_states,
            10,
            callback_group=self._cb_group,
        )
        if self._use_direct_io:
            self.create_timer(
                self._state_poll_period_sec,
                self._publish_current_grabbed,
                callback_group=self._cb_group,
            )

        self.create_service(SetBool, f"/{self._model}/pump/grab", self._grab_cb, callback_group=self._cb_group)
        self.create_service(SetBool, f"/{self._model}/pump/release", self._release_cb, callback_group=self._cb_group)
        self.create_service(SetBool, f"/{self._model}/pump/set_pump", self._set_pump_cb, callback_group=self._cb_group)
        self.create_service(SetBool, f"/{self._model}/pump/set_valve", self._set_valve_cb, callback_group=self._cb_group)
        self.create_service(SetBool, f"/{self._model}/pump/is_grabbed", self._is_grabbed_cb, callback_group=self._cb_group)

        self.get_logger().info(
            "Staubli pump controller ready: "
            f"pump=module {self._pump_module_id} pin {self._pump_pin}, "
            f"valve=module {self._valve_module_id} pin {self._valve_pin}, "
            f"vacuum=module {self._vacuum_module_id} pin {self._vacuum_pin}, "
            f"direct_io={self._use_direct_io}, "
            f"fallback_direct_io={self._fallback_to_direct_io}"
        )

    def _grab_cb(self, request: SetBool.Request, response: SetBool.Response) -> SetBool.Response:
        if not request.data:
            response.success = False
            response.message = "Call release with data=true to release."
            return response

        ok, message = self._set_output(self._pump_module_id, self._pump_pin, True)
        if ok and self._grab_sequence_delay_sec > 0.0:
            time.sleep(self._grab_sequence_delay_sec)
        if ok:
            ok, message = self._set_output(self._valve_module_id, self._valve_pin, True)

        response.success = ok
        response.message = "Pump and valve enabled." if ok else message
        return response

    def _release_cb(self, request: SetBool.Request, response: SetBool.Response) -> SetBool.Response:
        if not request.data:
            response.success = False
            response.message = "Call release with data=true to release."
            return response

        ok, message = self._set_output(self._valve_module_id, self._valve_pin, False)
        if ok:
            ok, message = self._set_output(self._pump_module_id, self._pump_pin, False)

        response.success = ok
        response.message = "Pump and valve disabled." if ok else message
        return response

    def _set_pump_cb(self, request: SetBool.Request, response: SetBool.Response) -> SetBool.Response:
        response.success, response.message = self._set_output(self._pump_module_id, self._pump_pin, request.data)
        return response

    def _set_valve_cb(self, request: SetBool.Request, response: SetBool.Response) -> SetBool.Response:
        response.success, response.message = self._set_output(self._valve_module_id, self._valve_pin, request.data)
        return response

    def _is_grabbed_cb(self, _request: SetBool.Request, response: SetBool.Response) -> SetBool.Response:
        grabbed = self._read_vacuum_state()
        if grabbed is None:
            response.success = False
            response.message = f"No usable IO state received on {self._io_states_topic}."
            return response

        response.success = grabbed
        response.message = "Object grabbed." if grabbed else "Object not grabbed."
        return response

    def _set_output(self, module_id: int, pin: int, state: bool) -> tuple[bool, str]:
        if self._use_direct_io:
            return self._direct_write_single_io(module_id, pin, state)

        if not self._write_client.wait_for_service(timeout_sec=self._service_wait_timeout_sec):
            return self._fallback_direct_write(
                module_id,
                pin,
                state,
                f"WriteSingleIO service unavailable: {self._write_service}",
            )

        request = WriteSingleIO.Request()
        request.module.id = module_id
        request.pin = pin
        request.state = state

        future = self._write_client.call_async(request)
        done = threading.Event()
        future.add_done_callback(lambda _future: done.set())

        if not done.wait(timeout=self._command_timeout_sec):
            return self._fallback_direct_write(
                module_id,
                pin,
                state,
                f"Timeout while writing module {module_id} pin {pin}.",
            )

        result = future.result()
        if result is None:
            return self._fallback_direct_write(
                module_id,
                pin,
                state,
                f"WriteSingleIO failed for module {module_id} pin {pin}: no response.",
            )
        if result.code.val != ServiceReturnCode.SUCCESS:
            return self._fallback_direct_write(
                module_id,
                pin,
                state,
                f"WriteSingleIO rejected module {module_id} pin {pin}.",
            )

        state_text = "ON" if state else "OFF"
        return True, f"Set module {module_id} pin {pin} {state_text}."

    def _fallback_direct_write(
        self,
        module_id: int,
        pin: int,
        state: bool,
        service_message: str,
    ) -> tuple[bool, str]:
        if not self._fallback_to_direct_io or not self._robot_ip_address:
            return False, service_message

        direct_ok, direct_message = self._direct_write_single_io(module_id, pin, state)
        if direct_ok:
            self.get_logger().warn(f"{service_message} Falling back to direct IO.")
            return True, f"{direct_message} (fallback direct IO after service failure)"

        return False, f"{service_message} Direct IO fallback failed: {direct_message}"

    def _on_io_states(self, message: IOStates) -> None:
        if self._use_direct_io:
            return
        self._last_io_states = message
        self._publish_current_grabbed()

    def _publish_current_grabbed(self) -> None:
        grabbed = self._read_vacuum_state()
        if grabbed is not None and grabbed != self._last_grabbed:
            self._last_grabbed = grabbed
            self._state_pub.publish(Bool(data=grabbed))

    def _read_vacuum_state(self) -> Optional[bool]:
        if self._use_direct_io:
            grabbed, message = self._direct_read_vacuum()
            if grabbed is None:
                self.get_logger().warn(message, throttle_duration_sec=5.0)
            return grabbed

        if self._last_io_states is None:
            return None

        states = self._states_for_module(self._vacuum_module_id, self._last_io_states)
        if states is None or self._vacuum_pin < 0 or self._vacuum_pin >= len(states):
            return None

        value = states[self._vacuum_pin].val
        if value == TriState.TRUE:
            return True
        if value == TriState.FALSE:
            return False
        return None

    @staticmethod
    def _states_for_module(module_id: int, states: IOStates):
        if module_id == IOModule.USER_IN:
            return states.user_in
        if module_id == IOModule.VALVE_OUT:
            return states.valve_out
        if module_id == IOModule.BASIC_IN:
            return states.basic_io_in
        if module_id == IOModule.BASIC_OUT:
            return states.basic_io_out
        if module_id == IOModule.BASIC_IN_2:
            return states.basic_io_in_2
        if module_id == IOModule.BASIC_OUT_2:
            return states.basic_io_out_2
        return None

    @staticmethod
    def _as_bool(value) -> bool:
        if isinstance(value, bool):
            return value
        return str(value).strip().lower() in ("1", "true", "yes", "on")

    def _direct_write_single_io(self, module_id: int, pin: int, state: bool) -> tuple[bool, str]:
        body = struct.pack("<ii?", module_id, pin, state)
        reply_code, _body = self._direct_simple_request(1621, body)
        if reply_code != 1:
            return False, f"Direct WriteSingleIO rejected module {module_id} pin {pin}."

        state_text = "ON" if state else "OFF"
        return True, f"Set module {module_id} pin {pin} {state_text}."

    def _direct_read_vacuum(self) -> tuple[Optional[bool], str]:
        reply_code, body = self._direct_simple_request(1622, b"")
        if reply_code != 1:
            return None, "Direct vacuum read failed."
        if len(body) < 1:
            return None, "Direct vacuum read returned no body."
        return struct.unpack("<?", body[:1])[0], "Direct vacuum read OK."

    def _direct_simple_request(self, msg_type: int, body: bytes) -> tuple[int, bytes]:
        if not self._robot_ip_address:
            return 2, b""

        packet = struct.pack("<i", 12 + len(body))
        packet += struct.pack("<iii", msg_type, 2, 0)
        packet += body

        try:
            with self._direct_io_lock:
                with socket.create_connection(
                    (self._robot_ip_address, self._io_port),
                    timeout=self._command_timeout_sec,
                ) as sock:
                    sock.settimeout(self._command_timeout_sec)
                    sock.sendall(packet)
                    length = struct.unpack("<i", self._recv_exact(sock, 4))[0]
                    payload = self._recv_exact(sock, length)
        except OSError as exc:
            self.get_logger().warn(f"Direct IO request failed: {exc}", throttle_duration_sec=5.0)
            return 2, b""

        if len(payload) < 12:
            return 2, b""
        _reply_type, _comm_type, reply_code = struct.unpack("<iii", payload[:12])
        return reply_code, payload[12:]

    @staticmethod
    def _recv_exact(sock: socket.socket, size: int) -> bytes:
        chunks = []
        remaining = size
        while remaining > 0:
            chunk = sock.recv(remaining)
            if not chunk:
                raise OSError("socket closed")
            chunks.append(chunk)
            remaining -= len(chunk)
        return b"".join(chunks)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = StaubliPumpController()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
