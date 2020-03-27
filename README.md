# ROS_2_ANDROID

Receiving and publishing data from Android via ROS 2

Once you have one Android application sending data via socket, you will be able to publish (talker) and subscriber (listener) via ROS 2. In this repository, you can find a simple Android application to use as example. 

The video tutorial is available [here](https://www.youtube.com/watch?v=Z-lVEcqZvuM).

## Dependencies: 

- [ROS 2 (dashing)](https://index.ros.org/doc/ros2/Installation/Dashing/)

## Clonning the repository

```bash
cd $HOME
git clone https://github.com/mirellameelo/ROS_2_ANDROID.git
```

## Debug step (optional)

1) Open your Android Studio 
2) Open the project "my_places" 
3) Go to app->java->com.example.myplaces->MainActivity and **CHANGE the IP to your computer IP** (you can verify it when running ifconfig in the terminal)
4) Run the application in your phone 
5) Open the terminal and run:

```bash
cd $HOME/ROS_2_ANDROID/src
./a.out
```

Now, every time you click the connection button, you'll be able to see a variable incrementing. This indicates that the socket connection its working fine, and you're able to go to the next steps.

## Building ROS 2 package

Open the terminal and source the ROS:

```bash
source /opt/ros/dashing/setup.bash

# Build the packages
cd $HOME/ROS_2_ANDROID 
colcon build --packages-select cpp_pubsub
```

# ROS 2 and Android communication

#### Step 1: runnning the Android application in your phone
1) Open your Android Studio 
2) Open the project "my_places" 
3) Go to app->java->com.example.myplaces->MainActivity and **CHANGE the IP to your computer IP** (you can verify it when running ifconfig in the terminal)
4) Run the application in your phone 

#### Step 2: runnning the talker and listener

Open two terminals and source the cpp_pubsub setup file in both.

```bash
source $HOME/ROS_2_ANDROID/install/setup.bash
```

**Terminal_1**: Run the talker
```bash
#run the talker
ros2 run cpp_pubsub talker
```

The publisher now is waiting for data comming via Socket. 
**Terminal_2**:  Run the listener

```bash
# run the listener
ros2 run cpp_pubsub listener
```

