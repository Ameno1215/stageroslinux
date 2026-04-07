from setuptools import find_packages, setup

package_name = 'isaac_joint_trajectory_bridge'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/follow_joint_trajectory_bridge.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Antonin',
    maintainer_email='antonin@todo.com',
    description='Bridge MoveIt FollowJointTrajectory actions to Isaac Sim joint_command JointState messages.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'follow_joint_trajectory_bridge = isaac_joint_trajectory_bridge.follow_joint_trajectory_bridge:main',
            'joint_state_relay = isaac_joint_trajectory_bridge.joint_state_relay:main',
        ],
    },
)
