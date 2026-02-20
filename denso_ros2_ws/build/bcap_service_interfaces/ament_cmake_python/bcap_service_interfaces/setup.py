from setuptools import find_packages
from setuptools import setup

setup(
    name='bcap_service_interfaces',
    version='1.2.0',
    packages=find_packages(
        include=('bcap_service_interfaces', 'bcap_service_interfaces.*')),
)
