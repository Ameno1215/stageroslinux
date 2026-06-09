from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    robot_ip_launch_arg = DeclareLaunchArgument(
        "robot_ip",
        description="IP address of the robot",
    )
    robot_ip = LaunchConfiguration(
        "robot_ip",
    )
    publish_io_states_arg = DeclareLaunchArgument(
        "publish_io_states",
        default_value="true",
        description="Publish /io_states from the IO socket",
    )
    io_state_poll_period_arg = DeclareLaunchArgument(
        "io_state_poll_period_sec",
        default_value="0.5",
        description="Polling period for /io_states",
    )
    vacuum_module_id_arg = DeclareLaunchArgument(
        "vacuum_module_id",
        default_value="3",
        description="IOModule id used for vacuum state in /io_states",
    )
    vacuum_pin_arg = DeclareLaunchArgument(
        "vacuum_pin",
        default_value="0",
        description="Pin used for vacuum state in /io_states",
    )
    
    io_interface = Node(
        package="staubli_val3_driver",
        executable="staubli_io_interface",
        parameters=[
            {
                "robot_ip_address": robot_ip,
                "publish_io_states": ParameterValue(LaunchConfiguration("publish_io_states"), value_type=bool),
                "io_state_poll_period_sec": ParameterValue(LaunchConfiguration("io_state_poll_period_sec"), value_type=float),
                "vacuum_module_id": ParameterValue(LaunchConfiguration("vacuum_module_id"), value_type=int),
                "vacuum_pin": ParameterValue(LaunchConfiguration("vacuum_pin"), value_type=int),
            }
        ],
    )

    return LaunchDescription(
        [
            robot_ip_launch_arg,
            publish_io_states_arg,
            io_state_poll_period_arg,
            vacuum_module_id_arg,
            vacuum_pin_arg,
            io_interface,
        ]
    )
