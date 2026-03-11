import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration, Command, PathJoinSubstitution, FindExecutable
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch_ros.substitutions import FindPackageShare
import xacro


def generate_launch_description():

    # Declare the sim argument so it can be passed through
    sim_arg = DeclareLaunchArgument(
        'sim',
        default_value='true',
        description='Start robot in simulation (Gazebo).'
    )
    sim = LaunchConfiguration('sim')

    # Avoid Gazebo downloading models from the internet which stalls startup for 30+ seconds
    os.environ["GAZEBO_MODEL_DATABASE_URI"] = ""

    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]), ' ',
            PathJoinSubstitution(
                [FindPackageShare("staubli_tx2_60l_moveit_config"), 'config', 'staubli_tx2_60l.urdf.xacro']),
            ' ',
            'sim:=', sim, ' '
        ])
    robot_description_clean = {'robot_description': robot_description_content}

    robot_description_semantic_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]), ' ',
            PathJoinSubstitution(
                [FindPackageShare("staubli_tx2_60l_moveit_config"), 'config', 'staubli_tx2_60l.srdf'])
        ])
    robot_description_semantic = {'robot_description_semantic': robot_description_semantic_content}

    kinematics_yaml = xacro.load_yaml(
        os.path.join(
            get_package_share_directory("staubli_tx2_60l_moveit_config"),
            "config",
            "kinematics.yaml",
        )
    )
    robot_description_kinematics = {'robot_description_kinematics': kinematics_yaml}

    # Trajectory execution functionality
    controllers_yaml = xacro.load_yaml(
        os.path.join(
            get_package_share_directory("staubli_tx2_60l_moveit_config"),
            "config",
            "staubli_tx2_60l_controllers.yaml",
        )
    )
    moveit_controllers = {
        "moveit_simple_controller_manager": controllers_yaml,
        "moveit_controller_manager": "moveit_simple_controller_manager/MoveItSimpleControllerManager",
    }
    trajectory_execution = {
        "moveit_manage_controllers": False,
        "trajectory_execution.execution_duration_monitoring": False,
        "trajectory_execution.allowed_execution_duration_scaling": 100.0,
        "trajectory_execution.allowed_goal_duration_margin": 0.5,
        "trajectory_execution.allowed_start_tolerance": 0.01,
    }
    planning_scene_monitor_parameters = {
        "publish_planning_scene": True,
        "publish_geometry_updates": True,
        "publish_state_updates": True,
        "publish_transforms_updates": True,
    }

    # Start the actual move_group node/action server
    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[robot_description_clean,
                    robot_description_semantic,
                    robot_description_kinematics,
                    trajectory_execution,
                    moveit_controllers,
                    planning_scene_monitor_parameters,
                    {"use_sim_time": True}],
        arguments=["--ros-args", "--log-level", "info"],
    )

    # RViz2
    rviz_base = os.path.join(get_package_share_directory("staubli_tx2_60l_moveit_config"), "config")
    rviz_full_config = os.path.join(rviz_base, "moveit.rviz")
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz_full_config],
        parameters=[
            robot_description_clean,
            robot_description_semantic,
            robot_description_kinematics,
            {"use_sim_time": True}
        ],
    )

    # Publish TF
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="both",
        parameters=[robot_description_clean, {"use_sim_time": True}],
    )

    # Gazebo Simulation
    gazebo = ExecuteProcess(
        cmd=['gazebo', '--verbose', 'worlds/empty.world', '-s', 'libgazebo_ros_factory.so', '-s', 'libgazebo_ros_init.so'],
        output='screen'
    )

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description', '-entity', 'staubli_tx2_60l', '-timeout', '120'],
        output='screen'
    )

    # Load controllers using Node (more reliable than shell=True ExecuteProcess)
    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_state_broadcaster', '--controller-manager', '/controller_manager',
                   '--controller-manager-timeout', '120'],
    )

    manipulator_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['manipulator_controller', '--controller-manager', '/controller_manager',
                   '--controller-manager-timeout', '120'],
    )

    return LaunchDescription(
        [
            sim_arg,
            gazebo,
            spawn_entity,
            rviz_node,
            robot_state_publisher,
            move_group_node,
            joint_state_broadcaster_spawner,
            manipulator_controller_spawner,
        ]
    )
