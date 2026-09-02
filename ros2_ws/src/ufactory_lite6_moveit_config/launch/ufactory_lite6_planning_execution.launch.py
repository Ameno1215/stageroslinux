#!/usr/bin/env python3
"""
TERMINAL_1 of the stack for the UFACTORY Lite 6.

Brings up robot_state_publisher, ros2_control (vendor fake hardware in
simulation, the real UFACTORY hardware interface otherwise), move_group and
RViz — the same role staubli_tx40_planning_execution_sim.launch.py plays for the
Staubli, and it follows that file's structure deliberately.

    ros2 launch ufactory_lite6_moveit_config ufactory_lite6_planning_execution.launch.py \
        sim:=true tool:=none

Pilz is loaded as a second planning pipeline: motion_control's planCartesianLin
and /sequence_move_group need MoveGroupSequenceAction/Service (contract C7).
The capabilities themselves are passed by launch_controller.py through the
"capabilities" argument that generate_demo_launch declares, exactly as for the
Staubli.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch


def _launch_setup(context):
    tool = LaunchConfiguration("tool").perform(context)
    sim = LaunchConfiguration("sim").perform(context)
    ip_address = LaunchConfiguration("ip_address").perform(context)

    moveit_config = (
        MoveItConfigsBuilder("ufactory_lite6", package_name="ufactory_lite6_moveit_config")
        .robot_description(
            file_path="config/ufactory_lite6.urdf.xacro",
            mappings={
                "model": "ufactory_lite6",
                "namespace": "",
                "sim": sim,
                "tool": tool,
                "ip_address": ip_address,
            },
        )
        .robot_description_semantic(
            file_path="config/ufactory_lite6.srdf.xacro",
            mappings={
                "model": "ufactory_lite6",
                "namespace": "",
                "tool": tool,
            },
        )
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .planning_pipelines(pipelines=["ompl", "pilz_industrial_motion_planner"])
        .to_moveit_configs()
    )

    return generate_demo_launch(moveit_config).entities


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "sim",
                default_value="true",
                description="true: vendor fake hardware. false: connect to the real Lite 6.",
            ),
            DeclareLaunchArgument(
                "tool",
                default_value="none",
                description="End-effector tool to attach (none, effecteur_v1..v3).",
            ),
            DeclareLaunchArgument(
                "ip_address",
                default_value="192.168.1.161",
                description="IP address of the Lite 6 controller (ignored when sim:=true).",
            ),
            OpaqueFunction(function=_launch_setup),
        ]
    )
