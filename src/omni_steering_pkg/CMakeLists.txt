cmake_minimum_required(VERSION 2.8.3)
project(omni_steering_pkg)
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} lib)

add_executable(omni_steering_test_node 
    src/omni_steering_test.cpp
    src/lib/steeringNodeHandler.cpp
)
target_link_libraries(omni_steering_test_node ${catkin_LIBRARIES})
add_dependencies(omni_steering_test_node ${omni_steering_test_node_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
