# ROS_2_ANDROID
Publishing data from Android via ROS 2

Once you have your Android application sending a data via socket, you are able to publish (talker) and subscriber (listener) via ROS 2.


## Dependencies: 

- [ROS 2 (dashing)](https://index.ros.org/doc/ros2/Installation/Dashing/)

## Building packages


Open the first terminal and source the ros:

```bash
source /opt/ros/dashing/setup.bash
```

```bash
cd $HOME
git clone https://github.com/mirellameelo/ROS_2_ANDROID.git
cd $HOME/ROS_2_ANDROID 

# Build the packages
colcon build --packages-select cpp_pubsub
. install/setup.bash

# run the talker
ros2 run cpp_pubsub talker

```

The publisher now is waiting for data comming via Socket

Open a new terminal to run the listener

```bash
source /opt/ros/dashing/setup.bash
cd $HOME/ROS_2_ANDROID 
. install/setup.bash

# run the listener
ros2 run cpp_pubsub listener
```



