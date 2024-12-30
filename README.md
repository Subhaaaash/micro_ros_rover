# micro_ros_rover
Micro ros based rover with ROS2 foxy.



https://github.com/user-attachments/assets/3c8428d1-d1d7-4376-b827-90f4396b3172


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

2. INSTALL MICRO ROS AND TELEOP:

   Teleop keyboard: https://index.ros.org/p/teleop_twist_keyboard/github-ros2-teleop_twist_keyboard/
   
   micro ros agent: https://micro.ros.org/docs/tutorials/core/first_application_linux/

```bash
$ mkdir -p micro_ros_ws/src && cd micro_ros_ws/src
$ git clone https://github.com/micro-ROS/micro-ROS-Agent.git -b foxy
$ git clone https://github.com/ros2/teleop_twist_keyboard.git
$ sudo apt update && rosdep update
$ cd ..
$ rosdep install --from-paths src --ignore-src -y
$ colcon build --symlink-intsall
$ source install/local_setup.bash
```

----
3. FLASH THE CODE micro_ros_ros_v1.ino INTO TO THE ROVER USING ARDUINO IDE:
   
   3.1 INCLUDE THIS LIBRARY IN THE ARDUINO IDE:
   
   https://github.com/micro-ROS/micro_ros_arduino.git

   Download the zip file from this github and include the library in arduino ide.
      
   ```bash
   REPLACE WITH YOUR NETWORK CREDENTIALS
   set_microros_wifi_transports("your_SSID", "network_password", "192.168.0.110(your host ros2 device ip)", 8888); //fill in your network credentials\
   ```
   Once the code is flashed power up your rover.

   ----

5. LAUNCH MICRO ROS AGENT AND TELEOP:

   In the first terminal.

   ```bash
   $ ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
   ```

   In the second terminal.

   ```bash
   $ ros2 run teleop_twist_keyboard teleop_twist_keyboard
   ```

   Power up the rover and control it with keyboard.

   
![IMG_6208](https://github.com/user-attachments/assets/8451d827-28dd-4241-abd6-228c36012e90)


