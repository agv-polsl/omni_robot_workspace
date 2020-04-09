#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <iostream>
#include <termios.h>
#include "lib/steeringNodeHandler.h"

using namespace std; 
using namespace SNH;
// Parameters 
#define L 0.04 // distance between body center and wheel center
#define r 0.01905 // wheel radius
#define sqrt3 1.732050807568877193176604123436845839023590087890625 
#define sqrt32 0.8660254037844385965883020617184229195117950439453125

double Vxm;
double Vym;
double omegaP;
double Vleft, Vright, Vback;

enum{
  UP = 65, DOWN = 66, RIGHT = 67, LEFT = 68, SPACE = 32
};




void inverseKinematicsMobile(){
  Vleft = -(Vxm/2.0) - (sqrt32*Vym) + (L*omegaP);
  Vright = -(Vxm/2.0) + (sqrt32*Vym) + (L*omegaP);
  Vback = Vxm + omegaP;
  return;
}


// Function to get the currently pressed key
int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings
  auto c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}


int main(int argc, char **argv){
  ros::init(argc, argv, "Omni_steering");
  // Frequency of loop(node) must be highest as possible
  // because it's reading keyboard actions 
  ros::NodeHandle n;
  steeringNodeHandler steeringnodehandler(n);
  ros::Rate loop_rate(1000);  

  Vxm = 0.0;
  Vym = 0.0;        
  omegaP = 0.0;
  double speed = 10; 
  
  inverseKinematicsMobile();
  steeringnodehandler.updateVelMsgs(Vleft, Vback, Vright);

  while (ros::ok()){
    auto keyPressed = getch();   // call your non-blocking input function
    // ROS_ERROR_STREAM("button pressed: " << c);
    switch (keyPressed){
      case UP:
        ROS_ERROR_STREAM("UP");
        Vxm = 0.0;
        Vym = speed;        
        omegaP = 0.0;
        break;
      case DOWN:
        ROS_ERROR_STREAM("DOWN");
        Vxm = 0.0;
        Vym = -speed;        
        omegaP = 0.0;
        break;
      case LEFT:
        ROS_ERROR_STREAM("LEFT");
        Vxm = -speed;
        Vym = 0.0;        
        omegaP = 0.0;
        break;
      case RIGHT:
        ROS_ERROR_STREAM("RIGHT");
        Vxm = speed;
        Vym = 0.0;        
        omegaP = 0.0;
        break;
      case SPACE:
        ROS_ERROR_STREAM("SPACE");
        Vxm = 0.0;
        Vym = 0.0;        
        omegaP = 0.0;
        break;
      default:
        Vxm = 0.0;
        Vym = 0.0;        
        omegaP = 0.0;
        break;
      }
    
    inverseKinematicsMobile();
    steeringnodehandler.updateVelMsgs(Vleft, Vback, Vright);
    steeringnodehandler.publishVelocities();

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;

}