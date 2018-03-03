#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>
#include <cmath>
#include <visualization_msgs/Marker.h>

#include <thorvald_2d_nav/scan_detected_line.h>
#include <thorvald_2d_nav/sub_goal.h>

visualization_msgs::Marker line_strip_1, line_strip_2, final_line;

thorvald_2d_nav::scan_detected_line measurement_points;
int end_line = 0, finale = 0, finale_1 = 0;

bool add(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     finale_1 = end_line;
     end_line = end_line + req.counter;
ROS_INFO("service on time");
     if(end_line > finale_1){
     finale = 0; 
     }
 
     return true;
   }

int main(int argc, char **argv)
  {
    ros::init(argc, argv, "fake_lines");
    ros::NodeHandle n;
    ros::Rate r(1);
         
    // Publishers
    ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("line_marker_1", 10);
    ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("line_marker_2", 10);
    ros::Publisher marker_pub_3 = n.advertise<visualization_msgs::Marker>("final_line", 10);
    ros::Publisher point_pub = n.advertise<thorvald_2d_nav::scan_detected_line>("measurement_points", 10);

    // Service Servers
    ros::ServiceServer service = n.advertiseService("sub_goal_check", add);

      while (ros::ok()){
	ros::spinOnce();

        if ((line_strip_1.points.size() < 2)){ 
        line_strip_1.header.frame_id = "/map";
        line_strip_1.action = visualization_msgs::Marker::ADD;
        line_strip_1.pose.orientation.w = 1.0;
        line_strip_1.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip_1.lifetime = ros::Duration(0.1);
        line_strip_1.id = 1;
        // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        line_strip_1.scale.x = 0.03;

        // Line strip is blue
        line_strip_1.color.b = 1.0;
        line_strip_1.color.a = 1.0;

        // Create the vertices for the points and lines
        geometry_msgs::Point pt_1[2];

        pt_1[1].x = -1.3704; 
        pt_1[1].y = -0.4452; 
        pt_1[2].x = -0.5791; 
        pt_1[2].y = -0.4525; 

        measurement_points.range[0] = 1.44099;
        measurement_points.bearing[0] = -2.8274;
        measurement_points.range[1] = 0.735;
        measurement_points.bearing[1] = -2.4783;

         for(int q_1 = 1; q_1 <= 2; q_1++){
           line_strip_1.points.push_back(pt_1[q_1]);            
         } // for loop end for storing points
        }

        if ((line_strip_2.points.size() < 2)){ 
        line_strip_2.header.frame_id = "/map";
        line_strip_2.action = visualization_msgs::Marker::ADD;
        line_strip_2.pose.orientation.w = 1.0;
        line_strip_2.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip_2.lifetime = ros::Duration(0.1);
        line_strip_2.id = 1;
        // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        line_strip_2.scale.x = 0.03;

        // Line strip is blue
        line_strip_2.color.b = 1.0;
        line_strip_2.color.a = 1.0;

        // Create the vertices for the points and lines

        geometry_msgs::Point pt_2[2];

        pt_2[1].x = -0.5725; 
        pt_2[1].y = 0.55294; 
        pt_2[2].x = -1.3284; 
        pt_2[2].y = 0.50995; 

        measurement_points.range[2] = 0.796;
        measurement_points.bearing[2] = 2.37364;
        measurement_points.range[3] = 1.4229;
        measurement_points.bearing[3] = 2.77507;
  
         for(int q_2 = 1; q_2 <= 2; q_2++){
           line_strip_2.points.push_back(pt_2[q_2]);            
         } // for loop end for storing points
        }

        if ((final_line.points.size() < 2)){ 
        final_line.header.frame_id = "/map";
        final_line.action = visualization_msgs::Marker::ADD;
        final_line.pose.orientation.w = 1.0;
        final_line.type = visualization_msgs::Marker::LINE_STRIP;
        final_line.lifetime = ros::Duration(0.1);
        final_line.id = 1;

       // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        final_line.scale.x = 0.04;

        // Line strip is blue
        final_line.color.r = 1.0;
        final_line.color.a = 1.0;

        // Create the vertices for the points and lines
        geometry_msgs::Point pt_3[2];
        pt_3[1].x = -1.3494; 
        pt_3[1].y = 0.03233; 
        pt_3[2].x = -0.57589; 
        pt_3[2].y = 0.05021; 
  
         for(int q_3 = 1; q_3 <= 2; q_3++){
         final_line.points.push_back(pt_3[q_3]); 
         } // for loop end for storing points          
        }

        line_strip_1.header.stamp = ros::Time::now();
        line_strip_2.header.stamp = ros::Time::now();
        final_line.header.stamp = ros::Time::now();

        marker_pub_1.publish(line_strip_1);
        marker_pub_2.publish(line_strip_2);
        marker_pub_3.publish(final_line);
        point_pub.publish(measurement_points);
        // r.sleep();
	} // node shutdown
   
     return 0;
  }

