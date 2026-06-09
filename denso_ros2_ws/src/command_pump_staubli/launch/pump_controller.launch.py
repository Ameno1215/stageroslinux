from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("model", default_value="staubli_tx40"),
            DeclareLaunchArgument("write_single_io_service", default_value="/io_interface/write_single_io"),
            DeclareLaunchArgument("io_states_topic", default_value="/io_states"),
            DeclareLaunchArgument("robot_ip_address", default_value=""),
            DeclareLaunchArgument("io_port", default_value="11003"),
            DeclareLaunchArgument("use_direct_io", default_value="false"),
            DeclareLaunchArgument("fallback_to_direct_io_on_service_failure", default_value="false"),
            DeclareLaunchArgument("state_poll_period_sec", default_value="0.5"),
            DeclareLaunchArgument("pump_module_id", default_value="4"),
            DeclareLaunchArgument("pump_pin", default_value="0"),
            DeclareLaunchArgument("valve_module_id", default_value="2"),
            DeclareLaunchArgument("valve_pin", default_value="0"),
            DeclareLaunchArgument("vacuum_module_id", default_value="3"),
            DeclareLaunchArgument("vacuum_pin", default_value="0"),
            Node(
                package="command_pump_staubli",
                executable="pump_controller_node",
                name="pump_controller",
                parameters=[
                    {
                        "model": LaunchConfiguration("model"),
                        "write_single_io_service": LaunchConfiguration("write_single_io_service"),
                        "io_states_topic": LaunchConfiguration("io_states_topic"),
                        "robot_ip_address": LaunchConfiguration("robot_ip_address"),
                        "io_port": LaunchConfiguration("io_port"),
                        "use_direct_io": LaunchConfiguration("use_direct_io"),
                        "fallback_to_direct_io_on_service_failure": LaunchConfiguration("fallback_to_direct_io_on_service_failure"),
                        "state_poll_period_sec": LaunchConfiguration("state_poll_period_sec"),
                        "pump_module_id": LaunchConfiguration("pump_module_id"),
                        "pump_pin": LaunchConfiguration("pump_pin"),
                        "valve_module_id": LaunchConfiguration("valve_module_id"),
                        "valve_pin": LaunchConfiguration("valve_pin"),
                        "vacuum_module_id": LaunchConfiguration("vacuum_module_id"),
                        "vacuum_pin": LaunchConfiguration("vacuum_pin"),
                    }
                ],
            ),
        ]
    )
