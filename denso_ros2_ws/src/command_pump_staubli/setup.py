from setuptools import find_packages, setup

package_name = 'command_pump_staubli'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml', 'README.md']),
        ('share/' + package_name + '/launch', ['launch/staubli_pump_valve.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Antonin',
    maintainer_email='antonin@todo.com',
    description='ROS2 services to command Staubli pump and valves through WRITE_SINGLE_IO.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'staubli_pump_valve_node = command_pump_staubli.staubli_pump_valve_node:main',
        ],
    },
)
