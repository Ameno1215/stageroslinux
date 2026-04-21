from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    declared_arguments = []
    
    declared_arguments.append(
        DeclareLaunchArgument(
            'model',
            default_value='tx2_60l',
            description='Type/series of used staubli robot.'
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            'tool',
            default_value='none',
            description='End-effector tool to attach (for future use).'
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            'sim',
            default_value='true',
            description='Start robot in simulation.'
        )
    )

    model = LaunchConfiguration('model')
    sim = LaunchConfiguration('sim')

    moveit_config_package_name = ['staubli_', model, '_moveit_config']
    
    # Launch file for real execution
    real_launch_file = PathJoinSubstitution([
        FindPackageShare(moveit_config_package_name),
        'launch',
        ['staubli_', model, '_planning_execution_real.launch.py']
    ])
    
    # Launch file for sim execution
    sim_launch_file = PathJoinSubstitution([
        FindPackageShare(moveit_config_package_name),
        'launch',
        ['staubli_', model, '_planning_execution_sim.launch.py']
    ])

    real_bringup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(real_launch_file),
        condition=UnlessCondition(sim)
    )

    sim_bringup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(sim_launch_file),
        condition=IfCondition(sim)
    )

    return LaunchDescription(declared_arguments + [real_bringup, sim_bringup])
