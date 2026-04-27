from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch


def _launch_setup(context):
    tool = LaunchConfiguration("tool").perform(context)
    moveit_config = (
        MoveItConfigsBuilder("staubli_tx2_60l", package_name="staubli_tx2_60l_moveit_config")
        .robot_description(
            file_path="config/staubli_tx2_60l.urdf.xacro",
            mappings={"tool": tool},
        )
        .robot_description_semantic(
            file_path="config/staubli_tx2_60l.srdf.xacro",
            mappings={"tool": tool},
        )
        .to_moveit_configs()
    )
    demo_launch = generate_demo_launch(moveit_config)
    return demo_launch.entities


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "tool",
                default_value="none",
                description="End-effector tool to attach.",
            ),
            OpaqueFunction(function=_launch_setup),
        ]
    )
