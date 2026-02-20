from setuptools import find_packages
from setuptools import setup

setup(
    name='denso_motion_control',
    version='0.0.0',
    packages=find_packages(
        include=('denso_motion_control', 'denso_motion_control.*')),
)
