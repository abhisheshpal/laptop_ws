#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>
#include <cmath>
#include <math.h>       /* fabs */
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseArray.h>

// ROS message includes
#include <thorvald_2d_nav/scan_detected_line.h>
#include <thorvald_2d_nav/sub_goal.h>
#include <thorvald_2d_nav/landmarks.h>

#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/transform_listener.h>

// Parameters 
geometry_msgs::Point n;
int k; // iterations need to find the best model
double thershold = 0.1;
int d = 25; // nearby point to fit the line

double best_model;
size_t num_ranges;
double x_1[1080], y_1[1080], angle_1[1080], x_2[1080], y_2[1080], angle_2[1080];
sensor_msgs::LaserScan scan_msg_main;
double current_range_1, current_range_2;
int count_i_1[1080], count_i_2[1080];
visualization_msgs::Marker line_strip_1, line_strip_2, final_line;
nav_msgs::Odometry thorvald_pose;
thorvald_2d_nav::scan_detected_line measurement_points;
thorvald_2d_nav::landmarks landmarks_pos;
tf2_ros::Buffer tfBuffer; 

// Our "data".
struct Point {
  double real_x; double real_y;
};

// Our "model".
struct Line {
  double m; double b;
};

Point best_inlierpoints_1[1080];
Point current_best_inlierpoints_1[1080];
Line final_line_1;
Point final_Index_1[2], current_Index_1[2];

Point best_inlierpoints_2[1080];
Point current_best_inlierpoints_2[1080];
Line final_line_2;
Point final_Index_2[2], current_Index_2[2];

//Transform varibles
geometry_msgs::TransformStamped transformStamped;
geometry_msgs::PoseStamped left_line_1, left_line_1_transformed, left_line_2, left_line_2_transformed;
geometry_msgs::PoseStamped right_line_1, right_line_1_transformed, right_line_2, right_line_2_transformed;

// dummy variables
int p_1 = 1, l_1 = 1, c_1 = 0, a_1 = 0, b_1 = 0, p_2 = 1, l_2 = 1, c_2 = 0, a_2 = 0, b_2 = 0;
int final_count_1 = 0, final_count_2 = 0, final_count_3 = 0, final_count_4 = 0, final_count_5 = 0, final_count_6 = 0, finale = 0;
double row_end = 0, yaw, row_no = 1;
thorvald_2d_nav::sub_goal end_row_check;
int end_row_reach = 0, line_pt = 0;
double min_range_view = 4.0, max_range = 30.0;
int end_line = 0, end_row = 0, finale_1 = 0, finale_2 = 0, land_check = 0;
bool line_found_1 = false, line_found_2 = false, new_row = false;

