# command_pump_staubli

ROS2 Humble package to command the Staubli pump and valves through the existing Staubli IO interface.

It wraps the `staubli_val3_driver` service:

```text
/io_interface/write_single_io
```

This package does not open a direct TCP connection to the robot. Start `staubli_io_interface`
first, usually through `robot_interface_streaming.launch.py`.

- pump: `module_id=4`, `pin=0`, mapped to `FastIO/fOut0`
- valve1: `module_id=2`, `pin=0`, mapped to `valve1`
- valve2: `module_id=2`, `pin=1`, mapped to `valve2`

## Run

```bash
cd ~/workspace/denso_ros2_ws
colcon build --packages-select command_pump_staubli
source install/setup.bash
ros2 launch command_pump_staubli staubli_pump_valve.launch.py
```

## Services

```bash
ros2 service call /staubli/pump/set std_srvs/srv/SetBool "{data: true}"
ros2 service call /staubli/pump/set std_srvs/srv/SetBool "{data: false}"

ros2 service call /staubli/valve1/set std_srvs/srv/SetBool "{data: true}"
ros2 service call /staubli/valve1/set std_srvs/srv/SetBool "{data: false}"

ros2 service call /staubli/valve2/set std_srvs/srv/SetBool "{data: true}"
ros2 service call /staubli/valve2/set std_srvs/srv/SetBool "{data: false}"
```

Last commanded output states:

```bash
ros2 service call /staubli/pump/get std_srvs/srv/Trigger "{}"
ros2 service call /staubli/valve1/get std_srvs/srv/Trigger "{}"
ros2 service call /staubli/valve2/get std_srvs/srv/Trigger "{}"
```

State topics:

```text
/staubli/pump/state
/staubli/valve1/state
/staubli/valve2/state
```
