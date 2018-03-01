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

using namespace Eigen;

thorvald_2d_nav::landmarks landmarks_pos;
double line_1_pho, line_1_theta, line_2_pho, line_2_theta, line_3_pho, line_3_theta, line_4_pho, line_4_theta, lambda_x, lambda_y, q, diff_line_pho, diff_line_theta;
nav_msgs::Odometry robot_pose;
geometry_msgs::Twist twist_msg;
int count_1, count_2 = 0;

// Initialization
int total_landmarks = 4; 
// std::cout << "fhmr" << std::endl;

MatrixXd cov = MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3)); // covariance
MatrixXd line_local(4,2); // line_local
MatrixXd line_local_fixed(4,2); // line_local_fixed
MatrixXd R = MatrixXd::Zero((2*total_landmarks+3),(2*total_landmarks+3)); // Motion Noise
MatrixXd R3 = MatrixXd::Identity(3,3); // Motion Noise
MatrixXd Z = MatrixXd::Zero(8,1); // Z
MatrixXd expectedZ = MatrixXd::Zero(8,1); // expectedZ
MatrixXd Q = MatrixXd::Zero(8,8); // Measurement Noise
MatrixXd K = MatrixXd::Zero((2*total_landmarks+3),2); // Kalman gain
MatrixXd diff = MatrixXd::Zero(2,2); // error
MatrixXd H = MatrixXd::Zero(2*total_landmarks,(2*total_landmarks+3)); // H - Jacobian
MatrixXd line_pho = MatrixXd::Zero(4,1); // polar co-ordinates
MatrixXd line_theta = MatrixXd::Zero(4,1); // polar co-ordinates
double measured_points_range[4];
double measured_points_bearing[4];
float motion_noise = 0.01;
float measurement_noise = 0.01;
double sub_goal_thershold = 0.05;
bool landmarks_observed = false;
geometry_msgs::Pose thorvald_estimated_pose;
thorvald_2d_nav::sub_goal goal_count; 
double yaw;
geometry_msgs::Twist odom_vel;

        //initialize velocity variables
       double vx = 0.0;
       double vy = 0.0;
       double vth = 0.0;
   
double d = 0.5; // distance between two wheels

double normalizeangle(double bearing);
// MatrixXd prediction_step(MatrixXd mu_1,MatrixXd cov_1, MatrixXd line_local_1);
// MatrixXd correction_step(MatrixXd mu_2,MatrixXd cov_2, MatrixXd line_local_2);

// robot velocity data
void odometryvelCallback (const geometry_msgs::Twist::ConstPtr& odometry_vel){

odom_vel.linear.x = odometry_vel->linear.x;
odom_vel.linear.y = odometry_vel->linear.y;
// count_1 = count_1 + 1;

}

// robot pose data
void odometryCallback (const nav_msgs::Odometry::ConstPtr& odometry){

robot_pose.pose.pose.position.x = odometry->pose.pose.position.x;
robot_pose.pose.pose.position.y = odometry->pose.pose.position.y;
robot_pose.pose.pose.orientation = odometry->pose.pose.orientation;
robot_pose.twist.twist.linear.x = odometry->twist.twist.linear.x;
robot_pose.twist.twist.angular.z = odometry->twist.twist.angular.x;

tf::Quaternion quat(robot_pose.pose.pose.orientation.x,robot_pose.pose.pose.orientation.y, robot_pose.pose.pose.orientation.z, robot_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

// count_1 = count_1 + 1;

}

//line point data
void linepointsCallback(const thorvald_2d_nav::scan_detected_line::ConstPtr& line_points){

if (line_points->range.size() > 0){
for (int num = 0; num < total_landmarks; num++){
measured_points_range[num] = line_points->range[num];
measured_points_bearing[num] = line_points->bearing[num];
}}

}

// line_marker_1 data
void leftlineCallback (const visualization_msgs::Marker::ConstPtr& line_1){

if(line_1->points.size() > 0){
landmarks_pos.pt_1.x = line_1->points[1].x;
landmarks_pos.pt_1.y = line_1->points[1].y;
landmarks_pos.pt_2.x = line_1->points[2].x;
landmarks_pos.pt_2.y = line_1->points[2].y;
}

line_pho(0,0) = sqrt(pow(landmarks_pos.pt_1.x,2) + pow(landmarks_pos.pt_1.y,2));
line_theta(0,0) = atan2(landmarks_pos.pt_1.y,landmarks_pos.pt_1.x);
line_pho(1,0) = sqrt(pow(landmarks_pos.pt_2.x,2) + pow(landmarks_pos.pt_2.y,2));
line_theta(1,0) = atan2(landmarks_pos.pt_2.y,landmarks_pos.pt_2.x);

count_1 = count_1 + 1;

}

// line_marker_2 data
void rightlineCallback (const visualization_msgs::Marker::ConstPtr& line_2){

if(line_2->points.size() > 0){
landmarks_pos.pt_3.x = line_2->points[1].x;
landmarks_pos.pt_3.y = line_2->points[1].y;
landmarks_pos.pt_4.x = line_2->points[2].x;
landmarks_pos.pt_4.y = line_2->points[2].y;
}

line_pho(2,0) = sqrt(pow(landmarks_pos.pt_3.x,2) + pow(landmarks_pos.pt_3.y,2));
line_theta(2,0) = atan2(landmarks_pos.pt_3.y,landmarks_pos.pt_3.x);
line_pho(3,0) = sqrt(pow(landmarks_pos.pt_4.x,2) + pow(landmarks_pos.pt_4.y,2));
line_theta(3,0) = atan2(landmarks_pos.pt_4.y,landmarks_pos.pt_4.x);

count_1 = count_1 + 1;

}

double normalizeangle(double bearing){

if (bearing > M_PI){
bearing = M_PI;
}

if(bearing < -M_PI){
bearing = -M_PI;
}

}

//prediction step
void prediction_step(MatrixXd& mu1,MatrixXd& cov1,MatrixXd& line_local1,MatrixXd& line_local_fixed1,double dt){

      vx = (odom_vel.linear.x + odom_vel.linear.y)/2;
      vy = 0.0;
      vth = (odom_vel.linear.y - odom_vel.linear.x)/d;

      // Odometry Compensation 
      double delta_x = (vx * cos(mu1(2,0)) - vy * sin(mu1(2,0))) * dt;
      double delta_y = (vx * sin(mu1(2,0)) + vy * cos(mu1(2,0))) * dt;
      double delta_th = vth * dt;

      mu1(0,0) = mu1(0,0) + delta_x;
      mu1(1,0) = mu1(1,0) + delta_y;
      mu1(2,0) = mu1(2,0) + delta_th;
      // mu(2,0)= normalizeangle(mu(2,0));

      // std::cout << "x" << "\t" << mu1(0,0) << "\t" << "y" << "\t" << mu1(2,0) << std::endl;
//--------------------JACOBIAN NEEDED TO BE CALCULATED--------------//

      // Gtx = [0 0 -robot_pose.twist.twist.linear.x*sin(mu_1(1,3)); 0 0 robot_pose.twist.twist.linear.y*sin(mu_1(1,3)); 0 0 0]];

      // cov1(1,1) = 1;  // ***need to calculate*** //
      cov(0,2) = -vx * sin(mu1(2,0)) - vy * cos(mu1(2,0));
      // cov1(2,2) = 1; 
      cov(1,2) = vx * cos(mu1(2,0)) - vy * sin(mu1(2,0));
      // cov1(3,3) = 1; 

      cov(0,0) += R3(0,0) * motion_noise;
      cov(1,1) += R3(1,1) * motion_noise;
      cov(2,2) += R3(2,2) * motion_noise/10;
                  
      // cov1 = cov1 + R; // Motion Noise

}

//correction step
MatrixXd correction_step(MatrixXd mu_2,MatrixXd cov_2, MatrixXd line_local_2, MatrixXd line_local_fixed_2, double dt){

      // if (i == 1){
            
      // Landmarks observation
     for (int z = 0; z < total_landmarks; z++){

        // Transformation of Line from global co-ordinate into robot frame
      if (landmarks_observed == false){
        line_local_2(z,0) =  line_pho(z,0) - (robot_pose.pose.pose.position.x * cos(line_theta(z,0))) - (robot_pose.pose.pose.position.y * sin(line_theta(z,0)));
        line_local_2(z,1) =  line_theta(z,0) - yaw + (3.14/2);
        if (z == total_landmarks){ landmarks_observed = true;}
      }

      Z(2*z,0) = measured_points_range[z];
      Z((2*z)+1,0) = measured_points_bearing[z];

      lambda_x = line_local_2(z,0) - robot_pose.pose.pose.position.x;
      lambda_y = line_local_2(z,1) - robot_pose.pose.pose.position.y;
      q = pow(lambda_x,2) + pow(lambda_y,2);


      double expectedRange = sqrt(q);
      double expectedBearing = normalizeangle((lambda_y/lambda_x) - yaw);
      expectedZ(2*z,0) = expectedRange;
      expectedZ((2*z)+1,0) = expectedBearing;

      // Compute the Jacobian H of the measurement function h wrt the landmark location
       H((2*z),0) = 1/q * (-sqrt(q)*lambda_x);
       H((2*z)+1,0) = 1/q * lambda_y;
       H((2*z),1) = 1/q * (-sqrt(q)*lambda_y);
       H((2*z)+1,1) = 1/q * (-lambda_y);
       H((2*z),2) = 0;
       H((2*z)+1,2) = -q;

       H((2*z),2*z+3) = 1/q * (sqrt(q)*lambda_x);
       H((2*z)+1,2*z+3) = 1/q * (-lambda_y);
       H((2*z),2*z+4) = 1/q * (sqrt(q)*lambda_y);
       H((2*z)+1,2*z+4) = 1/q * (lambda_x);       
      }	
		
      // Compute the Kalman gain
       K = cov_2*H.transpose()*(H*cov_2*H.transpose() + Q).inverse();
 
        // Compute the diference between the expected and recorded measurements.
       diff = Z - expectedZ;
        // diff = normalize_all_bearings(diff);

	// Finish the correction step by computing the new mu and sigma.
       mu_2 = mu_2 + K*diff;
       cov_2 =  (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*cov_2 ;
       // mu_2(2,0)= normalizeangle(mu_2(2,0));
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "thorvald_line_SLAM");
	ros::NodeHandle n;

        ros::Rate r(20.0);

        // Subscribers
        ros::Subscriber line_1_sub = n.subscribe("line_marker_1", 100, leftlineCallback);
	ros::Subscriber line_2_sub = n.subscribe("line_marker_2", 100, rightlineCallback);
	ros::Subscriber odom_sub = n.subscribe("/odometry/wheel", 100, odometryCallback);
	ros::Subscriber odom_vel_sub = n.subscribe("/odom_topic", 50, odometryvelCallback);
	ros::Subscriber point_sub = n.subscribe("measurement_points", 100, linepointsCallback);

        // Publishers
       ros::Publisher thorvald_pose_pub = n.advertise<geometry_msgs::Pose>("thorvald_pose", 10);

        // Servic Client
       ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("sub_goal_check");

       MatrixXd mu = MatrixXd::Zero(2*total_landmarks+3,1); // mu

       ros::Time current_time, last_time;
       current_time = ros::Time::now();
       last_time = ros::Time::now();

        while (ros::ok()){
        
      ros::spinOnce();	

      current_time = ros::Time::now();
      double dt = (current_time - last_time).toSec();

      // if(count_1 > 0){
/*
      current_time = ros::Time::now();
      vx = (odom_vel.linear.x + odom_vel.linear.y)/2;
      vy = 0.0;
      vth = (odom_vel.linear.y - odom_vel.linear.x)/d;

      // Odometry Compensation 
      double dt = (current_time - last_time).toSec();
      double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
      double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
      double delta_th = vth * dt;

      mu(0,0) = mu(0,0) + delta_x;
      mu(1,0) = mu(1,0) + delta_y;
      mu(2,0) = mu(2,0) + delta_th;
      // mu(2,0)= normalizeangle(mu(2,0));
       // x = x + delta_x;
       // y = y + delta_y;
       //th = th + delta_th;
      std::cout << "x" << "\t" << mu(0,0) << "\t" << "y" << "\t" << mu(2,0) << std::endl;
//--------------------JACOBIAN NEEDED TO BE CALCULATED--------------//

      // Gtx = [0 0 -robot_pose.twist.twist.linear.x*sin(mu_1(1,3)); 0 0 robot_pose.twist.twist.linear.y*sin(mu_1(1,3)); 0 0 0]];

      // cov1(1,1) = 1;  // ***need to calculate*** //
      cov(0,2) = -robot_pose.twist.twist.linear.x * sin(mu(2,0)) - robot_pose.twist.twist.linear.y * cos(mu(2,0));
      // cov1(2,2) = 1; 
      cov(1,2) = robot_pose.twist.twist.linear.x * cos(mu(2,0)) - robot_pose.twist.twist.linear.y * sin(mu(2,0));
      // cov1(3,3) = 1; 

      cov(0,0) = R3(0,0) * motion_noise;
      cov(1,1) = R3(1,1) * motion_noise;
      cov(2,2) = R3(2,2) * motion_noise/10;
                  
       // for (int i = 1; i <= 5; i++){ // ****change this timestep*** //
*/
       // prediction step
         prediction_step(mu, cov, line_local, line_local_fixed, dt);
 
       // correction step
       // correction_step(mu, cov, line_local, line_local_fixed, dt);
             // std::cout << "mu_x" << "\t" << mu(0,0) << "\t" << mu_y" << "\t" << mu(1,0) << std::endl;
       // }

       // count_1 = 0;

      //  }

   // Robot pose estimation
   thorvald_estimated_pose.position.x = mu(0,0);
   thorvald_estimated_pose.position.y = mu(1,0);
   geometry_msgs::Quaternion q = tf::createQuaternionMsgFromYaw(mu(2,0));
   thorvald_estimated_pose.orientation = q;

   // sub-goal check
   double goal = std::max(landmarks_pos.pt_1.x,landmarks_pos.pt_2.x);
   if ((thorvald_estimated_pose.position.x - goal) < sub_goal_thershold){  //sub-goal thershold
   goal_count.request.counter = 1;
   }

  thorvald_pose_pub.publish(thorvald_estimated_pose); 
  last_time = current_time;
  r.sleep();
  } 
  return 0;
}
