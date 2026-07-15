"""Mission 2 pipeline: frame client + pose estimator + RViz.

    ros2 launch t3_pose_estimation mission2.launch.py \
        server_url:=http://127.0.0.1:5000 use_rviz:=true
"""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    share = get_package_share_directory('t3_pose_estimation')
    params = os.path.join(share, 'config', 'params.yaml')
    default_calib = os.path.join(share, 'config', 'camera_synthetic.yaml')
    rviz_cfg = os.path.join(share, 'rviz', 't3_mission2.rviz')

    server_url = LaunchConfiguration('server_url')
    calib_file = LaunchConfiguration('calib_file')
    use_rviz = LaunchConfiguration('use_rviz')

    return LaunchDescription([
        DeclareLaunchArgument(
            'server_url', default_value='http://127.0.0.1:5000',
            description='Competition/mock server base URL'),
        DeclareLaunchArgument(
            'calib_file', default_value=default_calib,
            description='OpenCV yaml with camera_matrix/distortion_coefficients'),
        DeclareLaunchArgument('use_rviz', default_value='true'),

        Node(
            package='t3_pose_estimation',
            executable='pose_estimator_node',
            output='screen',
            parameters=[params, {'calib_file': calib_file}],
        ),
        Node(
            package='t3_pose_estimation',
            executable='frame_client_node',
            output='screen',
            parameters=[params, {'server_url': server_url}],
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            arguments=['-d', rviz_cfg],
            output='log',
            condition=IfCondition(use_rviz),
        ),
    ])
