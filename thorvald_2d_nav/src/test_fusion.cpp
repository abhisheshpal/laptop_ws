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
int n1 = 1, total_landmarks = 4;
MatrixXd p_j_0 = MatrixXd::Zero(1,1);
MatrixXd p_j_1 = MatrixXd::Zero(1,1);

// Thorvald pose structure
struct thorvald_pose_struct{
bool landmarks_observed;
MatrixXd mu = MatrixXd::Zero(2*total_landmarks+3,1); // mu
MatrixXd sigma = MatrixXd::Zero(2*total_landmarks + 3,2*total_landmarks + 3); // sigma
};

thorvald_pose_struct thor_pose, thor_pose_est;
geometry_msgs::Pose true_pose;
geometry_msgs::PoseStamped thor_est;
nav_msgs::Odometry thor_est_gps;
MatrixXd expp = MatrixXd::Zero(1,1);
MatrixXd weight_1 = MatrixXd::Zero(1,1);
MatrixXd weight_2 = MatrixXd::Zero(1,1);
MatrixXd zi =  MatrixXd::Zero(2*total_landmarks + 3,1);

// update step variables
double yaw, motion_noise = 0.00001, measurement_noise = 0.0001;
MatrixXd H = MatrixXd::Zero(2*total_landmarks + 3,2*total_landmarks + 3); // H - Jacobian
MatrixXd K = MatrixXd::Zero(2*total_landmarks + 3,2*total_landmarks + 3); // Kalman gain
MatrixXd Z = MatrixXd::Zero(2,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(2,1); // expectedZ
MatrixXd diff = MatrixXd::Zero(2*total_landmarks + 3,1); // error
MatrixXd Q_t = MatrixXd::Identity(2*total_landmarks+3,2*total_landmarks + 3)* measurement_noise; // Measurement Noise 
MatrixXd Q = MatrixXd::Zero(2*total_landmarks + 3,2*total_landmarks + 3)* measurement_noise; // Measurement Process 
MatrixXd C = MatrixXd::Zero(2*total_landmarks + 3,2*total_landmarks + 3); // C for weight

void thorposeCallback(const geometry_msgs::Pose::ConstPtr& curr_pose){
true_pose.position = curr_pose->position;
true_pose.orientation = curr_pose->orientation;
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
H(2,2) = 1; 

return H;
}


void correction_step(struct thorvald_pose_struct thor_pose1, MatrixXd diff1){

  // calculate jacobian w.r.t landmark pose
  H = measurement_model(thor_pose1);

 // Finish the correction step by computing the new mu and sigma.
  thor_pose1.mu = thor_pose1.mu + K*diff1;
  thor_pose1.sigma =  (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*thor_pose1.sigma;
  thor_pose1.mu(2,0)= normalizeangle(thor_pose1.mu(2,0));
}

MatrixXd compute_weight(struct thorvald_pose_struct thor_pose5, MatrixXd innovation){
	MatrixXd weight = MatrixXd::Zero(1,1);
C = H*thor_pose5.sigma*H.transpose() + Q;
expp = (-0.5*innovation.transpose()*C.inverse()*innovation).exp();
weight = (1/ (pow((2*M_PI),n1/2) * sqrt(C.determinant()))) * expp;
return weight;
}

struct thorvald_pose_struct fusion_model(struct thorvald_pose_struct thor_pose_f, MatrixXd weigh_1, MatrixXd weigh_2){

// normalizing weight
p_j_0 = weigh_1*(weigh_1+weigh_2).inverse();
p_j_1 = weigh_1*(weigh_1+weigh_2).inverse();

thor_pose_est.landmarks_observed = thor_pose_f.landmarks_observed;	

// final state and co-variance model
thor_pose_est.mu = thor_pose_f.mu*p_j_0 + thor_pose_f.mu*p_j_1;
zi = thor_pose_est.mu - thor_pose_f.mu;
ROS_INFO("1");
thor_pose_est.sigma = p_j_0*(thor_pose_f.sigma+(zi.transpose()*zi)) + p_j_1*(thor_pose_f.sigma+(zi.transpose()*zi));
ROS_INFO("2");
return thor_pose_est;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fusion_model");
  ros::NodeHandle n;
  ros::Rate r(10.0);

  // Subscribers
  ros::Subscriber pose_sub = n.subscribe("/thorvald_pose", 100, thorposeCallback);
  ros::Subscriber pose_sub1 = n.subscribe("/thor_est_laser", 100, estposeCallback);
  ros::Subscriber pose_sub2 = n.subscribe("/odometry/global", 100, estposeCallback1);

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
ROS_INFO("afa1");
  r.sleep();
  }
  return 0;
}

