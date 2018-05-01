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
double weight;

// Thorvald pose structure
struct thorvald_pose_struct{
bool landmarks_observed;
MatrixXd mu = MatrixXd::Zero(2,1); // mu
MatrixXd sigma = MatrixXd::Zero(2,2); // sigma
};

thorvald_pose_struct thor_pose;
geometry_msgs::PoseStamped true_pose;

// update step variables
double yaw, motion_noise = 0.00001, measurement_noise = 0.0001, total_landmarks = 4;
MatrixXd H = MatrixXd::Zero(2,2); // H - Jacobian
MatrixXd K = MatrixXd::Zero(2,2); // Kalman gain
MatrixXd Z = MatrixXd::Zero(2,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(2,1); // expectedZ
MatrixXd diff = MatrixXd::Zero(2,1); // error
MatrixXd Q_t = MatrixXd::Identity(2,2)* measurement_noise; // Measurement Noise 
MatrixXd Q = MatrixXd::Zero(2,2)* measurement_noise; // Measurement Process 

void thorposeCallback(const geometry_msgs::PoseStamped::ConstPtr& curr_pose){
true_pose.pose = curr_pose->pose;
}

double normalizeangle(double bearing){
    if (bearing < -M_PI) {
        bearing += 2*M_PI;
    } else if (bearing > M_PI) {
        bearing -= 2*M_PI;
    }
}

void correction_step(struct thorvald_pose_struct thor_pose1, MatrixXd diff1){

  // calculate jacobian w.r.t landmark pose
  // H = measurement_model(thor_pose1,i,s);

 // Finish the correction step by computing the new mu and sigma.
  thor_pose1.mu = thor_pose1.mu + K*diff1;
  thor_pose1.sigma =  (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*thor_pose1.sigma;
  thor_pose1.mu(1,0)= normalizeangle(thor_pose1.mu(1,0));
}

double compute_weight(MatrixXd innovation){
weight = 1/n1;
return weight;
}

void fusion_model(struct thorvald_pose_struct thor_pose2){

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fusion_model");
  ros::NodeHandle n;
  ros::Rate r(10.0);

  // Subscribers
  ros::Subscriber pose_sub = n.subscribe("thorvald_pose", 100, thorposeCallback);

  while (ros::ok()){

  // update step
  correction_step(thor_pose, diff);
  
  // compute weight
  weight = compute_weight(diff);

  // fusion model
  fusion_model(thor_pose);

  r.sleep();
  }
  return 0;
}

