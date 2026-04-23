import os
import yaml

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution, PythonExpression
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue
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
    # --- Arguments ---
    declared_arguments = [
        DeclareLaunchArgument("model", description="Robot model (e.g. vs060, cobotta, hsr065, tx2_60l, tx40)."),
        DeclareLaunchArgument("sim", default_value="true", description="Use simulated/fake hardware."),
        DeclareLaunchArgument("planning_group", default_value="", description="MoveIt planning group name."),
        DeclareLaunchArgument("velocity_scale", default_value="0.1", description="Max velocity scaling factor [0..1]."),
        DeclareLaunchArgument("accel_scale", default_value="0.1", description="Max acceleration scaling factor [0..1]."),
        DeclareLaunchArgument("tool", default_value="none", description="End-effector tool to attach (e.g., none, effecteur_v1)"),
        DeclareLaunchArgument("ik_solver", default_value="pick_ik", choices=['kdl', 'pick_ik']),
    ]

    # --- Launch configs (defined BEFORE any PythonExpression that uses them) ---
    model = LaunchConfiguration("model")
    sim = LaunchConfiguration("sim")
    tool = LaunchConfiguration("tool")
    velocity_scale = LaunchConfiguration("velocity_scale")
    accel_scale = LaunchConfiguration("accel_scale")
    ik_solver = LaunchConfiguration("ik_solver")
    planning_group_arg = LaunchConfiguration("planning_group")

    kinematics_plugin_name = PythonExpression([
        "'pick_ik/PickIkPlugin' if '", ik_solver, "' == 'pick_ik' else 'kdl_kinematics_plugin/KDLKinematicsPlugin'"
    ])

    # --- Dynamic Package & Folder Resolution ---
    # 1. URDF
    description_package = PythonExpression([
        "'staubli_tx40_description' if 'tx40' in '", model, "' else "
        "('staubli_tx2_60l_description' if 'tx2_60l' in '", model, "' else 'denso_robot_descriptions')"
    ])
    description_folder = "urdf"  # both robots use 'urdf/' for the URDF
    description_file = PythonExpression([
        "'tx40.xacro' if 'tx40' in '", model, "' else "
        "('tx2_60l.xacro' if 'tx2_60l' in '", model, "' else 'denso_robot.urdf.xacro')"
    ])

    # 2. SRDF
    moveit_config_package = PythonExpression([
        "'staubli_tx40_moveit_config' if 'tx40' in '", model, "' else "
        "('staubli_tx2_60l_moveit_config' if 'tx2_60l' in '", model, "' else 'denso_robot_moveit_config')"
    ])
    srdf_folder = PythonExpression([
        "'config' if ('tx2_60l' in '", model, "' or 'tx40' in '", model, "') else 'srdf'"
    ])
    moveit_config_file = PythonExpression([
        "'staubli_tx40.srdf' if 'tx40' in '", model, "' else "
        "('staubli_tx2_60l.srdf' if 'tx2_60l' in '", model, "' else 'denso_robot.srdf.xacro')"
    ])

    # 3. Planning group
    planning_group = PythonExpression([
        "'", planning_group_arg, "' if '", planning_group_arg,
        "' != '' else ('manipulator' if ('tx2_60l' in '", model, "' or 'tx40' in '", model, "') else 'arm')"
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

    # --- Kinematics (IK plugins config) ---
    denso_kinematics = load_yaml("denso_robot_moveit_config", "config/kinematics.yaml") or {}
    staubli_tx2_60l_kinematics = load_yaml("staubli_tx2_60l_moveit_config", "config/kinematics.yaml") or {}
    staubli_tx40_kinematics = load_yaml("staubli_tx40_moveit_config", "config/kinematics.yaml") or {}
    # Merge both kinematics maps so each planning group keeps its full solver settings.
    # Keys are distinct in this workspace ("arm" for DENSO, "manipulator" for Staubli).
    merged_kinematics = {}
    merged_kinematics.update(denso_kinematics)
    merged_kinematics.update(staubli_tx2_60l_kinematics)
    merged_kinematics.update(staubli_tx40_kinematics)

    # use_sim_time = ParameterValue(
    #     PythonExpression(["'tx2_60l' not in '", model, "'"]),
    #     value_type=bool,
    # )
    use_sim_time = True

    use_health_monitor = ParameterValue(
        PythonExpression(["not ('tx2_60l' in '", model, "' or 'tx40' in '", model, "')"]),
        value_type=bool,
    )

    motion_server_node = Node(
        package="motion_control",
        executable="motion_server",
        output="screen",
        parameters=[
            robot_description,
            robot_description_semantic,
            {"use_sim_time": use_sim_time},
            {"use_health_monitor": use_health_monitor},
            {"robot_description_kinematics": merged_kinematics},
            {
                "model": model,
                "planning_group": planning_group,
                "velocity_scale": velocity_scale,
                "accel_scale": accel_scale,
                "ik_solver": ik_solver,
                "ik_solver_plugin": kinematics_plugin_name,
                # Backward-compatible aliases for external clients expecting generic keys
                "solver": ik_solver,
                "solver_plugin": kinematics_plugin_name,
                "kinematics_solver": kinematics_plugin_name,
                'robot_description_kinematics.arm.kinematics_solver': kinematics_plugin_name,
                'robot_description_kinematics.manipulator.kinematics_solver': kinematics_plugin_name,
            }
        ],
    )

    return LaunchDescription(declared_arguments + [motion_server_node])
