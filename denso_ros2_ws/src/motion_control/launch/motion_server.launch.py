import os
import yaml

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PythonExpression, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue # <--- Import crucial ici
from ament_index_python.packages import get_package_share_directory


def load_yaml(package_name, file_path):
    try:
        package_path = get_package_share_directory(package_name)
        absolute_file_path = os.path.join(package_path, file_path)
        with open(absolute_file_path, "r") as f:
            return yaml.safe_load(f)
    except (OSError, ValueError):
        return None


def generate_launch_description():
    declared_arguments = []

    declared_arguments.append(DeclareLaunchArgument("model", description="Robot model (e.g. vs060, staubli_tx2_60l)."))
    declared_arguments.append(DeclareLaunchArgument("sim", default_value="true", description="Use simulated/fake hardware."))
    declared_arguments.append(DeclareLaunchArgument("planning_group", default_value="", description="MoveIt planning group name."))
    declared_arguments.append(DeclareLaunchArgument("velocity_scale", default_value="0.1", description="Max velocity scaling factor [0..1]."))
    declared_arguments.append(DeclareLaunchArgument("accel_scale", default_value="0.1", description="Max acceleration scaling factor [0..1]."))
    declared_arguments.append(DeclareLaunchArgument("tool", default_value="none", description="End-effector tool to attach"))
    declared_arguments.append(DeclareLaunchArgument("ik_solver", default_value="pick_ik", choices=['kdl', 'pick_ik']))

    # --- Launch configs ---
    model = LaunchConfiguration("model")
    sim = LaunchConfiguration("sim")
    tool = LaunchConfiguration("tool")
    velocity_scale = LaunchConfiguration("velocity_scale")
    accel_scale = LaunchConfiguration("accel_scale")
    ik_solver = LaunchConfiguration("ik_solver")

    kinematics_plugin_name = PythonExpression([
        "'pick_ik/PickIkPlugin' if '", ik_solver, "' == 'pick_ik' else 'kdl_kinematics_plugin/KDLKinematicsPlugin'"
    ])

    # --- Dynamic Package & Folder Resolution ---
    is_staubli = PythonExpression(["'staubli' in '", model, "'"])
    
    # 1. URDF
    description_package = PythonExpression([
        "'staubli_tx2_60l_description' if 'staubli_tx2_60l' in '", model, "' else 'denso_robot_descriptions'"
    ])
    description_folder = "urdf"  # Stäubli et Denso utilisent tous les deux 'urdf' pour ce fichier
    description_file = PythonExpression([
        "'tx2_60l.xacro' if 'staubli_tx2_60l' in '", model, "' else 'denso_robot.urdf.xacro'"
    ])
    
    # 2. SRDF
    moveit_config_package = PythonExpression([
        "'staubli_tx2_60l_moveit_config' if 'staubli_tx2_60l' in '", model, "' else 'denso_robot_moveit_config'"
    ])
    srdf_folder = PythonExpression([
        "'config' if 'staubli_tx2_60l' in '", model, "' else 'srdf'"
    ])
    moveit_config_file = PythonExpression([
        "'staubli_tx2_60l.srdf' if 'staubli_tx2_60l' in '", model, "' else 'denso_robot.srdf.xacro'"
    ])
    
    # 3. Planning group
    planning_group_arg = LaunchConfiguration("planning_group")
    planning_group = PythonExpression([
        "'", planning_group_arg, "' if '", planning_group_arg, "' != '' else ('manipulator' if 'staubli' in '", model, "' else 'arm')"
    ])

    # --- Robot description (URDF) ---
    robot_description_content = ParameterValue(Command([
        PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
        PathJoinSubstitution([FindPackageShare(description_package), description_folder, description_file]), " ",
        "model:=", model, " ",
        "sim:=", sim, " ",
        "namespace:=''", " ",
        "tool:=", tool, " ",
    ]), value_type=str)
    robot_description = {"robot_description": robot_description_content}

    # --- Robot semantic description (SRDF) ---
    robot_description_semantic_content = ParameterValue(Command([
        PathJoinSubstitution([FindExecutable(name="xacro")]), " ",
        PathJoinSubstitution([FindPackageShare(moveit_config_package), srdf_folder, moveit_config_file]), " ",
        "model:=", model, " ",
        "namespace:=''", " ",
        "tool:=", tool, " ",
    ]), value_type=str)
    robot_description_semantic = {"robot_description_semantic": robot_description_semantic_content}

    # --- Kinematics ---
    denso_kinematics = load_yaml("denso_robot_moveit_config", "config/kinematics.yaml") or {}
    staubli_kinematics = load_yaml("staubli_tx2_60l_moveit_config", "config/kinematics.yaml") or {}

    motion_server_node = Node(
        package="motion_control",
        executable="motion_server",
        output="screen",
        parameters=[
            robot_description,
            robot_description_semantic,
            {"robot_description_kinematics": denso_kinematics},
            {"robot_description_kinematics": staubli_kinematics},
            {
                "model": model,
                "planning_group": planning_group,
                "velocity_scale": velocity_scale,
                "accel_scale": accel_scale,
                'robot_description_kinematics.arm.kinematics_solver': kinematics_plugin_name,
                'robot_description_kinematics.manipulator.kinematics_solver': kinematics_plugin_name
            }
        ],
    )

    return LaunchDescription(declared_arguments + [motion_server_node])