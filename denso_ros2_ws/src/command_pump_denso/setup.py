from setuptools import find_packages, setup

package_name = 'command_pump_denso'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/pump_controller.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Antonin',
    maintainer_email='antonin@todo.com',
    description='Configurable vacuum pump and valve controller for DENSO robots via Mini I/O',
    license='MIT',
    entry_points={
        'console_scripts': [
            'pump_controller_node = command_pump_denso.pump_controller_node:main',
        ],
    },
)
