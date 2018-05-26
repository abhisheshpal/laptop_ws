#include <ros/ros.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Float64MultiArray.h>
#include <visualization_msgs/Marker.h>

float goalX;
float goalY;
std_msgs::Float64MultiArray x_point[500];

float fwSpeed = 0, sum_x_1 = 0, sum_y_1 = 0, sum_x_2 = 0, sum_y_2 = 0;
float final_x_1, final_y_1, final_x_2, final_y_2;
int k = 0, q = 0, count_1 = 0, count_2 = 0, smallest_iteration_1 = 0, smallest_iteration_2 = 0;
float array[360][2]; 
double Current_x_1, Current_y_1, Current_x_2, Current_y_2, final_range_1, final_range_2, smallest_range_1, smallest_range_2;
double range_1[360], range_2[360], count_angle_1[360], count_angle_2[360];
ros::Subscriber scan_sub;
double x[360], y[360], angle[360];
double min_range = 1.0;
sensor_msgs::LaserScan scan_msg_main;
		
visualization_msgs::Marker marker_1;
visualization_msgs::Marker marker_2;
visualization_msgs::Marker marker_goal;

void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
		size_t num_ranges = scan_msg->ranges.size();
                scan_msg_main.ranges = scan_msg->ranges;
                int initial_count_1 = 0;
                int initial_count_2 = 0;

//---------------------- FIRST HALF ---------------------------//
	for (int i = 0; i <= 90; i++){
			angle[i] = scan_msg->angle_min+i*scan_msg->angle_increment;
			x[i] = scan_msg->ranges[i]*cos(angle[i]);
			y[i] = scan_msg->ranges[i]*sin(angle[i]);

           if(!std::isnan(x[i]) && !std::isnan(y[i]) && (k == 0) && (scan_msg_main.ranges[i] < min_range)){
                       range_1[initial_count_1] = scan_msg->ranges[i];
                       count_angle_1[initial_count_1] = i;
                       initial_count_1 = initial_count_1 + 1;
                       k = 1;
           }
         } // for loop 	

          double smallest = range_1[0];
          for (int p=1; p < sizeof(range_1)/sizeof(range_1[0]); ++p){
            if (range_1[p] < smallest && (range_1[p] != 0)){
               smallest_range_1 = range_1[p] ;
               smallest_iteration_1 = count_angle_1[p];
               count_1 = 1;
            }
          }  

           if(count_1 == 1){
           Current_x_1 = x[smallest_iteration_1];
           Current_y_1 = y[smallest_iteration_1];
           }

//---------------------- SECOND HALF ---------------------------//
        for (int i = 270; i <= 360; i++){
			angle[i] = scan_msg->angle_min+i*scan_msg->angle_increment;
			x[i] = scan_msg->ranges[i]*cos(angle[i]);
			y[i] = scan_msg->ranges[i]*sin(angle[i]);

         if(!std::isnan(x[i]) && !std::isnan(y[i]) && (q == 0) && (scan_msg_main.ranges[i] < min_range)){
                       range_2[initial_count_2] = scan_msg->ranges[i];
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

} // Callback loop

int main(int argc, char** argv) 
{
	ros::init(argc, argv, "thorvald_laserscan");
	ros::NodeHandle n;

        // Publishers
        ros::Publisher vis_pub_1 = n.advertise<visualization_msgs::Marker>( "obstacle_marker_1", 1 );
        ros::Publisher vis_pub_2 = n.advertise<visualization_msgs::Marker>( "obstacle_marker_2", 1 );
        ros::Publisher vis_pub_3 = n.advertise<visualization_msgs::Marker>( "goal_marker", 1 );

        // Subscribers
	scan_sub = n.subscribe("scan_filtered", 100, scanCallback);
        ros::Rate loop_rate(10);
        double thershold = 0.02000;

	while (ros::ok()){

        if (scan_msg_main.ranges.size() > 0){    

//---------------------- FIRST HALF ---------------------------//
        for (int m = 0 ; m <=60; m++){
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
         k = 1;

         marker_1.header.frame_id = "laser";
         marker_1.header.stamp = ros::Time::now();
         marker_1.ns = "obstacles";
         marker_1.id = rand();
         marker_1.type = visualization_msgs::Marker::CYLINDER;
         marker_1.action = visualization_msgs::Marker::ADD;
         marker_1.pose.position.x = final_x_1;
         marker_1.pose.position.y = final_y_1;
         marker_1.pose.position.z = 0;
         marker_1.pose.orientation = tf::createQuaternionMsgFromYaw(1.57);
         marker_1.scale.x = 0.04;
         marker_1.scale.y = 0.04;
         marker_1.scale.z = 0.1;
         marker_1.color.a = 1.0; // Don't forget to set the alpha!
         marker_1.color.r = 0.0;
         marker_1.color.g = 0.0;
         marker_1.color.b = 1.0;
         marker_1.lifetime = ros::Duration(0.125);

//---------------------- SECOND HALF ---------------------------//
        for (int m = 270 ; m <=360; m++){
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

         marker_2.header.frame_id = "laser";
         marker_2.header.stamp = ros::Time::now();
         marker_2.ns = "obstacles";
         marker_2.id = rand();
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
         marker_goal.header.frame_id = "laser";
         marker_goal.header.stamp = ros::Time();
         marker_goal.ns = "obstacles";
         marker_goal.id = rand();
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
         vis_pub_1.publish(marker_1);
         vis_pub_2.publish(marker_2);
         vis_pub_3.publish(marker_goal);

       }

      ros::spinOnce();	
      } 

loop_rate.sleep();

}


