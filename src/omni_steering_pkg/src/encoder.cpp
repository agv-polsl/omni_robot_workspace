#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32.h>
#include <omni_steering_pkg/omni_velocity.h>

ros::Publisher js_publisher;

long double lw_pos_current; // left wheel position
long double bw_pos_current; // back wheel position
long double rw_pos_current; // right wheel position
long double lw_pos_prev;
long double bw_pos_prev;
long double rw_pos_prev;

long double lw_velocity;
long double bw_velocity;
long double rw_velocity;

long double duration;

ros::Time timeCurrent;
ros::Time timePrevious;

omni_steering_pkg::omni_velocity vel_msg;


void onJointMessage(const sensor_msgs::JointState::ConstPtr& input){
    timeCurrent = ros::Time::now();
    for (int i = 0; i < input->name.size(); i++){
        if (input->name[i][4] == 'b'){
            bw_pos_current = input->position[i];             
        }
        else if (input->name[i][4] == 'l'){
            lw_pos_current = input->position[i];             
        }
        else if (input->name[i][4] == 'r'){
            rw_pos_current = input->position[i];             
        }
    }
    duration = (timeCurrent - timePrevious).toSec();
    bw_velocity = (bw_pos_current - bw_pos_prev)/duration; 
    lw_velocity = (lw_pos_current - lw_pos_prev)/duration; 
    rw_velocity = (rw_pos_current - rw_pos_prev)/duration; 
    
    vel_msg.lw_vel = lw_velocity; 
    vel_msg.bw_vel = bw_velocity;
    vel_msg.rw_vel = rw_velocity;
    js_publisher.publish(vel_msg);


    timePrevious = timeCurrent;
    bw_pos_prev = bw_pos_current;
    lw_pos_prev = lw_pos_current;
    rw_pos_prev = rw_pos_current;

    return;
}

int main(int argc, char **argv){
    ros::init(argc, argv,"encoder");
    ros::NodeHandle nh;

    // waits until it recieves the first /clock message
    while (!ros::Time::waitForValid()){}

    // Initializing JointState topic subscriber
    ros::Subscriber js_subscriber = nh.subscribe("/omni_robot/joint_states",1,onJointMessage);

    
    js_publisher = nh.advertise<omni_steering_pkg::omni_velocity>("/wheel_velocity", 1); 

    // Loop processing callbacks
    ros::spin();

    return 0;
}
