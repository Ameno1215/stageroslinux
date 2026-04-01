"""
DensoPumpController - Configurable vacuum pump and valve controller for DENSO robots.

Controls a vacuum pump and valve via the DENSO Mini I/O bitmask system.
The pump and valve pin numbers are configurable, as well as an optional
vacuum sensor pin to detect whether a card/object has been grabbed.

The valve is in series with the pump:
  - Grab: pump ON + valve ON
  - Release: pump OFF + valve OFF

Usage:
    controller = DensoPumpController(
        node=my_node,
        pump_pin=25,
        valve_pin=26,
        vacuum_sensor_pin=8,  # optional, set to None if not used
        model="vs060",
    )

    # Wait for init (reads base MiniIO state)
    # Then:
    controller.grab()
    if controller.is_grabbed():
        # move robot
        controller.release()
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt32

from typing import Optional, Callable


class DensoPumpController:
    """Configurable vacuum pump and valve controller for DENSO robots via Mini I/O."""

    def __init__(
        self,
        node: Node,
        pump_pin: int,
        valve_pin: int,
        vacuum_sensor_pin: Optional[int] = None,
        model: str = "vs060",
    ):
        """
        Initialize the pump controller.

        Args:
            node: ROS2 node to attach publishers/subscribers to.
            pump_pin: Mini I/O port number for the vacuum pump (e.g., 25 = UOUT2).
            valve_pin: Mini I/O port number for the valve (e.g., 26 = UOUT3).
            vacuum_sensor_pin: Mini I/O port number for vacuum sensor input (e.g., 15 = UIN8).
                               Set to None if no vacuum sensor is available.
            model: Robot model name, used for topic namespace (e.g., "vs060").
        """
        self._node = node
        self._pump_pin = pump_pin
        self._valve_pin = valve_pin
        self._vacuum_sensor_pin = vacuum_sensor_pin
        self._model = model

        # Compute bitmasks from pin numbers
        self._pump_mask = 1 << pump_pin
        self._valve_mask = 1 << valve_pin
        self._grab_mask = self._pump_mask | self._valve_mask

        if vacuum_sensor_pin is not None:
            self._vacuum_sensor_mask = 1 << vacuum_sensor_pin
        else:
            self._vacuum_sensor_mask = None

        # State
        self._base_state: Optional[int] = None
        self._current_read_state: int = 0
        self._initialized = False

        # Publisher for writing Mini I/O outputs
        self._write_pub = node.create_publisher(
            UInt32,
            f"/{model}/Write_MiniIO",
            1,
        )

        # Subscriber for reading Mini I/O state
        self._read_sub = node.create_subscription(
            UInt32,
            f"/{model}/Read_MiniIO",
            self._on_read_mini_io,
            1,
        )

        # Optional user callbacks
        self._on_initialized_callback: Optional[Callable] = None
        self._on_grab_detected_callback: Optional[Callable] = None
        self._on_grab_lost_callback: Optional[Callable] = None

        # Previous grab state for edge detection
        self._was_grabbed = False

        self._node.get_logger().info(
            f"[PumpController] Created — pump=pin {pump_pin} (mask 0x{self._pump_mask:08X}), "
            f"valve=pin {valve_pin} (mask 0x{self._valve_mask:08X}), "
            f"vacuum_sensor=pin {vacuum_sensor_pin}, model={model}"
        )

    # -------------------------------------------------------------------------
    # Properties
    # -------------------------------------------------------------------------

    @property
    def initialized(self) -> bool:
        """True once the base Mini I/O state has been read at least once."""
        return self._initialized

    @property
    def base_state(self) -> Optional[int]:
        """The initial Mini I/O state captured on first read (system status bits)."""
        return self._base_state

    @property
    def current_read_state(self) -> int:
        """The most recent Read_MiniIO value."""
        return self._current_read_state

    @property
    def pump_pin(self) -> int:
        return self._pump_pin

    @property
    def valve_pin(self) -> int:
        return self._valve_pin

    @property
    def vacuum_sensor_pin(self) -> Optional[int]:
        return self._vacuum_sensor_pin

    # -------------------------------------------------------------------------
    # Callbacks registration
    # -------------------------------------------------------------------------

    def on_initialized(self, callback: Callable):
        """Register a callback called once when the base state is first read."""
        self._on_initialized_callback = callback

    def on_grab_detected(self, callback: Callable):
        """Register a callback called when vacuum sensor detects a grab (rising edge)."""
        self._on_grab_detected_callback = callback

    def on_grab_lost(self, callback: Callable):
        """Register a callback called when vacuum sensor detects grab lost (falling edge)."""
        self._on_grab_lost_callback = callback

    # -------------------------------------------------------------------------
    # Core actions
    # -------------------------------------------------------------------------

    def grab(self) -> bool:
        """
        Activate pump + valve to grab an object.

        Returns:
            True if the command was sent, False if not initialized yet.
        """
        if not self._initialized:
            self._node.get_logger().warn("[PumpController] Cannot grab — not initialized yet.")
            return False

        value = self._base_state | self._grab_mask
        self._write(value)
        self._node.get_logger().info(
            f"[PumpController] GRAB — sending {value} (0x{value:08X})"
        )
        return True

    def release(self) -> bool:
        """
        Deactivate pump + valve to release an object.

        Returns:
            True if the command was sent, False if not initialized yet.
        """
        if not self._initialized:
            self._node.get_logger().warn("[PumpController] Cannot release — not initialized yet.")
            return False

        # Clear pump and valve bits, keep base state
        value = self._base_state & ~self._grab_mask
        self._write(value)
        self._node.get_logger().info(
            f"[PumpController] RELEASE — sending {value} (0x{value:08X})"
        )
        return True

    def is_grabbed(self) -> bool:
        """
        Check if an object is currently grabbed based on vacuum sensor input.

        Returns:
            True if vacuum sensor indicates object is grabbed.
            Always returns False if no vacuum sensor pin was configured.
        """
        if self._vacuum_sensor_mask is None:
            self._node.get_logger().warn(
                "[PumpController] No vacuum sensor pin configured — cannot check grab state."
            )
            return False

        return bool(self._current_read_state & self._vacuum_sensor_mask)

    def is_pump_active(self) -> bool:
        """Check if the pump output is currently active based on last Read_MiniIO."""
        return bool(self._current_read_state & self._pump_mask)

    def is_valve_active(self) -> bool:
        """Check if the valve output is currently active based on last Read_MiniIO."""
        return bool(self._current_read_state & self._valve_mask)

    # -------------------------------------------------------------------------
    # Internal
    # -------------------------------------------------------------------------

    def _write(self, value: int):
        """Publish a UInt32 value to Write_MiniIO."""
        msg = UInt32()
        msg.data = value
        self._write_pub.publish(msg)

    def _on_read_mini_io(self, msg: UInt32):
        """Callback for Read_MiniIO subscription."""
        self._current_read_state = msg.data

        # Capture base state on first read (mask out user output bits 24-31)
        if not self._initialized:
            # Keep only non-user-output bits as the base state
            # User outputs are bits 24-31, so mask = 0x00FFFFFF
            self._base_state = msg.data & 0x00FFFFFF
            self._initialized = True
            self._node.get_logger().info(
                f"[PumpController] Initialized — base state = {self._base_state} "
                f"(0x{self._base_state:08X})"
            )
            if self._on_initialized_callback:
                self._on_initialized_callback()

        # Edge detection on vacuum sensor
        if self._vacuum_sensor_mask is not None:
            is_grabbed_now = bool(msg.data & self._vacuum_sensor_mask)
            if is_grabbed_now and not self._was_grabbed:
                self._node.get_logger().info("[PumpController] Grab DETECTED (vacuum sensor)")
                if self._on_grab_detected_callback:
                    self._on_grab_detected_callback()
            elif not is_grabbed_now and self._was_grabbed:
                self._node.get_logger().info("[PumpController] Grab LOST (vacuum sensor)")
                if self._on_grab_lost_callback:
                    self._on_grab_lost_callback()
            self._was_grabbed = is_grabbed_now
