import os
import yaml

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory


def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)
    try:
        with open(absolute_file_path, "r") as f:
            return yaml.safe_load(f)
    except OSError:
        return None


def generate_launch_description():
    # --- Arguments (same spirit as demo) ---
    declared_arguments = []

    declared_arguments.append(
        DeclareLaunchArgument("model", description="Denso robot model (e.g. vs060, cobotta, hsr065).")
    )
    declared_arguments.append(
        DeclareLaunchArgument("sim", default_value="true", description="Use simulated/fake hardware.")
    )
    declared_arguments.append(
        DeclareLaunchArgument("planning_group", default_value="arm", description="MoveIt planning group name.")
    )
    declared_arguments.append(
        DeclareLaunchArgument("velocity_scale", default_value="0.1", description="Max velocity scaling factor [0..1].")
    )
    declared_arguments.append(
        DeclareLaunchArgument("accel_scale", default_value="0.1", description="Max acceleration scaling factor [0..1].")
    )

    declared_arguments.append(
        DeclareLaunchArgument(
            "description_package",
            default_value="denso_robot_descriptions",
            description="Package containing URDF/XACRO files.",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "description_file",
            default_value="denso_robot.urdf.xacro",
            description="URDF/XACRO robot description file.",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "moveit_config_package",
            default_value="denso_robot_moveit_config",
            description="Package containing SRDF/XACRO files.",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "moveit_config_file",
            default_value="denso_robot.srdf.xacro",
            description="SRDF/XACRO semantic description file.",
        )
    )

    # --- Launch configs ---
    model = LaunchConfiguration("model")
    sim = LaunchConfiguration("sim")
    planning_group = LaunchConfiguration("planning_group")
    velocity_scale = LaunchConfiguration("velocity_scale")
    accel_scale = LaunchConfiguration("accel_scale")

    description_package = LaunchConfiguration("description_package")
    description_file = LaunchConfiguration("description_file")
    moveit_config_package = LaunchConfiguration("moveit_config_package")
    moveit_config_file = LaunchConfiguration("moveit_config_file")

    # --- Robot description (URDF) ---
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution([FindPackageShare(description_package), "urdf", description_file]),
            " ",
            "model:=",
            model,
            " ",
            "sim:=",
            sim,
            " ",
            "namespace:=''",
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    # --- Robot semantic description (SRDF) ---
    robot_description_semantic_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution([FindPackageShare(moveit_config_package), "srdf", moveit_config_file]),
            " ",
            "model:=",
            model,
            " ",
            "namespace:=''",
        ]
    )
    robot_description_semantic = {"robot_description_semantic": robot_description_semantic_content}

    # --- Kinematics (IK plugins config) ---
    kinematics_yaml = load_yaml("denso_robot_moveit_config", "config/kinematics.yaml")
    robot_description_kinematics = {"robot_description_kinematics": kinematics_yaml}

    # --- Node parameters for your motion server ---
    motion_server_params = {
        "model": model,
        "planning_group": planning_group,
        "velocity_scale": velocity_scale,
        "accel_scale": accel_scale,
    }

    motion_server_node = Node(
        package="denso_motion_control",
        executable="denso_motion_server",
        output="screen",
        parameters=[
            robot_description,
            robot_description_semantic,
            robot_description_kinematics,
            motion_server_params,
        ],
    )

    return LaunchDescription(declared_arguments + [motion_server_node])
