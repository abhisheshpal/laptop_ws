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
#include <nav_msgs/Path.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64MultiArray.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>
#include <random>
#include <string>
#include <assert.h>

using namespace Eigen;
int n1;
MatrixXd p_j = MatrixXd::Zero(2,1);

// Thorvald pose structure
struct thorvald_pose_struct{
bool landmarks_observed;
MatrixXd mu = MatrixXd::Zero(6,1); // mu
MatrixXd sigma = MatrixXd::Zero(6,6); // sigma
};

thorvald_pose_struct thor_pose;
geometry_msgs::PoseStamped true_pose, thor_est;
nav_msgs::Odometry thor_est_gps;
MatrixXd expp = MatrixXd::Zero(1,1);
MatrixXd weight_1 = MatrixXd::Zero(1,1);
MatrixXd weight_2 = MatrixXd::Zero(1,1);

// update step variables
double yaw, motion_noise = 0.00001, measurement_noise = 0.0001, total_landmarks = 4;
MatrixXd H = MatrixXd::Zero(6,6); // H - Jacobian
MatrixXd K = MatrixXd::Zero(2,2); // Kalman gain
MatrixXd Z = MatrixXd::Zero(2,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(2,1); // expectedZ
MatrixXd diff = MatrixXd::Zero(2,1); // error
MatrixXd Q_t = MatrixXd::Identity(6,6)* measurement_noise; // Measurement Noise 
MatrixXd Q = MatrixXd::Zero(6,6)* measurement_noise; // Measurement Process 
MatrixXd C = MatrixXd::Zero(6,6); // C for weight

void thorposeCallback(const geometry_msgs::PoseStamped::ConstPtr& curr_pose){
true_pose.pose = curr_pose->pose;
}

void estposeCallback(const geometry_msgs::PoseStamped::ConstPtr& est_pose){
thor_est.pose = est_pose->pose;
}

void estposeCallback1(const nav_msgs::Odometry::ConstPtr& est_pose){
thor_est_gps.pose.pose = est_pose->pose.pose;
}


double normalizeangle(double bearing){
    if (bearing < -M_PI) {
        bearing += 2*M_PI;
    } else if (bearing > M_PI) {
        bearing -= 2*M_PI;
    }
}

MatrixXd measurement_model(struct thorvald_pose_struct thor_pose3){

// For Laser
H(0,0) = 1; 
H(1,1) = 1; 
H(2,2) = 1; 

// For GPS
H(0,0) = 1; 
H(1,1) = 1; 
H(5,5) = 1;

return H;
}


void correction_step(struct thorvald_pose_struct thor_pose1, MatrixXd diff1){

  // calculate jacobian w.r.t landmark pose
  H = measurement_model(thor_pose1);

 // Finish the correction step by computing the new mu and sigma.
  thor_pose1.mu = thor_pose1.mu + K*diff1;
  thor_pose1.sigma =  (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*thor_pose1.sigma;
  thor_pose1.mu(1,0)= normalizeangle(thor_pose1.mu(1,0));
}

MatrixXd compute_weight(struct thorvald_pose_struct thor_pose5, MatrixXd innovation){
C = H*thor_pose5.sigma*H.transpose() + Q;
expp = (-0.5*innovation*C.inverse()*innovation.transpose()).exp();
MatrixXd weight = (1/ (pow((2*M_PI),n1/2) * sqrt(C.determinant()))) * expp;
return weight;
}

struct thorvald_pose_struct fusion_model(struct thorvald_pose_struct thor_pose_f, MatrixXd weigh_1, MatrixXd weigh_2){

// normalizing weight
// p_j(0,0) = weigh_1/(weigh_1+weigh_2);
// p_j(1,0) = weigh_1/(weigh_1+weigh_2);


return thor_pose_f;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fusion_model");
  ros::NodeHandle n;
  ros::Rate r(10.0);

  // Subscribers
  ros::Subscriber pose_sub = n.subscribe("/curr_thor", 100, thorposeCallback);
  ros::Subscriber pose_sub1 = n.subscribe("/thor_est_laser", 100, estposeCallback);
  ros::Subscriber pose_sub2 = n.subscribe("/thor_est_gps", 100, estposeCallback1);

  while (ros::ok()){

  // update step
  correction_step(thor_pose, diff);
  
  // compute weight
  if(n1 == 1){
  weight_1 = compute_weight(thor_pose, diff);
  }

  if(n1 == 2){
  weight_2 = compute_weight(thor_pose, diff);
  }

  // fusion model
  thor_pose = fusion_model(thor_pose, weight_1, weight_2);

  r.sleep();
  }
  return 0;
}

