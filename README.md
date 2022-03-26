# Wander_bot
ROS Gazebo仿真 控制Turtlebots实现扫地机器人算法

1.Problem background
The aim of this assignment is to give you a way in to writing software for controlling a (simulated) robot using the Robot Operating System (ROS).
In this assignment you will create a ROS node to drive the robot around with a simple wanderer algorithm, very like a ‘Roomba’ robot vacuum cleaner. The robot should move forward until it reaches an obstacle, then rotate in the same position until the way ahead is clear, then move forward again and repeat.

2.Creating a wander_bot Package
In ROS, the programs organized as packages. So, we have to create a ROS package before writing any program. To create a ROS package, we have to give a name of the package,then the dependent packages which help to compile the programs inside the package.
For example, if your package has C++ program, you have to add ‘roscpp’ as dependency.
Before creating the package, first switch to the src folder.

$ cd ~/catkin_ws/src
$ catkin_create_pkg wander_bot roscpp rospy std_msgs
Figure 1 shows the output when we execute this command.
Figure 1. Creating the Package
Figure 1. Creating the Package

3.Creating a Wander.h

4.Creating a Wander.cpp

5.Creating a ROS wander_bot Node

6.Editing the CMakeLists.txt File
After saving the two files in the wander_bot/src folder, the nodes need to be compiled to create the executable. To do this, we have to edit the CMakeLists.txt file, which is not too complicated. We need to add four lines of code to CMakeLists.txt.
Figure 2 shows the additional lines of code to insert (Line 128 - 129)
在这里插入图片描述

Figure 2. Changes to the CMakeLists.txt file (Line 128-129)

7.Building C++ Nodes
After saving CMakeLists.txt, we can build the source code. The command to build the nodes is catkin_make. Just switch to the workspace folder and execute the catkin_make command.
To switch to the catkin_ws folder, assume that the workspace is in the home folder.

$ cd ~/catkin_ws
Executing the catkin_make command to build the nodes

$ catkin_make --pkg wander_bot
If everything is correct, you get a message saying that the build was successful (see Figure 3).
在这里插入图片描述

Figure 3.Building Successful
So we have successfully built the nodes. Now what? We can execute these nodes, right? That is covered in the next section.

8.Creating Launch Files
<launch>
    <param name="/use_sim_time" value="true" />
    <!-- Launch turtlebot3 world -->
    <include file="$(find turtlebot3_gazebo)/launch/turtlebot3_world.launch"/>
    <!-- Launch stopper node -->
    <node name="wander_bot" pkg="wander_bot" type="wander_bot" output="screen"/>
</launch>
The following is the command to execute this launch file. We can execute it from any terminal path.

$ roslaunch wander_bot wander_bot.launch
After the roslaunch command, use the package name and then the launch file name
在这里插入图片描述

Figure 4. Talker and Listener working together

9.Visualising a Computing Graph
The rqt_graph GUI tool visualises the ROS computation graph. Use any of the launch files that we created in the previous section.

$ roslaunch wonder_bot wonder_bot.launch
And in another terminal, run the following.

$ rqt_graph
Figure 5 shows the output of this GUI tool.
在这里插入图片描述

Figure 5. ROS Graph
Check the list of ROS topics in the system by using the following command.

$ rostopic list
在这里插入图片描述

Figure 6. Rostopic List

效果视频

wander

视频地址
