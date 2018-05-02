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
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64MultiArray.h>

// ROS message includes
#include <thorvald_2d_nav/sub_goal.h>
#include <thorvald_2d_nav/landmarks.h>

#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/transform_listener.h>

//Callback Initialzations
geometry_msgs::PoseStamped thor_est, thor_est_trans;
thorvald_2d_nav::landmarks landmarks_pose;
geometry_msgs::TransformStamped transformStamped;
tf2_ros::Buffer tfBuffer;

//Rosservice parameters
thorvald_2d_nav::sub_goal goal_count; 
int row_no = 0;
bool next_row_check = true;

//Controller Parameters
geometry_msgs::Point mini_goal_pts;
int Total_Points = 15;
geometry_msgs::Pose Points[20];
geometry_msgs::Twist est_twist;
double yaw, position_error, angular_error, q_x , q_y, lastError = 0;
double K_d = 0.01, K_p = 0.02, K_i = 0.001;
bool mini_goal = false;
double _integral = 0;

// dummy variables
int counter_line = 0, counter_1 = 0, line_count = 0, c = 1;
