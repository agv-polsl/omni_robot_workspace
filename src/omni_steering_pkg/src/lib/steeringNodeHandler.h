// steeringNodeHandler.h
#ifndef STEERING_NODE_HANDLER_H // include guard
#define STEERING_NODE_HANDLER_H


#include <iostream>
#include "ros/ros.h"
#include <iostream>
#include "std_msgs/Float64.h"

namespace SNH{
    class steeringNodeHandler{
    private:
    void initializePublishers(ros::NodeHandle& n);
    public:
    // Joint topic names
    std::string left_joint_cmd_topic = "omni_robot/left_joint_velocity_controller/command";
    std::string right_joint_cmd_topic = "omni_robot/right_joint_velocity_controller/command";
    std::string back_joint_cmd_topic = "omni_robot/back_joint_velocity_controller/command";
    
    // Objects used for publishing data into specified topic 
    ros::Publisher VletfPub;
    ros::Publisher VrightPub;
    ros::Publisher VbackPub;

    // Messages using to publish velocity to joints
    std_msgs::Float64 VleftMsg;
    std_msgs::Float64 VrightMsg; 
    std_msgs::Float64 VbackMsg;

    steeringNodeHandler(ros::NodeHandle& n);

    void publishVelocities();

    void updateVelMsgs(double Vleft, double Vback, double Vright);

    void printVels();

    };
}


#endif /* STEERING_NODE_HANDLER_H */