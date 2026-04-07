from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('joint_command_topic', default_value='/joint_command'),
        DeclareLaunchArgument('joint_states_topic', default_value='/joint_states'),
        DeclareLaunchArgument('action_name', default_value='follow_joint_trajectory'),
        Node(
            package='isaac_joint_trajectory_bridge',
            executable='follow_joint_trajectory_bridge',
            name='denso_joint_trajectory_controller',
            parameters=[{
                'joint_command_topic': LaunchConfiguration('joint_command_topic'),
                'joint_states_topic': LaunchConfiguration('joint_states_topic'),
                'action_name': LaunchConfiguration('action_name'),
            }],
            output='screen',
        ),
    ])
