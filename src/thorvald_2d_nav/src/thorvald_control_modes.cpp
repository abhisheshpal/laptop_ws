#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <cmath>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>

// ROS message includes
#include <thorvald_2d_nav/sub_goal.h>
#include <thorvald_2d_nav/landmarks.h>

nav_msgs::Odometry thorvald_estimated_pose;
geometry_msgs::Point line[2], max_line, min_line, mini_goal_pts;
double   linear_velocity = 0.2 , angular_velocity = 0;
int Total_Points = 10;
geometry_msgs::Pose Points[20];
double yaw;
geometry_msgs::Twist est_twist;
double counter_line = 0, counter_1 = 0;
double position_error, angular_error;
int c = 1;
bool mini_goal = false;
thorvald_2d_nav::sub_goal goal_count; 

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
line[1].x = line_msg->points[0].x;
line[1].y = line_msg->points[0].y;

line[2].x = line_msg->points[1].x;
line[2].y = line_msg->points[1].y;

if(counter_line == 0){
mini_goal = true;
ROS_INFO("Assigned new Sub-goal");
}
counter_line = 1;

}

}

double control_law(double v){

  double K_d = 0.5;
  double K_p = 0.1;

  if(mini_goal == true){
  mini_goal_pts.x = Points[c].position.x;
  mini_goal_pts.y = Points[c].position.y;
  mini_goal == false;
  // ROS_INFO("Assigned new Sub-goal");
  }

  // calculation of error
  double q_x =  pow((mini_goal_pts.x-thorvald_estimated_pose.pose.pose.position.x),2);
  double q_y =  pow((mini_goal_pts.y-thorvald_estimated_pose.pose.pose.position.y),2);
  position_error = sqrt(q_x + q_y);
  angular_error = (Points[c].position.y/Points[c].position.x) - yaw;

  // control law
  double omega = v * pow(cos(angular_error),3) * (-(K_d*tan(angular_error)) - (K_p*position_error));
  // omega = 0;

  if((position_error <= 0.05)){
   ROS_INFO("New Mini-Goal Initiated");
   ros::Duration(0.01).sleep();
   c = c + 1;
   //std::cout << "Points[c].position.x" << Points[c].position.x << "thorvald_estimated_pose.pose.pose.position.x" << thorvald_estimated_pose.pose.pose.position.x<< std::endl;
   mini_goal = true;
  }

  return omega;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "thorvald_control_modes");
  ros::NodeHandle n;

  // ros::Subscriber pose_sub = n.subscribe("thorvald_pose", 100, robotposeCallback);
  ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);
  ros::Subscriber finalline_sub = n.subscribe("/final_line", 100, finallineCallback);

  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);

  // Service Client
  ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/sub_goal_check");
  ros::Rate r(1.0);

  while (ros::ok()){

  ros::spinOnce();	

  if(counter_line == 1){ // generated line check
   if(counter_1 == 0){ // final min-goal check
    for(int i=1;i<=Total_Points;i++){
       Points[i].position.x = (line[1].x *(1-(float(i)/Total_Points))) + (line[2].x *(float(i)/Total_Points));
       Points[i].position.y = (line[1].y *(1-(float(i)/Total_Points))) + (line[2].y *(float(i)/Total_Points));
      // std::cout << "Points["<<i<<"].position.x" << Points[i].position.x  << std::endl;
    }

  angular_velocity = control_law (linear_velocity); 

  if((line[2].x - thorvald_estimated_pose.pose.pose.position.x) <= 0.01){
   linear_velocity = 0;
   angular_velocity = 0;
   counter_1 = 1;
   est_twist.linear.x = linear_velocity;
   est_twist.angular.z = angular_velocity;
   ROS_INFO("Final Mini-Goal Reached");
   }
   else{
    est_twist.linear.x = linear_velocity;
    }
   }// final min-goal check

   if(counter_1 == 1){
   goal_count.request.counter = 1;
   if (client.call(goal_count)){
   ROS_INFO("client request");
   counter_1 = 2;
   }
   }

   twist_gazebo.publish(est_twist);
  } // generated line check
 r.sleep();
 }
  return 0;
}
