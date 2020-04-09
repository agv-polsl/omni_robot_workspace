#include "steeringNodeHandler.h"
using namespace SNH;
  void steeringNodeHandler::initializePublishers(ros::NodeHandle& n){
    this->VletfPub = n.advertise<std_msgs::Float64>(left_joint_cmd_topic, 1000);
    this->VrightPub = n.advertise<std_msgs::Float64>(right_joint_cmd_topic, 1000);
    this->VbackPub = n.advertise<std_msgs::Float64>(back_joint_cmd_topic, 1000);
  }
  
  steeringNodeHandler::steeringNodeHandler(ros::NodeHandle& n){
    this->initializePublishers(n);
    this->VleftMsg.data = 0.0;
    this->VrightMsg.data = 0.0;
    this->VbackMsg.data = 0.0;
  }

  void steeringNodeHandler::publishVelocities(){
    VletfPub.publish(this->VleftMsg);
    VrightPub.publish(this->VrightMsg);
    VbackPub.publish(this->VbackMsg);
  }

  void steeringNodeHandler::updateVelMsgs(double Vleft, double Vback, double Vright){
    this->VleftMsg.data = Vleft;
    this->VrightMsg.data = Vright;
    this->VbackMsg.data = Vback;
  }

  void steeringNodeHandler::printVels(){
    ROS_ERROR_STREAM("Vleft: " << this->VleftMsg.data);
    ROS_ERROR_STREAM("Vright: "<< this->VrightMsg.data);
    ROS_ERROR_STREAM("Vback: " << this->VbackMsg.data);
  }
