import os
import yaml
import tempfile
import xacro
from typing import Iterable, Text

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription, 
                            OpaqueFunction, SetLaunchConfiguration)
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.launch_context import LaunchContext
from launch.substitution import Substitution
from launch.some_substitutions_type import SomeSubstitutionsType
from launch_ros.parameter_descriptions import ParameterValue
from launch.launch_description_sources import PythonLaunchDescriptionSource

""" Fonction pour charger un fichier yaml. """
def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)
    try:
        with open(absolute_file_path) as file:
            return yaml.safe_load(file)
    except OSError:
        return None

""" Classe de substitution pour fusionner du texte (utile pour les namespaces) """
class TextJoinSubstitution(Substitution):
    def __init__(self, substitutions: Iterable[SomeSubstitutionsType], text: Text, sequence: Text) -> None:
        super().__init__()
        from launch.utilities import normalize_to_list_of_substitutions
        self.__substitutions = normalize_to_list_of_substitutions(substitutions)
        self.__text = text
        self.__sequence = sequence

    @property
    def substitutions(self) -> Iterable[Substitution]:
        return self.__substitutions

    def describe(self) -> Text:
        return "LocalVar('{}')".format(' + '.join([s.describe() for s in self.substitutions]))

    def perform(self, context: LaunchContext) -> Text:
        performed_substitutions = [sub.perform(context) for sub in self.__substitutions]
        return self.__sequence.join(performed_substitutions) + self.__sequence + self.__text

""" Fonction Opaque pour générer l'URDF et le YAML temporaire (Fix Gazebo Humble) """
def generate_urdf_and_params(context: LaunchContext):
    # Récupération des valeurs des arguments
    model_val = context.launch_configurations.get('model', 'tx2_60l')
    namespace_val = context.launch_configurations.get('namespace', '')
    sim_val = context.launch_configurations.get('sim', 'true')
    tool_val = context.launch_configurations.get('tool', 'none')
    verbose_val = context.launch_configurations.get('verbose', 'false')
    
    # Chemin vers le fichier xacro
    pkg_path = get_package_share_directory('staubli_tx2_60l_moveit_config')
    xacro_file = os.path.join(pkg_path, 'config', 'staubli_tx2_60l.urdf.xacro')

    # Exécution de xacro
    mappings = {
        'model': model_val,
        'namespace': namespace_val,
        'sim': sim_val,
        'tool': tool_val,
        'verbose': verbose_val
    }
    doc = xacro.process_file(xacro_file, mappings=mappings)
    urdf_string = doc.toxml()

    # 1. Création du fichier URDF temporaire (pour spawn_entity)
    temp_urdf = tempfile.NamedTemporaryFile(delete=False, mode='w', suffix='.urdf')
    temp_urdf.write(urdf_string)
    temp_urdf.close()

    # 2. Création du YAML temporaire pour les paramètres de Gazebo (Fix long string bug)
    gazebo_params_dict = {
        'gazebo_ros2_control': {
            'ros__parameters': {
                'robot_description': urdf_string
            }
        }
    }
    temp_yaml = tempfile.NamedTemporaryFile(delete=False, mode='w', suffix='.yaml')
    with open(temp_yaml.name, 'w') as f:
        yaml.dump(gazebo_params_dict, f)

    return [
        SetLaunchConfiguration('temp_urdf_path', temp_urdf.name),
        SetLaunchConfiguration('temp_yaml_path', temp_yaml.name),
        SetLaunchConfiguration('final_robot_description', urdf_string)
    ]

def generate_launch_description():
    declared_arguments = []

    # --- Arguments ---
    declared_arguments.append(DeclareLaunchArgument('model', default_value='tx2_60l'))
    declared_arguments.append(DeclareLaunchArgument('tool', default_value='none'))
    declared_arguments.append(DeclareLaunchArgument('namespace', default_value=''))
    declared_arguments.append(DeclareLaunchArgument('sim', default_value='true'))
    declared_arguments.append(DeclareLaunchArgument('verbose', default_value='false'))
    declared_arguments.append(DeclareLaunchArgument('ik_solver', default_value='kdl', choices=['kdl', 'pick_ik']))
    declared_arguments.append(DeclareLaunchArgument('robot_controller', default_value='manipulator_controller'))
    declared_arguments.append(DeclareLaunchArgument('controllers_file', default_value='ros2_controllers.yaml'))

    # --- Initialisation Configurations ---
    model = LaunchConfiguration('model')
    namespace = LaunchConfiguration('namespace')
    sim = LaunchConfiguration('sim')
    verbose = LaunchConfiguration('verbose')
    robot_controller = LaunchConfiguration('robot_controller')
    controllers_file = LaunchConfiguration('controllers_file')
    ik_solver = LaunchConfiguration('ik_solver')

    moveit_config_package = 'staubli_tx2_60l_moveit_config'
    
    # Action pour générer les fichiers temporaires
    setup_action = OpaqueFunction(function=generate_urdf_and_params)

    # Robot Description pour les nœuds ROS
    robot_description = {'robot_description': ParameterValue(LaunchConfiguration('final_robot_description'), value_type=str)}

    # SRDF
    robot_description_semantic_content = Command([
        PathJoinSubstitution([FindExecutable(name='xacro')]), ' ',
        PathJoinSubstitution([FindPackageShare(moveit_config_package), 'config', 'staubli_tx2_60l.srdf.xacro']), ' ',
        'model:=', model, ' namespace:=', namespace, ' tool:=', LaunchConfiguration('tool')
    ])
    robot_description_semantic = {'robot_description_semantic': ParameterValue(robot_description_semantic_content, value_type=str)}

    # Configuration MoveIt (YAMLs chargés en dictionnaires)
    kinematics_yaml = load_yaml(moveit_config_package, 'config/kinematics.yaml')
    robot_description_kinematics = {'robot_description_kinematics': kinematics_yaml}

    joint_limits_yaml = load_yaml(moveit_config_package, 'config/joint_limits.yaml')
    robot_description_planning = {'robot_description_planning': joint_limits_yaml}

    ompl_planning_yaml = load_yaml(moveit_config_package, 'config/ompl_planning.yaml')
    ompl_planning_pipeline_config = {'move_group': {'planning_plugin': 'ompl_interface/OMPLPlanner'}}
    omit_adapters = ' default_planner_request_adapters/AddTimeOptimalParameterization' \
                   ' default_planner_request_adapters/FixWorkspaceBounds' \
                   ' default_planner_request_adapters/FixStartStateBounds' \
                   ' default_planner_request_adapters/FixStartStateCollision' \
                   ' default_planner_request_adapters/FixStartStatePathConstraints'
    ompl_planning_pipeline_config['move_group']['request_adapters'] = omit_adapters
    ompl_planning_pipeline_config['move_group'].update(ompl_planning_yaml)

    moveit_controllers_yaml = load_yaml(moveit_config_package, 'config/moveit_controllers.yaml')
    moveit_controllers = {'moveit_controller_manager': 'moveit_simple_controller_manager/MoveItSimpleControllerManager'}

    # Solveur cinématique dynamique
    from launch.substitutions import PythonExpression
    kinematics_plugin_name = PythonExpression([
        "'pick_ik/PickIkPlugin' if '", ik_solver, "' == 'pick_ik' else 'kdl_kinematics_plugin/KDLKinematicsPlugin'"
    ])

    # --- Nodes ---

    move_group_node = Node(
        package='moveit_ros_move_group',
        executable='move_group',
        output='screen',
        parameters=[
            robot_description,
            robot_description_semantic,
            robot_description_kinematics,
            robot_description_planning,
            ompl_planning_pipeline_config,
            moveit_controllers,
            moveit_controllers_yaml,
            {'use_sim_time': sim},
            {'robot_description_kinematics.manipulator.kinematics_solver': kinematics_plugin_name}
        ])

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='both',
        parameters=[{'use_sim_time': sim}, robot_description])

    # Gazebo
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([PathJoinSubstitution([FindPackageShare('gazebo_ros'), 'launch', 'gazebo.launch.py'])]),
        condition=IfCondition(sim),
        launch_arguments={
            'verbose': verbose,
            'extra_gazebo_args': ['--ros-args ', '--params-file ', LaunchConfiguration('temp_yaml_path')]
        }.items())

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        condition=IfCondition(sim),
        arguments=['-file', LaunchConfiguration('temp_urdf_path'), '-entity', model],
        output='screen')

    robot_controllers_yaml = PathJoinSubstitution([
        FindPackageShare(moveit_config_package), 'config', controllers_file
    ])

    control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        condition=UnlessCondition(sim),
        parameters=[
            robot_description,
            robot_controllers_yaml
        ],
        output='screen')

    # Contrôleurs
    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_state_broadcaster', '--controller-manager', '/controller_manager'])

    robot_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[robot_controller, '-c', '/controller_manager'])

    # RViz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2_moveit',
        output='log',
        arguments=['-d', PathJoinSubstitution([FindPackageShare(moveit_config_package), 'config', 'moveit.rviz'])],
        parameters=[
            robot_description,
            robot_description_semantic,
            ompl_planning_pipeline_config,
            robot_description_kinematics,
            {'robot_description_kinematics.manipulator.kinematics_solver': kinematics_plugin_name}
        ])

    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0', '0', '0', '0', '0', '0', 'world', TextJoinSubstitution([namespace], 'base_link', '')])

    nodes_to_start = [
        setup_action,
        control_node,
        robot_state_publisher_node,
        joint_state_broadcaster_spawner,
        robot_controller_spawner,
        move_group_node,
        rviz_node,
        static_tf,
        gazebo,
        spawn_entity
    ]

    return LaunchDescription(declared_arguments + nodes_to_start)