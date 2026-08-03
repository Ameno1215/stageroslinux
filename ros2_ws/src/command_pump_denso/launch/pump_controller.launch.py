from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('model', default_value='vs060',
                              description='Robot model namespace'),
        DeclareLaunchArgument('pump_pin', default_value='25',
                              description='Mini I/O port number for vacuum pump'),
        DeclareLaunchArgument('valve_pin', default_value='26',
                              description='Mini I/O port number for valve'),
        DeclareLaunchArgument('vacuum_sensor_pin', default_value='-1',
                              description='Mini I/O port number for vacuum sensor (-1 = disabled)'),

        Node(
            package='command_pump_denso',
            executable='pump_controller_node',
            name='pump_controller',
            parameters=[{
                'model': LaunchConfiguration('model'),
                'pump_pin': LaunchConfiguration('pump_pin'),
                'valve_pin': LaunchConfiguration('valve_pin'),
                'vacuum_sensor_pin': LaunchConfiguration('vacuum_sensor_pin'),
            }],
            output='screen',
        ),
    ])
