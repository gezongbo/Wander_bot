#include "Wander.h"
int main(int argc, char **argv)
{
    // Initiate new ROS node named wander_bot
    ros::init(argc, argv, "wander_bot");
    // Create new wander object
    Wander wander;
    // Start the movement
    wander.startMoving();
    return 0;
}
