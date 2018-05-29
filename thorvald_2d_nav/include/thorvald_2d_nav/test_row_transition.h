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
geometry_msgs::PoseStamped thor_est, thor_est_trans;

//Transform parameters
geometry_msgs::Pose goal_pt[2];
tf2_ros::Buffer tfBuffer, tfBuffer1;
geometry_msgs::TransformStamped transformStamped, transformStamped1;
thorvald_2d_nav::sub_goal end_row_transit, end_row_transit_1;

//Parameters for pole detection
double min_range_left = 2.0, min_range_right = 3.0;
sensor_msgs::LaserScan scan_msg_main, scan_msg;
size_t num_ranges;
bool goal_found = false;
double sum_x_1 = 0, sum_y_1 = 0;
int k = 0, q = 0, n = 0, unfit = 0, unfit_1 = 0, unfit_2 = 0;
double current_range_1, current_range_2, current_range_3, current_range_4, angle_1, angle_2, angle_3, angle_4;

double nearest_pole_x, nearest_pole_y, next_nearest_pole_x, next_nearest_pole_y, farthest_pole_x, farthest_pole_y;
double min_itr_1, max_itr_1, min_itr_2, max_itr_2;
int turn_side = 1; // 1 for RIGHT, 2 for LEFT
enum TURN {RIGHT = 1, LEFT = 2};

//Pole Markers
visualization_msgs::Marker marker_1, marker_2, marker_3;
visualization_msgs::Marker marker_goal_1, marker_goal_2;
visualization_msgs::Marker empty_pole_1, empty_pole_2, empty_pole_3;
visualization_msgs::Marker empty_goal_1, empty_goal_2;

//dummy variables
double linear_velocity = 0.4, angular_velocity = 0.0;
double goal_range, goal_bearing, a = 0;
bool pole_detect = false, turn_90 = false; 
int goal_transit = 0, c = 0, row_transit = 1, row_transit_mode = 0;
double min_goal_range = 0.10;
