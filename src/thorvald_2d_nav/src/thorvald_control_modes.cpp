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
int Total_Points = 15;
geometry_msgs::Pose Points[20];
geometry_msgs::Twist est_twist;
double counter_line = 0, counter_1 = 0, line_count = 0;
double yaw, position_error, angular_error, q_x , q_y;
int c = 1;
double K_d = 0.01, K_p = 0.01;
bool mini_goal = false;
thorvald_2d_nav::sub_goal goal_count; 
thorvald_2d_nav::landmarks landmarks_pose;

// Thorvald Estimated Pose data
void robotposeCallback (const nav_msgs::Odometry::ConstPtr& pose_msg)
{
thorvald_estimated_pose.pose.pose.position = pose_msg->pose.pose.position;
thorvald_estimated_pose.pose.pose.orientation = pose_msg->pose.pose.orientation;

tf::Quaternion quat(thorvald_estimated_pose.pose.pose.orientation.x,thorvald_estimated_pose.pose.pose.orientation.y, thorvald_estimated_pose.pose.pose.orientation.z, thorvald_estimated_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

/*//line points 
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

}*/


//line points 
void landmarksposeCallback (const thorvald_2d_nav::landmarks::ConstPtr& landmarks_msg)
{

if (landmarks_msg->landmark_check > 0){        
landmarks_pose.pt_5.x = landmarks_msg->pt_5.x;
landmarks_pose.pt_5.y = landmarks_msg->pt_5.y;

landmarks_pose.pt_6.x = landmarks_msg->pt_6.x;
landmarks_pose.pt_6.y = landmarks_msg->pt_6.y;
landmarks_pose.landmark_check = landmarks_msg->landmark_check;
counter_line = 1;
}

}


double control_law(double v){

  // calculation of error
  q_x =  mini_goal_pts.x-thorvald_estimated_pose.pose.pose.position.x;
  q_y =  mini_goal_pts.y-thorvald_estimated_pose.pose.pose.position.y;
  position_error = sqrt(pow(q_x,2) + pow(q_y,2));
  angular_error = atan2(q_y,q_x)- yaw;

  // control law
  double robotlength = 1.1;
//  double omega = atan(2*robotlength*sin(angular_error))/position_error;
  double omega = v * pow(cos(angular_error),3) * (-(K_d*tan(angular_error)) - (K_p*position_error));

  if (omega > 3.14) 
  {
  omega -= 3.14;
  }
  if (omega < -3.14)
  {
  omega += 3.14;
  }

  if((position_error <= 0.1) && (omega <= 0.1)&& (c<=Total_Points)){
   // ROS_INFO("New Mini-Goal Initiated");
   // ros::Duration(0.01).sleep();
   mini_goal_pts.x = Points[c].position.x;
   mini_goal_pts.y = Points[c].position.y;
   c = c + 1;
   mini_goal = true;
  }

  return omega;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "thorvald_control_modes");
  ros::NodeHandle n;

  ros::Subscriber landmarks_sub = n.subscribe("landmark_points", 100, landmarksposeCallback);
  ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);
  // ros::Subscriber finalline_sub = n.subscribe("/final_line", 100, finallineCallback);

  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);

  // Service Client
  ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/sub_goal_check");

  ros::Rate r(1.0);
  double linear_velocity = 0.1, angular_velocity = 0;

  while (ros::ok()){

  ros::spinOnce();	

  if(landmarks_pose.landmark_check > line_count){
   line_count = landmarks_pose.landmark_check;

    for(int i=1;i<=Total_Points;i++){
    Points[i].position.x = (thorvald_estimated_pose.pose.pose.position.x *(1-(float(i)/Total_Points))) + ((landmarks_pose.pt_6.x*0.8) *(float(i)/Total_Points));
    Points[i].position.y = (thorvald_estimated_pose.pose.pose.position.y *(1-(float(i)/Total_Points))) + ((landmarks_pose.pt_6.y*0.8) *(float(i)/Total_Points));
      // std::cout << "Points["<<i<<"].position.x" << Points[i].position.x  << std::endl;
    }

  mini_goal_pts.x = Points[1].position.x;
  mini_goal_pts.y = Points[1].position.y;
  mini_goal = true;
  counter_1 = 0;
  ROS_INFO("Assigned new Sub-goal");
  }

  if(counter_line > 0){ // generated line check
   if(mini_goal==true){ // final min-goal check

   angular_velocity = control_law(linear_velocity); // control law

   std::cout << "angular_velocity:" << angular_velocity << "\n" << "mini_goal_pts.x:" << mini_goal_pts.x << "\n"  << "thorvald_estimated_pose.pose.pose.position.x:" << thorvald_estimated_pose.pose.pose.position.x << "\n" << std::endl;
   // std::cout << "landmarks_pose.pt_6.x:" << landmarks_pose.pt_6.x <<"\n" << "thorvald_estimated_pose.pose.pose.position.x:" << thorvald_estimated_pose.pose.pose.position.x <<"\n"<< std::endl;

   if((Points[Total_Points].position.x - thorvald_estimated_pose.pose.pose.position.x) <= 0.10){
   linear_velocity = 0;
   angular_velocity = 0;
   counter_1 = 1;
   mini_goal = false;
   est_twist.linear.x = linear_velocity;
   est_twist.angular.z = angular_velocity;
   ROS_INFO("Final Mini-Goal Reached");
   c = 1;
   }
   else{
   est_twist.linear.x = 0.05;
   est_twist.angular.z = angular_velocity;
    } 
   }// final min-goal check

   if(counter_1 == 1){
   goal_count.request.counter = 1;
   if (client.call(goal_count)){
   // ROS_INFO("client request");
   counter_1 = 2;
   }}

   twist_gazebo.publish(est_twist);
  } // generated line check
 r.sleep();
 }
  return 0;
}
