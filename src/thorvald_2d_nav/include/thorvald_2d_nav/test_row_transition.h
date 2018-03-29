#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <cmath>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>

// ROS message includes
#include <thorvald_2d_nav/sub_goal.h>

#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

//Callback parameters
geometry_msgs::Twist est_twist;
double yaw;
nav_msgs::Odometry thorvald_pose;

//Transform parameters
geometry_msgs::Pose goal_pt[2];
tf2_ros::Buffer tfBuffer;
geometry_msgs::TransformStamped transformStamped;
thorvald_2d_nav::sub_goal end_row_transit, end_row_transit_1;

//Parameters for pole detection
double min_range = 3.0;
sensor_msgs::LaserScan scan_msg_main;
size_t num_ranges;
bool goal_found = false;
double sum_x_1 = 0, sum_y_1 = 0;
int k = 0, q = 0, unfit = 0, unfit_1 = 0;
double current_range_1, current_range_2, current_range_3, angle_1, angle_2, angle_3;
int row_transit_mode = 0;
double nearest_pole_x, nearest_pole_y, next_nearest_pole_x, next_nearest_pole_y, farthest_pole_x, farthest_pole_y;

//Pole Markers
visualization_msgs::Marker marker_1;
visualization_msgs::Marker marker_2;
visualization_msgs::Marker marker_3;
visualization_msgs::Marker marker_goal_1;
visualization_msgs::Marker marker_goal_2;

//dummy variables
double linear_velocity = 0.5, angular_velocity = 0.0;
double goal_range, goal_bearing, a = 0;
bool pole_detect = false, turn_90 = false; 
int goal_transit = 1, c = 0;
