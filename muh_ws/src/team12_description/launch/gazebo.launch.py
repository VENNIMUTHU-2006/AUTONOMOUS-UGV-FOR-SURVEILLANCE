from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction
from launch_ros.actions import Node
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    pkg_path = get_package_share_directory('team12_description')

    world_file = os.path.join(pkg_path, 'worlds', 'two_room.world')
    urdf_file = os.path.join(pkg_path, 'urdf', 'team12_amr.xacro')

    return LaunchDescription([

        # -----------------------------
        # Start Gazebo WITH ROS CLOCK
        # -----------------------------
        ExecuteProcess(
            cmd=[
                'gazebo',
                '--verbose',
                world_file,
                '-s', 'libgazebo_ros_init.so',      # ✅ publishes /clock
                '-s', 'libgazebo_ros_factory.so'
            ],
            output='screen'
        ),

        # -----------------------------
        # Robot State Publisher
        # -----------------------------
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{
                'robot_description': Command(['xacro ', urdf_file])
            }],
            output='screen'
        ),

        # -----------------------------
        # Spawn Robot in Gazebo
        # -----------------------------
        TimerAction(
            period=3.0,
            actions=[
                Node(
                    package='gazebo_ros',
                    executable='spawn_entity.py',
                    arguments=[
                        '-topic', 'robot_description',
                        '-entity', 'team12_robot',
                        '-x', '0.0',
                        '-y', '0.0',
                        '-z', '0.6'
                    ],
                    output='screen'
                )
            ]
        )

    ])
