from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_moveit_rviz_launch


def generate_launch_description():
    tool = LaunchConfiguration("tool")
    moveit_config = (
        MoveItConfigsBuilder("staubli_tx40", package_name="staubli_tx40_moveit_config")
        .robot_description(
            file_path="config/staubli_tx40.urdf.xacro",
            mappings={"tool": tool},
        )
        .robot_description_semantic(
            file_path="config/staubli_tx40.srdf.xacro",
            mappings={"tool": tool},
        )
        .to_moveit_configs()
    )
    base_launch = generate_moveit_rviz_launch(moveit_config)
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "tool",
                default_value="none",
                description="End-effector tool to attach.",
            ),
            *base_launch.entities,
        ]
    )
