from setuptools import find_packages
from setuptools import setup

setup(
    name='denso_robot_core_interfaces',
    version='1.2.0',
    packages=find_packages(
        include=('denso_robot_core_interfaces', 'denso_robot_core_interfaces.*')),
)
