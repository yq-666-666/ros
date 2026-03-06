import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_share = get_package_share_directory('dog_urdf')
    urdf_path = os.path.join(pkg_share, 'urdf', 'dog.urdf')
    rviz_config_path = os.path.join(pkg_share, 'rviz', 'dog_rviz.rviz')
    with open(urdf_path, 'r', encoding='utf-8') as urdf_file:
        robot_description = urdf_file.read()

    robot_state_pub = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}]
    )

    joint_state_pub_gui = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui'
    )

    rviz2_node = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config_path]
    )

    return LaunchDescription([
        robot_state_pub,
        joint_state_pub_gui,
        rviz2_node
    ])