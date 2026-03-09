import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration, Command, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue

def launch_setup(context, *args, **kwargs):
    # 1. Récupérer la valeur des arguments sous forme de texte
    robot_model = LaunchConfiguration('robot_model').perform(context)
    use_sim = LaunchConfiguration('use_sim').perform(context)

    # 2. Construire le chemin vers le fichier Xacro dynamiquement
    description_pkg = FindPackageShare('staubli_robot_description')
    
    # Chemin : staubli_robot_description/urdf/<robot_model>/<robot_model>.xacro
    xacro_file = PathJoinSubstitution([
        description_pkg,
        'urdf',
        robot_model,
        f'{robot_model}.xacro' 
    ])

    # 3. Générer l'URDF via la commande xacro en lui passant l'argument de simulation
    robot_description_content = Command([
        'xacro ', xacro_file, ' use_mock_hardware:=', use_sim
    ])
    robot_description = {
        'robot_description': ParameterValue(robot_description_content, value_type=str)
    }

    # 4. Définir les nœuds à lancer
    # Le robot_state_publisher publie la position des liens (TF)
    robot_state_pub_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )

    rviz_config = PathJoinSubstitution([
        description_pkg, 
        'rviz', 
        f'view_{robot_model}.rviz' 
    ])
    
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config],
        output='screen'
    )

    # On retourne la liste des nœuds à lancer
    return [
        robot_state_pub_node,
        rviz_node
    ]

def generate_launch_description():
    # Déclaration des arguments de lancement
    return LaunchDescription([
        DeclareLaunchArgument(
            'robot_model',
            default_value='tx2_60l',
            description='Modèle du robot Staubli (ex: tx2_60l, tx40)'
        ),
        DeclareLaunchArgument(
            'use_sim',
            default_value='true',
            description='Utiliser mock_hardware (true) ou le vrai robot (false)'
        ),
        # L'OpaqueFunction permet d'évaluer le contexte avant de lancer les nœuds
        OpaqueFunction(function=launch_setup)
    ])