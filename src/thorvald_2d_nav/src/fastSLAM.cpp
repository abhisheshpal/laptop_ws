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
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>
#include <random>
#include <string>
#include <assert.h>
#include "matplotlibcpp.h"

// ROS message includes
#include <thorvald_2d_nav/scan_detected_line.h>
#include <thorvald_2d_nav/landmarks.h>
#include <thorvald_2d_nav/sub_goal.h>
#include "plot_tool/PlotPose.h"

#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/transform_listener.h>

#define INF 1000
using namespace Eigen;

namespace plt = matplotlibcpp;

// Initialization for callbacks
geometry_msgs::Twist odom_vel;
nav_msgs::Odometry robot_pose;
thorvald_2d_nav::landmarks landmarks_pose;
nav_msgs::Odometry thorvald_estimated_pose;
thorvald_2d_nav::sub_goal goal_count; 
geometry_msgs::Twist twist_msg;
double measured_points_range[4], measured_points_bearing[4];
static const int total_landmarks = 4; 
double d = 0.5; // distance between two wheels
double lambda_x, lambda_y, q, dt, expectedRange, expectedBearing;
// bool landmarks_observed = false;
ros::Time current_time, last_time;
plot_tool::PlotPose xyplot, xyplot1, xyplot2, xyplot3, xyplot4, xyplot5;

//initialize velocity variables
double vx = 0.0, vy = 0.0, vth = 0.0;

// Markers
visualization_msgs::Marker landmark_strip_1, landmark_strip_2, landmark_strip_3, landmark_strip_4;
nav_msgs::Path thor_pose;

geometry_msgs::TransformStamped transformStamped;
tf::StampedTransform transform;
geometry_msgs::PoseStamped landmark_trans, landmark_transformed, robot_trans, robot_transformed;

// Initialization for SLAM
double yaw, current_yaw = 0, motion_noise = 0.00001, measurement_noise = 0.0001, sub_goal_thershold = 0.05;

MatrixXd H = MatrixXd::Zero(2,2); // H - Jacobian
MatrixXd K = MatrixXd::Zero(2,2); // Kalman gain
MatrixXd Q_t = MatrixXd::Identity(2,2)* measurement_noise; // Measurement Noise 
MatrixXd Q = MatrixXd::Zero(2,2)* measurement_noise; // Measurement Process 
MatrixXd Z = MatrixXd::Zero(2,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(2,1); // expectedZ
MatrixXd diff = MatrixXd::Zero(2,1); // error
MatrixXd line_pho = MatrixXd::Zero(4,1); // polar co-ordinates
MatrixXd line_theta = MatrixXd::Zero(4,1); // polar co-ordinates

// particle filter
static const int numParticles = 100;
double noise = 0.000005, gaussnoise = 0;
int N = numParticles;
MatrixXd w = MatrixXd::Zero(1,N);
MatrixXd num = MatrixXd::Zero(1,1);
double den;


// Particle structure
struct landmarks_struct{
bool landmarks_observed;
MatrixXd mu = MatrixXd::Zero(2,1); // mu
MatrixXd sigma = MatrixXd::Zero(2,2); // sigma
};

struct particles_struct{
MatrixXd weight = MatrixXd::Zero(1,1); // weight
geometry_msgs::PoseStamped pose;
geometry_msgs::Pose pose_history;
struct landmarks_struct landmarks[total_landmarks];
};

particles_struct particles[numParticles], old_particles[numParticles];

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
// std::cout << "measured_points_range[1]" << measured_points_range[1] << "measured_points_bearing[1]" << measured_points_bearing[1]  << std::endl;
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
    if (bearing < -M_PI) {
        bearing += 2*M_PI;
    } else if (bearing > M_PI) {
        bearing -= 2*M_PI;
    }
}

MatrixXd measurement_model(struct particles_struct *particles3, int i, int z){
 lambda_x = particles3[i].landmarks[z].mu(0) - robot_pose.pose.pose.position.x;
 lambda_y = particles3[i].landmarks[z].mu(1) - robot_pose.pose.pose.position.y;
 q = pow(lambda_x,2) + pow(lambda_y,2);

 expectedRange = sqrt(q);
 expectedBearing = normalizeangle((lambda_y/lambda_x) - yaw);
 expectedZ(0,0) = expectedRange;
 expectedZ(1,0) = expectedBearing;

 H(0,0) = (particles[i].landmarks[z].mu(0)-particles[i].pose.pose.position.x)/expectedRange;
 H(0,1) = (particles[i].landmarks[z].mu(1)-particles[i].pose.pose.position.y)/expectedRange;
 H(1,0) = (particles[i].pose.pose.position.y-particles[i].landmarks[z].mu(1))/(pow(expectedRange,2));
 H(1,1) = (particles[i].landmarks[z].mu(0)-particles[i].pose.pose.position.x)/(pow(expectedRange,2));
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

void cumsum(MatrixXd &w) 
{
    MatrixXd csumVec = MatrixXd(w);

    for (int i=0; i< w.size(); i++) {
        float sum =0;
        for (int j=0; j<=i; j++) {
	    sum+=csumVec(j);
	}			
	w(i) = sum;
    }
}

double unifRand()
{
    return rand() / double(RAND_MAX);
}

void initializate_paramters(){
 for (int i = 0; i < numParticles; i++){
 particles[i].weight(0,0) = 1/numParticles;
 particles[i].pose.pose.position.x = 0;
 particles[i].pose.pose.position.y = 0;
 particles[i].pose.pose.orientation = tf::createQuaternionMsgFromYaw(0);
 particles[i].pose_history = particles[i].pose.pose;
  for (int j = 0; j < total_landmarks; j++){
  particles[i].landmarks[j].landmarks_observed = false;
  }
 }
}

void prediction_step(struct particles_struct *particles1, double dt1, geometry_msgs::TransformStamped transformed_stamp){

 vx = robot_pose.twist.twist.linear.x;
 vy = robot_pose.twist.twist.linear.y;
 vth = robot_pose.twist.twist.angular.z;

 for (int i = 0; i < numParticles; i++){
// particles[i].pose_history = particles[i].pose;
 gaussnoise = normrnd(vth,noise);
 particles1[i].pose.header.stamp = ros::Time::now(); 	
 particles1[i].pose.pose.position.x = particles1[i].pose.pose.position.x + ((vx+gaussnoise)*dt1);
 particles1[i].pose.pose.position.y = particles1[i].pose.pose.position.y + ((vy+gaussnoise)*dt1);
 current_yaw = (current_yaw+vth+gaussnoise)*dt1;
 current_yaw = normalizeangle(current_yaw);
 particles1[i].pose.pose.orientation = tf::createQuaternionMsgFromYaw(current_yaw);
 }
// ROS_INFO("HERE");
}

void correction_step(struct particles_struct *particles2, double dt2, geometry_msgs::TransformStamped transformed_stamp){

for (int i = 0; i < numParticles; i++){

      // Landmarks observation
     for (int s = 0; s < total_landmarks; s++){

        // Transformation of Line from global co-ordinate into robot frame
      if (particles[i].landmarks[s].landmarks_observed == false){
        // line_local_2(z,0) =  line_pho(z,0) - (robot_pose.pose.pose.position.x * cos(line_theta(z,0))) - (robot_pose.pose.pose.position.y * sin(line_theta(z,0)));
        // line_local_2(z,1) =  line_theta(z,0) - yaw + (3.14/2);

         // transformation from hokuyo to map frame
         landmark_trans.header.frame_id = "hokuyo";
         landmark_trans.pose.position.x = measured_points_range[s] * cos(yaw+measured_points_bearing[s]);
         landmark_trans.pose.position.y = measured_points_range[s] * sin(yaw+measured_points_bearing[s]);
         tf2::doTransform(landmark_trans, landmark_transformed, transformed_stamp);

         particles[i].landmarks[s].mu(0) =   robot_pose.pose.pose.position.x + (landmark_transformed.pose.position.x);
         particles[i].landmarks[s].mu(1) =   robot_pose.pose.pose.position.y + (landmark_transformed.pose.position.y);
         particles[i].landmarks[s].landmarks_observed = true;
 // std::cout << "measured_points_range[0]" << measured_points_range[0] << "\n" << "measured_points_bearing[0]" << measured_points_bearing[0] << std::endl;
 // std::cout << "particles[i].landmarks["<<s<<"].mu(0)" << measured_points_range[0] * cos(measured_points_bearing[0]) << "\n" << "particles[i].landmarks["<<s<<"].mu(1)" << measured_points_range[0] *	 sin(measured_points_bearing[0])  << std::endl;
         // calculate jacobian w.r.t landmark pose
         H = measurement_model(particles,i,s);

         // initialize 2*2 EKF for current landmark 
         particles[i].landmarks[s].sigma = H.inverse() * Q_t * (H.inverse()).transpose(); //CHECK
         particles[i].weight(0,0) = 0.5;
      }

     else{
         Z(0,0) = measured_points_range[s];
         Z(1,0) = measured_points_bearing[s];

         // calculate jacobian w.r.t landmark pose
         H = measurement_model(particles,i,s);

         Q = (H*particles[i].landmarks[s].sigma*H.transpose()) + Q_t;

         // Kalman Gain
         K = (particles[i].landmarks[s].sigma*H.transpose()) * (Q.inverse());

         // Compute the diference between the expected and recorded measurements.
         diff = Z - expectedZ;
         diff(1) = normalizeangle(diff(1));
         // std::cout << "K" << K << "\n" << "diff" << diff << std::endl;
	 // Finish the correction step by computing the new mu and sigma.
         particles[i].landmarks[s].mu = particles[i].landmarks[s].mu + K*diff;
         particles[i].landmarks[s].sigma = (MatrixXd::Identity(2,2)- K*H)*particles[i].landmarks[s].sigma;


        // Particle Weight
        den = 2*M_PI*sqrt(Q.determinant()); 
        num = (-0.5* diff.transpose() * Q.inverse() * diff).exp(); 
        particles[i].weight = particles[i].weight * (num/den); 
       }
      }	
// std::cout << "particles1[i].pose.position.y:" << particles1[1].pose.position.y << "\n"  << "current_yaw:" << current_yaw << "\n" << std::endl;
 }
        // ROS_INFO("HERE1");
}

void resample(struct particles_struct *particles4, double dt4){

// initializations
int Nmin = 0.75*N;
int doresample = 1;
int len;
double ws, wsum, Neff = 0;
std::vector<int> keep;
MatrixXd wsqrd = MatrixXd::Zero(1,N);
std::vector<float> select;
std::vector<float>::iterator diter; 
float k, temp, new_w;
int ctr=0;

for(int i=0;i<N;i++){
w(i)= particles4[i].weight(0,0);}
ws = w.sum(); 
// assert(ws!=0);

for (int i=0;i<N;i++){
w(i)= w(i)/ws;}

for (int i=0;i<N;i++){
particles4[i].weight(0,0)= (particles4[i].weight(0,0)/ws);}

// stratified_resample 
wsum = w.sum(); 

for (int i=0;i<w.size();i++){
w(i)= w(i)/wsum; // normalise
wsqrd(i) = (float)pow(w(i),2);
}

Neff= 1.0f/(float)wsqrd.sum(); 

len= w.size();
keep.resize(len);
for (int i=0; i<len; i++){
keep[i] = -1;
}

// stratified_random 
 k = 1.0/float(len);
    //deterministic intervals
    temp = k/2;
    select.push_back(temp);
    while (temp < 1-k/2) {
        temp = temp+k;
        select.push_back(temp);
    }

    //dither within interval
    for (diter = select.begin(); diter != select.end(); diter++) {
        *diter = (*diter) + unifRand() * k - (k/2);
    }

    cumsum(w); 

    for (int i=0; i<len; i++) {
        while ((ctr<len) && (select[ctr]<w(i))) {
            keep[ctr] = i;
            ctr++;
        }
    }

// straified resample ends
for (int i=0; i<N; i++) {
old_particles[i] = particles[i];
}
// ROS_INFO("HERE2");
    if ((Neff < Nmin) && (doresample == 1)) {
        for(int i=0; i< keep.size(); i++) {
            particles[i] = old_particles[keep[i]]; 	
        }	
        for (int i=0; i<N; i++) {
            new_w = 1.0f/(float)N;
            assert(std::isfinite(new_w));
            assert(N == 100);
            particles[i].weight(0,0) = new_w;
        }
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

  // Publishers
  ros::Publisher thorvald_pose_pub = n.advertise<geometry_msgs::PoseStamped>("thorvald_pose", 10);
  ros::Publisher thorvald_path_pub = n.advertise<nav_msgs::Path>("thorvald_path", 10);
  ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("landmark_marker_1", 10);
  ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("landmark_marker_2", 10);
  ros::Publisher marker_pub_3 = n.advertise<visualization_msgs::Marker>("landmark_marker_3", 10);
  ros::Publisher marker_pub_4 = n.advertise<visualization_msgs::Marker>("landmark_marker_4", 10);

  //Service Client
  // ros::ServiceClient pose_srv_h = n.serviceClient<plot_tool::PlotPose>("plot_tool/draw_pose");
  // ros::ServiceClient pose_srv_h1 = n.serviceClient<plot_tool::PlotPose>("plot_tool/draw_pose");

  current_time = ros::Time::now();
  last_time = ros::Time::now();
  int init = 0;
  std::vector<double> weights_total;
  int max_weight;

  tf::TransformListener listener;
  tf2_ros::Buffer tfBuffer; 
  tf2_ros::TransformListener tfListener(tfBuffer);

  while (ros::ok()){

  ros::spinOnce();
  current_time = ros::Time::now();
  dt = (current_time - last_time).toSec();

  // initialization step
  if(init==0){
  initializate_paramters();
  init = 1;}

  if (landmarks_pose.landmark_check > 0){  // robot static check

  try{
  transformStamped = tfBuffer.lookupTransform("map", "hokuyo", ros::Time(0));
  }
  catch (tf2::TransformException &ex){
  ROS_WARN("%s",ex.what());
  ros::Duration(1.0).sleep();
  } 

  // prediction step
  prediction_step(particles, dt, transformStamped);

  // correction step
  correction_step(particles, dt, transformStamped);

  // resampling step
  resample(particles, dt);

  for (int i=0; i<N; i++) {
  weights_total.push_back(particles[i].weight(0,0));
  }

  max_weight = (ceil)(*(std::max_element(weights_total.begin(), weights_total.end())));

        thor_pose.header.frame_id = "/map";
        thor_pose.poses.push_back(particles[max_weight].pose);

        landmark_strip_1.header.frame_id = "/map";
        landmark_strip_1.action = visualization_msgs::Marker::ADD;
        landmark_strip_1.pose.position.x = particles[1].landmarks[0].mu(0);
        landmark_strip_1.pose.position.y = particles[1].landmarks[0].mu(1);
        landmark_strip_1.pose.position.z = 0.75;
        landmark_strip_1.pose.orientation.w = 1.0;
        landmark_strip_1.type = visualization_msgs::Marker::CYLINDER;
        landmark_strip_1.lifetime = ros::Duration(0.1);
        landmark_strip_1.id = 1;
        landmark_strip_1.scale.x = 0.1;
        landmark_strip_1.scale.y = 0.1;
        landmark_strip_1.scale.z = 0.2;
        landmark_strip_1.color.g = 1.0;
        landmark_strip_1.color.a = 1.0;

        landmark_strip_2.header.frame_id = "/map";
        landmark_strip_2.action = visualization_msgs::Marker::ADD;
        landmark_strip_2.pose.position.x = particles[max_weight].landmarks[1].mu(0);
        landmark_strip_2.pose.position.y = particles[max_weight].landmarks[1].mu(1);
        landmark_strip_2.pose.position.z = 0.75;
        landmark_strip_2.pose.orientation.w = 1.0;
        landmark_strip_2.type = visualization_msgs::Marker::CYLINDER;
        landmark_strip_2.lifetime = ros::Duration(0.1);
        landmark_strip_2.id = 1;
        landmark_strip_2.scale.x = 0.1;
        landmark_strip_2.scale.y = 0.1;
        landmark_strip_2.scale.z = 0.2;
        landmark_strip_2.color.g = 1.0;
        landmark_strip_2.color.a = 1.0;

        landmark_strip_3.header.frame_id = "/map";
        landmark_strip_3.action = visualization_msgs::Marker::ADD;
        landmark_strip_3.pose.position.x = particles[max_weight].landmarks[2].mu(0);
        landmark_strip_3.pose.position.y = particles[max_weight].landmarks[2].mu(1);
        landmark_strip_3.pose.position.z = 0.75;
        landmark_strip_3.pose.orientation.w = 1.0;
        landmark_strip_3.type = visualization_msgs::Marker::CYLINDER;
        landmark_strip_3.lifetime = ros::Duration(0.1);
        landmark_strip_3.id = 1;
        landmark_strip_3.scale.x = 0.1;
        landmark_strip_3.scale.y = 0.1;
        landmark_strip_3.scale.z = 0.2;
        landmark_strip_3.color.g = 1.0;
        landmark_strip_3.color.a = 1.0;

        landmark_strip_4.header.frame_id = "/map";
        landmark_strip_4.action = visualization_msgs::Marker::ADD;
        landmark_strip_4.pose.position.x = particles[max_weight].landmarks[3].mu(0);
        landmark_strip_4.pose.position.y = particles[max_weight].landmarks[3].mu(1);
        landmark_strip_4.pose.position.z = 0.75;
        landmark_strip_4.pose.orientation.w = 1.0;
        landmark_strip_4.type = visualization_msgs::Marker::CYLINDER;
        landmark_strip_4.lifetime = ros::Duration(0.1);
        landmark_strip_4.id = 1;
        landmark_strip_4.scale.x = 0.1;
        landmark_strip_4.scale.y = 0.1;
        landmark_strip_4.scale.z = 0.2;
        landmark_strip_4.color.g = 1.0;
        landmark_strip_4.color.a = 1.0;


        landmark_strip_1.header.stamp = ros::Time::now();
        landmark_strip_2.header.stamp = ros::Time::now();
        landmark_strip_3.header.stamp = ros::Time::now();
        landmark_strip_4.header.stamp = ros::Time::now();
        thor_pose.header.stamp = ros::Time::now();

 /* xyplot.request.msg.position.x = particles[max_weight].pose.position.y;
  xyplot.request.msg.position.y = particles[max_weight].pose.position.x;
  xyplot.request.append=true;
  xyplot.request.series= 0;
  xyplot.request.symbol= 's';
  xyplot.request.symbol_size= 5;

  xyplot1.request.msg.position.x = robot_pose.pose.pose.position.y;
  xyplot1.request.msg.position.y = robot_pose.pose.pose.position.x;
  xyplot1.request.append=true;
  xyplot1.request.series= 2;
  xyplot1.request.symbol= 's';
  xyplot1.request.symbol_size= 5;

  xyplot2.request.msg.position.x = particles[max_weight].landmarks[0].mu(0,0);
  xyplot2.request.msg.position.y = particles[max_weight].landmarks[0].mu(1,0);
  xyplot2.request.append=false;
  xyplot2.request.series= 1;
  xyplot2.request.symbol= 's';
  xyplot2.request.symbol_size= 5;
  xyplot3.request.msg.position.x = particles[max_weight].landmarks[1].mu(0,0);
  xyplot3.request.msg.position.y = particles[max_weight].landmarks[1].mu(1,0);
  xyplot3.request.append=false;
  xyplot3.request.series= 1;
  xyplot3.request.symbol= 's';
  xyplot3.request.symbol_size= 5;
  xyplot4.request.msg.position.x = particles[max_weight].landmarks[2].mu(0,0);
  xyplot4.request.msg.position.y = particles[max_weight].landmarks[2].mu(1,0);
  xyplot4.request.append=false;
  xyplot4.request.series= 1;
  xyplot4.request.symbol= 's';
  xyplot4.request.symbol_size= 5;
  xyplot5.request.msg.position.x = particles[max_weight].landmarks[3].mu(0,0);
  xyplot5.request.msg.position.y = particles[max_weight].landmarks[3].mu(1,0);
  xyplot5.request.append=false;
  xyplot5.request.series= 1;
  xyplot5.request.symbol= 's';
  xyplot5.request.symbol_size= 5;

  pose_srv_h.call(xyplot);
  pose_srv_h.call(xyplot1);
  pose_srv_h.call(xyplot2);
  pose_srv_h.call(xyplot3);
  pose_srv_h.call(xyplot4);
  pose_srv_h.call(xyplot5);
  // pose_srv_h1.call(xyplot1);
  // ros::Duration(0.05).sleep(); */

  thorvald_pose_pub.publish(particles[max_weight].pose); 
  thorvald_path_pub.publish(thor_pose);
  marker_pub_1.publish(landmark_strip_1);	
  marker_pub_2.publish(landmark_strip_2);	
  marker_pub_3.publish(landmark_strip_3);	
  marker_pub_4.publish(landmark_strip_4);	
  } // robot static check

  last_time = current_time;
  r.sleep();
}
  return 0;
}


