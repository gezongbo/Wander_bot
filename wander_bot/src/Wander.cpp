#include "Wander.h"
#include "geometry_msgs/Twist.h"

#include<stdlib.h>  //random number
#include<time.h>
#define random(x) (rand()%x)



Wander::Wander()
{
    keepMoving = true;
    keepMoving0=true;
    getRandom = false;
    // Advertise a new publisher for the robot~s velocity command topic
    commandPub = node.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    // Subscribe to the simulated robot~s laser scan topic
    laserSub = node.subscribe("/scan", 1, &Wander::scanCallback, this);
}
// Send a velocity command
void Wander::moveForward()
{
    geometry_msgs::Twist msg; // The default constructor will set all commands to 0
    msg.linear.x = FORWARD_SPEED;
    ROS_INFO("SPEED : % f", msg.linear.x);
    commandPub.publish(msg);
}

void Wander::turnCorner()
{
    static geometry_msgs::Twist msg; // The default constructor will set all commands to 0
    if(keepMoving0==1 && keepMoving==0)
    getRandom = 1;
    else
    getRandom = 0;

    if(getRandom)   //If you are turning, you do not need to regenerate random numbers, only the first moment of turning generates random numbers
    {
        angular_velocity = (random(100)-50)/25.0;
        msg.angular.z = angular_velocity;
    }
    ROS_INFO("Angular velocity : % f", msg.angular.z);
    commandPub.publish(msg);
}

// Process the incoming laser scan message
void Wander::scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan)
{
    keepMoving0 = keepMoving;
    bool isObstacleInFront = false; //是前面的障碍物吗
    keepMoving = true;
    // Find the closest range between the defined minimum and maximum angles

    
    int minIndex = 360 + floor((MIN_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    //floor() rounds down
    //Change the radian system to 360 degree system, here minndex is 345 degrees when MIN_SCAN_ANGLE = -15.0 / 180 * M_PI
    //Function: Returns the largest integer less than the incoming parameter
    int maxIndex = floor((MAX_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    //Function: scan->angle_min indicates the rad that starts during the actual scan
    
    std::vector<std::pair<float, float>> scaled_ranges;
    //pair is to combine 2 data into one data
    for (int i = minIndex; i < 360; i++)
        scaled_ranges.push_back(std::make_pair(i, scan->ranges[i]));//make_pair integrated into a container
    for (int i = 0; i <= maxIndex; i++)
        scaled_ranges.push_back(std::make_pair(i, scan->ranges[i]));
    for (auto value : scaled_ranges)
    {
        // std::cout << value.first << ":" << value.second << ",";
        //Should be the first and second value of value
        //The first value represents the angle 345-15 and the second represents the distance
        if (value.second < MIN_DIST_FROM_OBSTACLE)
        {
            keepMoving = false;
            ROS_INFO("Turn a corner!");
            break;
        }
    }
    
     //std::cout << std::endl;
}


void Wander::startMoving()
{
    srand((int)time(0));

    ros::Rate rate(10);
    ROS_INFO("Start moving");
    // Keep spinning loop until user presses Ctrl+C or the robot got too close to an obstacle
    while (ros::ok())
    {
        // Need to call this function often to allow ROS to process incoming messages
        ros::spinOnce();
        
        if (false == keepMoving)
            turnCorner();
        else
            moveForward();
        
        rate.sleep();
    }
}

