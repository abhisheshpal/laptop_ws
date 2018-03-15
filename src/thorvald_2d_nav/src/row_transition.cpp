#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <algorithm>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/tf.h>
#include <cmath>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>

geometry_msgs::Twist est_twist;
double yaw;
nav_msgs::Odometry thorvald_estimated_pose;
double thorvald_position_x, thorvald_position_y;

// Parameters for pole detection
float fwSpeed = 0, sum_x_1 = 0, sum_y_1 = 0, sum_x_2 = 0, sum_y_2 = 0;
float final_x_1, final_y_1, final_x_2, final_y_2;
int m = 0, k = 0, q = 0, count_1 = 0, count_2 = 0, smallest_iteration_1 = 0, smallest_iteration_2 = 0;
float array[1080][2]; 
double Current_x_1, Current_y_1, Current_x_2, Current_y_2, final_range_1, final_range_2, smallest_range_1, smallest_range_2;
double range_1[1080], range_2[1080], count_angle_1[1080], count_angle_2[1080];
ros::Subscriber scan_sub;
double x[1080], y[1080], angle[1080];
double min_range = 2.0;
sensor_msgs::LaserScan scan_msg_main;
int initial_count_1 = 1, initial_count_2 = 1;

// Pole Markers
visualization_msgs::Marker marker_1;
visualization_msgs::Marker marker_2;
visualization_msgs::Marker marker_goal;
ros::Publisher vis_pub_1, vis_pub_2, vis_pub_3;

// Laser Scan data
void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
        // size_t num_ranges = scan_msg->ranges.size();
        scan_msg_main.header.stamp = scan_msg->header.stamp;
        scan_msg_main.ranges = scan_msg->ranges;
        scan_msg_main.angle_min = scan_msg->angle_min;
        scan_msg_main.angle_increment = scan_msg->angle_increment;

} // callback end

// Thorvald Estimated Pose data
void robotposeCallback (const nav_msgs::Odometry::ConstPtr& pose_msg)
{
thorvald_estimated_pose.pose.pose.position = pose_msg->pose.pose.position;
thorvald_estimated_pose.pose.pose.orientation = pose_msg->pose.pose.orientation;

tf::Quaternion quat(thorvald_estimated_pose.pose.pose.orientation.x,thorvald_estimated_pose.pose.pose.orientation.y, thorvald_estimated_pose.pose.pose.orientation.z, thorvald_estimated_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

// Pole detection
void Pole_detection(sensor_msgs::LaserScan scan_msg_poles){

double thershold = 0.02000;

//---------------------- FIRST HALF ---------------------------//
	for (int i = 1; i <= 540; i++){
			angle[i] = scan_msg_poles.angle_min+i*scan_msg_poles.angle_increment;
			x[i] = scan_msg_poles.ranges[i]*cos(angle[i]);
			y[i] = scan_msg_poles.ranges[i]*sin(angle[i]);

           if(!std::isnan(x[i]) && !std::isnan(y[i]) && (scan_msg_poles.ranges[i] < min_range)){
                       range_1[initial_count_1] = scan_msg_poles.ranges[i];
                       count_angle_1[initial_count_1] = i;
                       initial_count_1 = initial_count_1 + 1;
           }
         } // for loop 	

          int random_count_1 = rand()% (initial_count_1-1);
          smallest_iteration_1 = count_angle_1[random_count_1];
          Current_x_1 = x[smallest_iteration_1];
          Current_y_1 = y[smallest_iteration_1];
          initial_count_1 = 1;

         /* for (int p=1; p < sizeof(range_1)/sizeof(range_1[0]); p++){
            if (range_1[p] < smallest && (range_1[p] != 0)){
               smallest_range_1 = range_1[p] ;
               smallest_iteration_1 = count_angle_1[p];
               count_1 = 1;
            }
          }  

           if(count_1 == 1){
           Current_x_1 = x[smallest_iteration_1];
           Current_y_1 = y[smallest_iteration_1];
           }*/


//---------------------- FIRST HALF ---------------------------//
        for (int m = 1 ; m <= 540; m++){
         if((scan_msg_main.ranges[m] < min_range) && !std::isnan(x[m]) && !std::isnan(y[m])){
  	  double obst_dist_1 = sqrt(pow(y[m]-Current_y_1,2) + pow(x[m]-Current_x_1,2)); 
          if (thershold > abs(obst_dist_1) ){
            array[1][1] = Current_x_1;
            array[1][2] = Current_y_1;

            array[k+1][1] = x[m];
            array[k+1][2] = y[m]; 
            k = k + 1;
           }
         }
        }
         
        for (int j = 1; j<=(k-1); j++){
		sum_x_1+=array[j][1];
		sum_y_1+=array[j][2];
        }

         final_x_1 = sum_x_1/(k-1);
         final_y_1 = sum_y_1/(k-1);

          std::cout << "final_x_1:" << final_x_1 << "\n" << "final_y_1:" << final_y_1 << "\n" << "angle[i]:" << angle[smallest_iteration_1] << "\n" << std::endl;

         // if(k > )

         k = 1;
         sum_x_1 = 0;
         sum_y_1 = 0;

//---------------------- SECOND HALF ---------------------------//
        for (int i = 640; i <= 900; i++){
			angle[i] = scan_msg_poles.angle_min+i*scan_msg_poles.angle_increment;
			x[i] = scan_msg_poles.ranges[i]*cos(angle[i]);
			y[i] = scan_msg_poles.ranges[i]*sin(angle[i]);

         if(!std::isnan(x[i]) && !std::isnan(y[i]) && (q == 0) && (scan_msg_poles.ranges[i] < min_range)){
                       range_2[initial_count_2] = scan_msg_poles.ranges[i];
                       count_angle_2[initial_count_2] = i;
                       initial_count_2 = initial_count_2 + 1;
                       q = 1;
                 }  
                } // for loop 

          double smallest_2 = range_2[0];
          for (int p=1; p < sizeof(range_2)/sizeof(range_2[0]); ++p){
            if (range_2[p] < smallest_2 && (range_2[p] != 0)){
               smallest_range_2 = range_2[p] ;
               smallest_iteration_2 = count_angle_2[p];
               count_2 = 1;
            }
          }  	  

           if(count_2 == 1){
           Current_x_2 = x[smallest_iteration_2];
           Current_y_2 = y[smallest_iteration_2];
           }

//---------------------- SECOND HALF ---------------------------//
      for (int m = 640 ; m <=900; m++){
         if((scan_msg_main.ranges[m] < min_range) && !std::isnan(x[m]) && !std::isnan(y[m])){
  	  double obst_dist_2 = sqrt(pow(y[m]-Current_y_2,2) + pow(x[m]-Current_x_2,2)); 
          if (abs(obst_dist_2) < thershold){
            array[1][1] = Current_x_2;
            array[1][2] = Current_y_2;

            array[q+1][1] = x[m];
            array[q+1][2] = y[m]; 
            q = q + 1;
           }
         }
        }
         
        for (int j = 1; j<=(q-1); j++){
		sum_x_2+=array[j][1];
		sum_y_2+=array[j][2];
        }

         final_x_2 = sum_x_2/(q-1);
         final_y_2 = sum_y_2/(q-1);
         q = 1;

         marker_2.header.frame_id = "hokuyo";
         marker_2.header.stamp = ros::Time::now();
         marker_2.ns = "poles";
         marker_2.id = 2;
         marker_2.type = visualization_msgs::Marker::CYLINDER;
         marker_2.action = visualization_msgs::Marker::ADD;
         marker_2.pose.position.x = final_x_2;
         marker_2.pose.position.y = final_y_2;
         marker_2.pose.position.z = 0;
         marker_2.pose.orientation = tf::createQuaternionMsgFromYaw(1.57);
         marker_2.scale.x = 0.04;
         marker_2.scale.y = 0.04;
         marker_2.scale.z = 0.1;
         marker_2.color.a = 1.0; // Don't forget to set the alpha!
         marker_2.color.r = 0.0;
         marker_2.color.g = 0.0;
         marker_2.color.b = 1.0;
         marker_2.lifetime = ros::Duration(0.125);

//---------------------- GOAL ---------------------------//
         marker_goal.header.frame_id = "hokuyo";
         marker_goal.header.stamp = ros::Time();
         marker_goal.ns = "poles";
         marker_goal.id = 3;
         marker_goal.type = visualization_msgs::Marker::CYLINDER;
         marker_goal.action = visualization_msgs::Marker::ADD;
         marker_goal.pose.position.x = (final_x_1 + final_x_2)/2;
         marker_goal.pose.position.y = (final_y_1 + final_y_2)/2;
         marker_goal.pose.position.z = 0;
         marker_goal.pose.orientation = tf::createQuaternionMsgFromYaw(1.57);
         marker_goal.scale.x = 0.1;
         marker_goal.scale.y = 0.1;
         marker_goal.scale.z = 0.2;
         marker_goal.color.a = 1.0; // Don't forget to set the alpha!
         marker_goal.color.r = 0.0;
         marker_goal.color.g = 1.0;
         marker_goal.color.b = 0.0;
         marker_goal.lifetime = ros::Duration(0.125);

         // publish the markers

         vis_pub_2.publish(marker_2);
         vis_pub_3.publish(marker_goal);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "row_transition");
  ros::NodeHandle n;

  ros::Subscriber scan_sub_test = n.subscribe("scan", 100, scanCallback);
  ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);

  //publisher
  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);
  vis_pub_1 = n.advertise<visualization_msgs::Marker>( "obstacle_marker_1", 1 );
  vis_pub_2 = n.advertise<visualization_msgs::Marker>( "obstacle_marker_2", 1 );
  vis_pub_3 = n.advertise<visualization_msgs::Marker>( "goal_marker", 1 );

  ros::Rate r(1.0);
  double linear_velocity = 0.3;
  double angular_velocity = 0.20;

  while (ros::ok()){
  ros::spinOnce();

  if (scan_msg_main.ranges.size() > 0){ // scan check  

  if(int i = 0){
  thorvald_position_x = thorvald_estimated_pose.pose.pose.position.x;
  thorvald_position_y = thorvald_estimated_pose.pose.pose.position.y;
  i++;
  } 

  if(m < 5){
  Pole_detection(scan_msg_main);
  m = m + 1;
  }

  /* if(((thorvald_estimated_pose.pose.pose.position.x - thorvald_position_x) < 3.0)){
  est_twist.linear.x = linear_velocity;
  // est_twist.angular.z = angular_velocity;
  }
  else if(((thorvald_estimated_pose.pose.pose.position.y - thorvald_position_y) < 0.5)){
  est_twist.linear.x = 0.05; 
  est_twist.angular.z = angular_velocity; 
  }
  else{
  est_twist.linear.x = 0.0; 
  est_twist.angular.z = 0.0;

  Pole_detection(scan_msg_main);
   } 
 


  twist_gazebo.publish(est_twist);
*/




  } // scan check

  marker_1.header.frame_id = "hokuyo";
  marker_1.header.stamp = ros::Time::now();
  marker_1.ns = "poles";
  marker_1.id = 1;
  marker_1.type = visualization_msgs::Marker::CYLINDER;
  marker_1.action = visualization_msgs::Marker::ADD;
  marker_1.pose.position.x = final_x_1;
  marker_1.pose.position.y = final_y_1;
  marker_1.pose.orientation.w = 1.0;
  marker_1.scale.x = 0.05;
  marker_1.scale.y = 0.05;
  marker_1.scale.z = 0.1;
  marker_1.color.a = 1.0; // Don't forget to set the alpha!
  marker_1.color.b = 1.0;
  marker_1.lifetime = ros::Duration(0.125);

  vis_pub_1.publish(marker_1);

  r.sleep();
  }
 

 return 0;
} // main loop end
