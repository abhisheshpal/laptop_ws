#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>
#include <cmath>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>

nav_msgs::Odometry thorvald_estimated_pose;
geometry_msgs::Point line[2];
double   linear_velocity = 0.1 , angular_velocity = 0;
int Total_Points = 20;
geometry_msgs::Pose Points[20];
double yaw;
geometry_msgs::Twist est_twist;
double counter = 0, counter_1 = 0;
double position_error, angular_error;

// Thorvald Estimated Pose data
void robotposeCallback (const nav_msgs::Odometry::ConstPtr& pose_msg)
{
thorvald_estimated_pose.pose.pose.position = pose_msg->pose.pose.position;
thorvald_estimated_pose.pose.pose.orientation = pose_msg->pose.pose.orientation;

tf::Quaternion quat(thorvald_estimated_pose.pose.pose.orientation.x,thorvald_estimated_pose.pose.pose.orientation.y, thorvald_estimated_pose.pose.pose.orientation.z, thorvald_estimated_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

//line points 
void finallineCallback (const visualization_msgs::Marker::ConstPtr& line_msg)
{

if (line_msg->points.size() > 0){        
line[1].x = line_msg->points[1].x;
line[1].y = line_msg->points[1].y;

line[2].x = line_msg->points[2].x;
line[2].y = line_msg->points[2].y;
counter = 1;
}

}

double control_law(double v){

   // split the line into segment of points
   for(int i=0;i<Total_Points;i++){
        Points[i].position.x = line[1].x * (1 - (i/Total_Points)) + line[2].x * (i / Total_Points);
        Points[i].position.y =line[1].y * (1 - (i/Total_Points)) + line[2].y * (i / Total_Points);
    }

 // linear_velocity = 0.1; // angluar velocity
  double K_d = 0.5;
  double K_p = 0.1;

  // calculation of error
  double q_x =  pow((2.1-thorvald_estimated_pose.pose.pose.position.x),2);
  double q_y =  pow((-0.08-thorvald_estimated_pose.pose.pose.position.y),2);
  position_error = sqrt(q_x + q_y);
  angular_error = (0.08/0.26) - yaw;
std::cout << "position_error" << position_error << std::endl;
  // control law
  double omega = v * pow(cos(angular_error),3) * (-(K_d*tan(angular_error)) - (K_p*position_error));
 // omega = 0;
//std::cout << "v:" << v << std::endl;
 /* if((position_error < 0.01) && (angular_error < 0.01)){
  v = 0;
  omega = 0;
  }*/
  return omega;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "thorvald_control_modes");
  ros::NodeHandle n;

  // ros::Subscriber pose_sub = n.subscribe("thorvald_pose", 100, robotposeCallback);
  ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);
  ros::Subscriber finalline_sub = n.subscribe("final_line", 100, finallineCallback);

  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);
  ros::Rate r(1.0);

  while (ros::ok()){

  ros::spinOnce();	

  if(counter == 1){
  
  if(counter_1 == 0){
  angular_velocity = control_law (linear_velocity); 
  }

  if((position_error < 0.2)){
  linear_velocity = 0;
  angular_velocity = 0;
  counter_1 = 1;
  }
std::cout << "angular_velocity" << angular_velocity << std::endl;
  est_twist.linear.x = linear_velocity;
  //est_twist.angular.z = angular_velocity;
  twist_gazebo.publish(est_twist);

   }

   else{
  est_twist.linear.x = 0.0;
  est_twist.angular.z = 0.0;
  twist_gazebo.publish(est_twist);
   }

  r.sleep();
  }

  return 0;

}
