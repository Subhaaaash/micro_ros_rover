# micro_ros_rover
Micro ros based rover with ROS2 foxy.

Follow this Github to build your own rover https://github.com/Subhaaaash/ESP-NOW_Rover.git

This project was done and tested on Ubuntu 20 with ROS2 Foxy.

---

1. INSTALL ROS2 FOXY
   
  (use this https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html)

  Enable Ubuntu Universe repository:
   ```bash
$ sudo apt install software-properties-common
$ sudo add-apt-repository universe 
```
  Add ROS 2 GPG key:
``` bash
$ sudo apt update && sudo apt install curl -y
$ sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```
  Add the repository to your sources list:

  ```bash
$ echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
$ sudo apt update
$ sudo apt upgrade
```
  Install Full Desktop version:
  
  ```bash
$ sudo apt install ros-foxy-desktop python3-argcomplete

```

  Setup environment (source your ROS 2):
  add this command to your bashrc file for convenience.

  ```bash
$ source /opt/ros/foxy/setup.bash

```
----

2. INSTALL MICRO ROS.

```bash
$ mkdir -p micro_ros_ws/ros && cd micro_ros_ws/ros
```
