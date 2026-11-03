#!/usr/bin/env python3
"""
Robot state publisher for the UFACTORY Lite 6.

Included by ufactory_lite6_planning_execution.launch.py through
moveit_configs_utils' generate_demo_launch, which includes this file by path
and passes no arguments: "sim", "tool" and "ip_address" are inherited from the
launch context of the parent.

The robot description mappings below MUST stay identical to the ones in
rsp.launch.py, move_group.launch.py and ufactory_lite6_planning_execution.launch.py.
If they drift, RViz and ros2_control end up driving two different robots.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_rsp_launch


def generate_launch_description():
    sim = LaunchConfiguration("sim")
    tool = LaunchConfiguration("tool")
    ip_address = LaunchConfiguration("ip_address")

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

    base_launch = generate_rsp_launch(moveit_config)
    return LaunchDescription(
        [
            DeclareLaunchArgument("sim", default_value="true"),
            DeclareLaunchArgument("tool", default_value="none"),
            DeclareLaunchArgument("ip_address", default_value="192.168.1.161"),
            *base_launch.entities,
        ]
    )
