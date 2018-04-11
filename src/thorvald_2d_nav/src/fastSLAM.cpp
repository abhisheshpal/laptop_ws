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
#include <random>

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
// bool landmarks_observed = false;
ros::Time current_time, last_time;

//initialize velocity variables
double vx = 0.0, vy = 0.0, vth = 0.0;

// Initialization for SLAM
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

// particle filter
static const int numParticles = 100;
double noise = 0.005;

// particle structure
struct landmarks_struct{
bool landmarks_observed;
double mu[2];
double sigma[2][2];
};

struct particles_struct{
double weight;
geometry_msgs::Pose pose;
geometry_msgs::Pose pose_history;
struct landmarks_struct landmarks[numParticles];
};

particles_struct particles[numParticles];

// robot velocity data
void odometryvelCallback (const geometry_msgs::Twist::ConstPtr& odometry_vel){
odom_vel.linear = odometry_vel->linear;
}

// robot pose data
void odometryCallback (const nav_msgs::Odometry::ConstPtr& odometry){
robot_pose.pose.pose = odometry->pose.pose;
robot_pose.twist.twist = odometry->twist.twist;

tf::Quaternion quat(robot_pose.pose.pose.orientation.x,robot_pose.pose.pose.orientation.y, robot_pose.pose.pose.orientation.z, robot_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

//line point data
void linepointsCallback(const thorvald_2d_nav::scan_detected_line::ConstPtr& line_points){

if (line_points->range.size() > 0){
for (int num = 0; num < total_landmarks; num++){
measured_points_range[num] = line_points->range[num];
measured_points_bearing[num] = line_points->bearing[num];
}}

}

//line points 
void landmarksposeCallback (const thorvald_2d_nav::landmarks::ConstPtr& landmarks_msg)
{

if (landmarks_msg->landmark_check > 0){        
landmarks_pose.pt_1 = landmarks_msg->pt_1;
landmarks_pose.pt_2 = landmarks_msg->pt_2;
landmarks_pose.pt_3 = landmarks_msg->pt_3;
landmarks_pose.pt_4 = landmarks_msg->pt_4;
landmarks_pose.pt_5 = landmarks_msg->pt_5;
landmarks_pose.pt_6 = landmarks_msg->pt_6;
landmarks_pose.landmark_check = landmarks_msg->landmark_check; 

// calculation of estimated range and bearing
line_pho(0,0) = sqrt(pow(landmarks_pose.pt_1.x,2) + pow(landmarks_pose.pt_1.y,2));
line_theta(0,0) = atan2(landmarks_pose.pt_1.y,landmarks_pose.pt_1.x);
line_pho(1,0) = sqrt(pow(landmarks_pose.pt_2.x,2) + pow(landmarks_pose.pt_2.y,2));
line_theta(1,0) = atan2(landmarks_pose.pt_2.y,landmarks_pose.pt_2.x);

line_pho(2,0) = sqrt(pow(landmarks_pose.pt_3.x,2) + pow(landmarks_pose.pt_3.y,2));
line_theta(2,0) = atan2(landmarks_pose.pt_3.y,landmarks_pose.pt_3.x);
line_pho(3,0) = sqrt(pow(landmarks_pose.pt_4.x,2) + pow(landmarks_pose.pt_4.y,2));
line_theta(3,0) = atan2(landmarks_pose.pt_4.y,landmarks_pose.pt_4.x);
}

}

double normalizeangle(double bearing){
if (bearing > M_PI){
bearing = M_PI;}
if(bearing < -M_PI){
bearing = -M_PI;}
}

void initializate_paramters(){

for (int i = 1; i <= numParticles; i++){
particles[i].weight = 1/numParticles;
particles[i].pose.position.x = 0;
particles[i].pose.position.y = 0;
particles[i].pose.orientation = tf::createQuaternionMsgFromYaw(0);
particles[i].pose_history = particles[i].pose;
 for (int j = 1; j <= total_landmarks; j++){
 particles[i].landmarks[j].landmarks_observed = false;
 particles[i].landmarks[j].mu[2] = {0};
 particles[i].landmarks[j].sigma[2][2] = {};
 }
}

}

void prediction_step(struct particles_struct *particles1, double dt1){

  vx = robot_pose.twist.twist.linear.x;
  vy = robot_pose.twist.twist.linear.y;
  vth = robot_pose.twist.twist.angular.z;

for (int i = 1; i <= numParticles; i++){

/* particles[i].pose_history = particles[i].pose;

particles1[i].pose.position.x = particles1[i].pose.position.x + (vx*dt);
particles1[i].pose.position.y = particles1[i].pose.position.y + (vy*dt);
particles1[i].pose.orientation = tf::createQuaternionMsgFromYaw(yaw+(vth*dt));

*/

std::normal_distribution<double> distribution(vth,noise);

particles1[i].pose.position.x = robot_pose.pose.pose.position.x;
particles1[i].pose.position.y = robot_pose.pose.pose.position.y;
particles1[i].pose.orientation = robot_pose.pose.pose.orientation;

}

}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "fastSLAM");
  ros::NodeHandle n;
  ros::Rate r(10.0);

   // Subscribers
   ros::Subscriber landmarks_sub = n.subscribe("landmark_points", 100, landmarksposeCallback);
   ros::Subscriber odom_sub = n.subscribe("/thorvald_ii/odom", 100, odometryCallback);
   ros::Subscriber odom_vel_sub = n.subscribe("/odom_topic", 50, odometryvelCallback);
   ros::Subscriber point_sub = n.subscribe("measurement_points", 100, linepointsCallback);

   current_time = ros::Time::now();
   last_time = ros::Time::now();

  while (ros::ok()){

  ros::spinOnce();
  current_time = ros::Time::now();
  dt = (current_time - last_time).toSec();
 
  initializate_paramters();

   // prediction step
  prediction_step(particles, dt);

  r.sleep();
  } 
  return 0;
}

