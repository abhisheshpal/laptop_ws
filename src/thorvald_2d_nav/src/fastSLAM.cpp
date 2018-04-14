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
double gaussnoise = 0;

//initialize velocity variables
double vx = 0.0, vy = 0.0, vth = 0.0;

// Initialization for SLAM
double yaw, current_yaw = 0, motion_noise = 0.00001, measurement_noise = 0.0001, sub_goal_thershold = 0.05;
// MatrixXd mu = MatrixXd::Zero(2,1); // mu
// MatrixXd sigma = MatrixXd::Zero(2,2); // mu

MatrixXd H = MatrixXd::Zero(2,2); // H - Jacobian
MatrixXd diff = MatrixXd::Zero(2,2); // error
MatrixXd K = MatrixXd::Zero(2,2); // Kalman gain
MatrixXd Z = MatrixXd::Zero(2,1); // Z
MatrixXd Q_t = MatrixXd::Identity(2,2)* measurement_noise; // Measurement Noise 
MatrixXd Q = MatrixXd::Identity(2,2)* measurement_noise; // Measurement Noise 
MatrixXd expectedZ = MatrixXd::Zero(2,1); // expectedZ
MatrixXd line_pho = MatrixXd::Zero(4,1); // polar co-ordinates
MatrixXd line_theta = MatrixXd::Zero(4,1); // polar co-ordinates


/*MatrixXd mu = MatrixXd::Zero(2*total_landmarks+3,1); // mu
MatrixXd line_local(4,2); // line_local
MatrixXd line_local_fixed(4,2); // line_local_fixed
MatrixXd robSigma    = MatrixXd::Zero(3,3);
MatrixXd robMapSigma = MatrixXd::Zero(3,(2*total_landmarks));
MatrixXd mapSigma    = INF*MatrixXd::Identity((2*total_landmarks), (2*total_landmarks));
MatrixXd cov = MatrixXd::Zero((2*total_landmarks+3),(2*total_landmarks+3));
MatrixXd R = MatrixXd::Zero((2*total_landmarks+3),(2*total_landmarks+3)); // Motion Noise
*/

// particle filter
static const int numParticles = 100;
double noise = 0.005;

// particle structure
struct landmarks_struct{
bool landmarks_observed;
MatrixXd mu = MatrixXd::Zero(2,1); // mu
MatrixXd sigma = MatrixXd::Zero(2,2); // sigma
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
for (int num = 1; num <= total_landmarks; num++){
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


MatrixXd measurement_model(struct particles_struct *particles3, int i, int z){
 lambda_x = particles3[i].landmarks[z].mu(0) - robot_pose.pose.pose.position.x;
 lambda_y = particles3[i].landmarks[z].mu(1) - robot_pose.pose.pose.position.y;
 q = pow(lambda_x,2) + pow(lambda_y,2);

 double expectedRange = sqrt(q);
 double expectedBearing = normalizeangle((lambda_y/lambda_x) - yaw);
 expectedZ(2*z,0) = expectedRange;
 expectedZ((2*z)+1,0) = expectedBearing;

 H(1,1) = (particles[i].landmarks[z].mu(0)-particles[i].pose.position.x)/expectedRange;
 H(1,2) = (particles[i].landmarks[z].mu(1)-particles[i].pose.position.y)/expectedRange;
 H(2,1) = (particles[i].pose.position.y-particles[i].landmarks[z].mu(1))/(pow(expectedRange,2));
 H(2,2) = (particles[i].landmarks[z].mu(0)-particles[i].pose.position.x)/(pow(expectedRange,2));
 return H;
}

double normrnd(double mean, double stdDev) {
    double u, v, s;
    do {
        u = ((double)rand()/(double)RAND_MAX) * 2.0 - 1.0;
        v = ((double)rand()/(double)RAND_MAX) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1 || s == 0);
    double mul = sqrt(-2.0 * log(s) / s);
    return mean + stdDev * u * mul;
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
 // particles[i].landmarks[j].mu[2] = {0};
 // particles[i].landmarks[j].sigma[2][2] = {};
 }
}

}

void prediction_step(struct particles_struct *particles1, double dt1){

vx = robot_pose.twist.twist.linear.x;
vy = robot_pose.twist.twist.linear.y;
vth = robot_pose.twist.twist.angular.z;

for (int i = 1; i <= numParticles; i++){

// particles[i].pose_history = particles[i].pose;
gaussnoise = normrnd(vth,noise);
particles1[i].pose.position.x = particles1[i].pose.position.x + ((vx+gaussnoise)*dt1);
particles1[i].pose.position.y = particles1[i].pose.position.y + ((vy+gaussnoise)*dt1);

current_yaw = (current_yaw+vth+gaussnoise)*dt1;
particles1[i].pose.orientation = tf::createQuaternionMsgFromYaw(current_yaw);}
}

void correction_step(struct particles_struct *particles2, double dt2){

for (int i = 1; i <= numParticles; i++){

      // Landmarks observation
     for (int z = 1; z <= total_landmarks; z++){

        // Transformation of Line from global co-ordinate into robot frame
      if (particles[i].landmarks[z].landmarks_observed == false){
        // line_local_2(z,0) =  line_pho(z,0) - (robot_pose.pose.pose.position.x * cos(line_theta(z,0))) - (robot_pose.pose.pose.position.y * sin(line_theta(z,0)));
        // line_local_2(z,1) =  line_theta(z,0) - yaw + (3.14/2);

         particles[i].landmarks[z].mu(0) =  robot_pose.pose.pose.position.x + (measured_points_range[z] + cos(yaw+measured_points_bearing[z]));
         particles[i].landmarks[z].mu(1) =  robot_pose.pose.pose.position.y + (measured_points_range[z] + sin(yaw+measured_points_bearing[z]));
         particles[i].landmarks[z].landmarks_observed = true;

         // calculate jacobian w.r.t landmark pose
         H = measurement_model(particles,i,z);

         // initialize 2*2 EKF for current landmark
         particles[i].landmarks[z].sigma = H.inverse() * Q_t * (H.inverse()).transpose(); //CHECK
         particles[i].weight = 0.5;
      }

      else{

         Z(2*z,0) = measured_points_range[z];
         Z((2*z)+1,0) = measured_points_bearing[z];

         // calculate jacobian w.r.t landmark pose
         H = measurement_model(particles,i,z);

         Q = (H*particles[i].landmarks[z].sigma*H.transpose()) + Q_t;

         // Kalman Gain
         K = (particles[i].landmarks[z].sigma*H.transpose()) * (Q.inverse());

        // Compute the diference between the expected and recorded measurements.
         diff = Z - expectedZ;

	// Finish the correction step by computing the new mu and sigma.
        particles[i].landmarks[z].mu = particles[i].landmarks[z].mu + K*diff;
        particles[i].landmarks[z].sigma =  (MatrixXd::Identity(2,2)- K*H)*particles[i].landmarks[z].sigma ;
        particles[i].landmarks[z].mu(1) = normalizeangle(particles[i].landmarks[z].mu(1));

        // Particle Weight
        // particles[i].weight = particles[i].weight*(1/sqrt(det(2*M_PI*Q))*exp((-1/2)*diff.transpose()/Q*diff));
        // particles[i].weight = particles[i].weight * (abs(pow((2*M_PI*Q),0.5)) * exp((-1/2)*diff.transpose()*Q.inverse()*diff));
       }
      }	


}

}

void resample(){
N= length(particles);
w= zeros(1,N);
for i=1:N, w(i)= particles(i).w; end
ws= sum(w); w= w/ws;
for i=1:N, particles(i).w= particles(i).w / ws; end

[keep, Neff] = stratified_resample(w);
if Neff < Nmin & doresample==1
    particles= particles(keep);
for i=1:N, particles(i).w= 1/N; end
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

  // correction step
  correction_step(particles, dt);

  // resampling step
  resample(particles, dt);

  r.sleep();
}
  return 0;
}

