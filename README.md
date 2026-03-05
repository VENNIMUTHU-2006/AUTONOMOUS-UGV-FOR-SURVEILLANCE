# Team12 AMR – ROS2 Simulation, Mapping and Navigation

## Project Overview

The **Team12 Autonomous Mobile Robot (AMR)** project focuses on designing, simulating, mapping, and navigating a differential drive robot using **ROS2**, **Gazebo**, and **SLAM Toolbox**.

The robot is simulated in a custom **two-room indoor environment** containing obstacles. The robot uses a **LiDAR sensor** for environment perception and builds a map using **SLAM (Simultaneous Localization and Mapping)**.

After mapping, the robot can be extended to perform **autonomous navigation between Room A and Room B** using the **Nav2 Navigation Stack**.

This project demonstrates a complete **AMR development pipeline**, including:

* Robot modeling (URDF/XACRO)
* Simulation (Gazebo)
* Sensor integration (LiDAR)
* Teleoperation
* Mapping (SLAM)
* Navigation (future stage)
* Hardware architecture for real robot implementation

---

# System Architecture

The system architecture consists of simulation, perception, control, and navigation layers.

```
Robot Hardware / Simulation
        │
        │
   LiDAR Sensor
        │
        ▼
   LaserScan (/scan)
        │
        ▼
   SLAM Toolbox
        │
        ▼
        Map (/map)
        │
        ▼
   Navigation Stack (Nav2)
        │
        ▼
 Autonomous Movement
```

---

# Software Stack

| Component             | Description                  |
| --------------------- | ---------------------------- |
| Ubuntu                | Operating system             |
| ROS2 Humble           | Robotics middleware          |
| Gazebo                | Robot simulation environment |
| RViz2                 | Visualization tool           |
| SLAM Toolbox          | Mapping algorithm            |
| Teleop Twist Keyboard | Manual robot control         |
| Nav2                  | Autonomous navigation stack  |

---

# Robot Specifications

## Robot Type

Differential Drive Mobile Robot

## Physical Parameters

| Parameter        | Value  |
| ---------------- | ------ |
| Robot Length     | 0.46 m |
| Robot Width      | 0.30 m |
| Wheel Diameter   | 0.20 m |
| Wheel Separation | 0.30 m |
| Number of Wheels | 4      |

## Sensors

| Sensor                  | Purpose                |
| ----------------------- | ---------------------- |
| LiDAR                   | Environment perception |
| Wheel encoders (future) | Odometry               |

---

# Hardware Architecture (Real Robot)

The physical robot system uses the following hardware components.

| Component              | Purpose                    |
| ---------------------- | -------------------------- |
| Raspberry Pi           | Main ROS controller        |
| BTS7960 Motor Driver   | High current motor control |
| 12V Johnson Motors (4) | Robot propulsion           |
| 12.7V 30Ah Battery     | Power supply               |
| LiDAR Sensor           | Environment scanning       |

## Power Architecture

```
Battery (12.7V 30Ah)
        │
        ├── BTS7960 Motor Drivers
        │        │
        │        └── DC Motors
        │
        ├── Buck Converter (12V → 5V)
        │        │
        │        └── Raspberry Pi
        │
        └── LiDAR Sensor
```

---

# Project Directory Structure

```
muh_ws/
│
├── src/
│   └── team12_description/
│        │
│        ├── launch/
│        │     gazebo.launch.py
│        │
│        ├── urdf/
│        │     team12_amr.xacro
│        │
│        ├── worlds/
│        │     two_room.world
│        │
│        ├── meshes/
│        │     chassis.stl
│        │
│        └── package.xml
│
├── build/
├── install/
└── log/
```

---

# Simulation Environment

The Gazebo simulation environment contains:

* **Room A**
* **Room B**
* **Doorway between rooms**
* **Multiple obstacles**

The environment is used for **SLAM mapping and navigation testing**.

```
Room A  → Doorway → Room B
```

---

# Building the Workspace

Navigate to the ROS workspace:

```bash
cd ~/Documents/muh_ws
```

Clean the workspace:

```bash
rm -rf build install log
```

Build the project:

```bash
colcon build --symlink-install
```

Source the workspace:

```bash
source install/setup.bash
```

---

# Launching the Simulation

Start Gazebo with the robot model.

```bash
ros2 launch team12_description gazebo.launch.py
```

This will start:

* Gazebo simulator
* Robot model
* LiDAR sensor
* Differential drive controller

---

# Verifying Robot Topics

Check available topics:

```bash
ros2 topic list
```

Important topics:

```
/cmd_vel
/odom
/scan
/tf
/tf_static
```

---

# Starting SLAM Mapping

Launch SLAM Toolbox:

```bash
ros2 launch slam_toolbox online_async_launch.py use_sim_time:=true
```

SLAM Toolbox processes LiDAR data and generates a map.

---

# Starting RViz Visualization

Launch RViz:

```bash
rviz2
```

Set:

```
Fixed Frame → map
```

Add the following displays:

* Map
* LaserScan
* TF
* RobotModel

Topics:

```
/scan
/map
```

---

# Teleoperation (Manual Control)

Control the robot using the keyboard.

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

## Keyboard Controls

```
u    i    o
j    k    l
m    ,    .
```

| Key | Action        |
| --- | ------------- |
| i   | Move forward  |
| ,   | Move backward |
| j   | Rotate left   |
| l   | Rotate right  |
| u   | Forward left  |
| o   | Forward right |
| k   | Stop          |

---

# Mapping Procedure

To generate a good map, follow these steps:

1. Drive around **Room A perimeter**
2. Move around **obstacles**
3. Navigate through **doorway**
4. Map **Room B**
5. Perform **zig-zag motion** inside both rooms

This ensures the LiDAR observes all surfaces.

---

# Map Generation

During mapping, RViz will display:

| Color | Meaning           |
| ----- | ----------------- |
| Black | Walls / obstacles |
| White | Free space        |
| Gray  | Unknown space     |

---

# Saving the Map

Once mapping is complete:

```bash
ros2 run nav2_map_server map_saver_cli -f team12_map
```

Generated files:

```
team12_map.yaml
team12_map.pgm
```

These files will be used for navigation.

---

# Autonomous Navigation (Future Work)

After mapping, the robot will use **Nav2** for navigation.

Capabilities include:

* Localization using AMCL
* Path planning
* Obstacle avoidance
* Waypoint navigation

Example use case:

```
Room A → Room B autonomous delivery
```

---

# Troubleshooting

## Gazebo Already Running

```
Address already in use
```

Fix:

```bash
killall -9 gzserver gzclient gazebo
```

---

## Robot Not Moving

Check velocity commands:

```bash
ros2 topic echo /cmd_vel
```

---

## LiDAR Not Publishing

Check sensor topic:

```bash
ros2 topic echo /scan
```

---

# Future Improvements

* Integrate **Nav2 navigation stack**
* Implement **AMCL localization**
* Add **real hardware deployment**
* Integrate **camera-based perception**
* Implement **autonomous task execution**

---

# Conclusion

The **Team12 AMR project** demonstrates a complete robotic system pipeline using ROS2:

* Robot modeling
* Simulation
* Sensor integration
* SLAM mapping
* Teleoperation
* Autonomous navigation

This system can be extended to operate as a **warehouse robot, inspection robot, or delivery robot**.

---

# Author

Team 12 - 
Surendhar
Sanjay
Boopathy
Venni
Sampaul
Sundhar
Jayamani
