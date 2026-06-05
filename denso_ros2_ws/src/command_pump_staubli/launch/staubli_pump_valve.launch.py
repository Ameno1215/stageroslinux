from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('namespace', default_value='staubli',
                              description='ROS service namespace'),
        DeclareLaunchArgument('io_service_name', default_value='/io_interface/write_single_io',
                              description='WriteSingleIO service exposed by staubli_io_interface'),
        DeclareLaunchArgument('service_wait_timeout', default_value='1.0',
                              description='Seconds to wait for io_interface service availability'),
        DeclareLaunchArgument('command_timeout', default_value='2.0',
                              description='Seconds to wait for each IO command response'),
        DeclareLaunchArgument('publish_initial_state', default_value='false',
                              description='Publish false as initial local output state before any command'),

        DeclareLaunchArgument('pump_module_id', default_value='4',
                              description='Staubli BASIC_OUT module id for pump'),
        DeclareLaunchArgument('pump_pin', default_value='0',
                              description='Staubli fOut0 pin for pump'),
        DeclareLaunchArgument('valve1_module_id', default_value='2',
                              description='Staubli VALVE_OUT module id for valve1'),
        DeclareLaunchArgument('valve1_pin', default_value='0',
                              description='Staubli valve1 pin'),
        DeclareLaunchArgument('valve2_module_id', default_value='2',
                              description='Staubli VALVE_OUT module id for valve2'),
        DeclareLaunchArgument('valve2_pin', default_value='1',
                              description='Staubli valve2 pin'),

        Node(
            package='command_pump_staubli',
            executable='staubli_pump_valve_node',
            name='staubli_pump_valve',
            parameters=[{
                'namespace': LaunchConfiguration('namespace'),
                'io_service_name': LaunchConfiguration('io_service_name'),
                'service_wait_timeout': LaunchConfiguration('service_wait_timeout'),
                'command_timeout': LaunchConfiguration('command_timeout'),
                'publish_initial_state': LaunchConfiguration('publish_initial_state'),
                'pump_module_id': LaunchConfiguration('pump_module_id'),
                'pump_pin': LaunchConfiguration('pump_pin'),
                'valve1_module_id': LaunchConfiguration('valve1_module_id'),
                'valve1_pin': LaunchConfiguration('valve1_pin'),
                'valve2_module_id': LaunchConfiguration('valve2_module_id'),
                'valve2_pin': LaunchConfiguration('valve2_pin'),
            }],
            output='screen',
        ),
    ])
