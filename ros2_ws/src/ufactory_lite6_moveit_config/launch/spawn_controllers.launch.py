#!/usr/bin/env python3
"""
Spawns the controllers listed in config/moveit_controllers.yaml
(lite6_traj_controller) plus joint_state_broadcaster.

generate_spawn_controllers_launch only reads the controller names out of the
trajectory_execution configuration, so the robot description is never actually
evaluated here. The paths are still given explicitly because to_moveit_configs()
fills in anything left unset, and its fallback for the SRDF is
config/<robot_name>.srdf — a plain .srdf this package does not ship, which it
would then try to read eagerly and fail on.
"""

from launch import LaunchDescription
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_spawn_controllers_launch


def generate_launch_description() -> LaunchDescription:
    moveit_config = (
        MoveItConfigsBuilder("ufactory_lite6", package_name="ufactory_lite6_moveit_config")
        .robot_description(file_path="config/ufactory_lite6.urdf.xacro")
        .robot_description_semantic(file_path="config/ufactory_lite6.srdf.xacro")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .planning_pipelines(pipelines=["ompl", "pilz_industrial_motion_planner"])
        .to_moveit_configs()
    )
    return generate_spawn_controllers_launch(moveit_config)
