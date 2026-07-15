from setuptools import find_packages
from setuptools import setup

setup(
    name='t3_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('t3_interfaces', 't3_interfaces.*')),
)
