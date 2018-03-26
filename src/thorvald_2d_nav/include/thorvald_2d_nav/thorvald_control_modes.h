#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <cmath>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>

// ROS message includes
#include <thorvald_2d_nav/sub_goal.h>
#include <thorvald_2d_nav/landmarks.h>


//Callback Initialzations
nav_msgs::Odometry thorvald_estimated_pose;
thorvald_2d_nav::landmarks landmarks_pose;

//Rosservice parameters
thorvald_2d_nav::sub_goal goal_count; 
int row_no = 0;
bool next_row_check = true;

//Controller Parameters
geometry_msgs::Point mini_goal_pts;
int Total_Points = 15;
geometry_msgs::Pose Points[20];
geometry_msgs::Twist est_twist;
double yaw, position_error, angular_error, q_x , q_y;
double K_d = 0.00000000001, K_p = 0.01;
bool mini_goal = false;
