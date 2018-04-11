#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>    // std::max
#include <cmath>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

// ROS message includes
#include <thorvald_2d_nav/scan_detected_line.h>
#include <thorvald_2d_nav/landmarks.h>
#include <thorvald_2d_nav/sub_goal.h>

#define INF 1000
using namespace Eigen;

// Initialization for callbacks
geometry_msgs::Twist odom_vel;
nav_msgs::Odometry robot_pose;
thorvald_2d_nav::landmarks landmarks_pose;
nav_msgs::Odometry thorvald_estimated_pose;
thorvald_2d_nav::sub_goal goal_count; 
geometry_msgs::Twist twist_msg;
double measured_points_range[4], measured_points_bearing[4];
int total_landmarks = 4; 
double d = 0.5; // distance between two wheels
double lambda_x, lambda_y, q, dt;
bool landmarks_observed = false;
ros::Time current_time, last_time;

// Initialization for localization
double yaw, motion_noise = 0.00001, measurement_noise = 0.0001, sub_goal_thershold = 0.05;
MatrixXd mu = MatrixXd::Zero(2*total_landmarks+3,1); // mu
MatrixXd line_local(4,2); // line_local
MatrixXd line_local_fixed(4,2); // line_local_fixed
MatrixXd Z = MatrixXd::Zero(8,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(8,1); // expectedZ
MatrixXd K = MatrixXd::Zero((2*total_landmarks+3),2); // Kalman gain
MatrixXd diff = MatrixXd::Zero(2,2); // error
MatrixXd H = MatrixXd::Zero(2*total_landmarks,(2*total_landmarks+3)); // H - Jacobian
MatrixXd line_pho = MatrixXd::Zero(4,1); // polar co-ordinates
MatrixXd line_theta = MatrixXd::Zero(4,1); // polar co-ordinates
MatrixXd robSigma    = MatrixXd::Zero(3,3);
MatrixXd robMapSigma = MatrixXd::Zero(3,(2*total_landmarks));
MatrixXd mapSigma    = INF*MatrixXd::Identity((2*total_landmarks), (2*total_landmarks));
MatrixXd cov = MatrixXd::Zero((2*total_landmarks+3),(2*total_landmarks+3));
MatrixXd R = MatrixXd::Zero((2*total_landmarks+3),(2*total_landmarks+3)); // Motion Noise
MatrixXd Q = MatrixXd::Identity(8,8)* measurement_noise; // Measurement Noise

//initialize velocity variables
double vx = 0.0, vy = 0.0, vth = 0.0;
