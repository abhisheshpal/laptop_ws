#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>
#include <cmath>
#include <math.h>       /* fabs */
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseArray.h>

// ROS message includes
#include <thorvald_2d_nav/scan_detected_line.h>
#include <thorvald_2d_nav/sub_goal.h>
#include <thorvald_2d_nav/landmarks.h>

#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

// Parameters 
geometry_msgs::Point n;
int k; // iterations need to find the best model
double thershold = 0.1;
int d = 25; // nearby point to fit the line

double best_model;
double x_1[1080], y_1[1080], angle_1[1080], x_2[1080], y_2[1080], angle_2[1080];
sensor_msgs::LaserScan scan_msg_main;
int p_1 = 1, l_1 = 1, c_1 = 0, a_1 = 0, b_1 = 0, p_2 = 1, l_2 = 1, c_2 = 0, a_2 = 0, b_2 = 0;
double current_range_1, current_range_2;
int final_count_1 = 0, final_count_2 = 0, final_count_3 = 0, final_count_4 = 0, final_count_5 = 0, final_count_6 = 0, finale = 0;
int count_i_1[1080], count_i_2[1080];
visualization_msgs::Marker line_strip_1, line_strip_2, final_line;
int end_line = 0, finale_1 = 0;
double yaw;
int line_pt = 0;
nav_msgs::Odometry thorvald_estimated_pose;
bool line_found_1 = false, line_found_2 = false;

thorvald_2d_nav::scan_detected_line measurement_points;
thorvald_2d_nav::landmarks landmarks_pos;

// Our "data".
struct Point {
  double real_x; double real_y;
};

// Our "model".
struct Line {
  double m; double b;
};

Point best_inlierpoints_1[1080];
Point current_best_inlierpoints_1[1080];
Line final_line_1;
Point final_Index_1[2], current_Index_1[2];

Point best_inlierpoints_2[1080];
Point current_best_inlierpoints_2[1080];
Line final_line_2;
Point final_Index_2[2], current_Index_2[2];

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

// RANSAC for line detection
Point Line_detection_1(sensor_msgs::LaserScan scan_msgs, Point* line_pt_1){

        // x, y, theta calculation
	for (int i_1 = 1; i_1 <= 540; i_1++){
	 angle_1[i_1] = scan_msg_main.angle_min +i_1*scan_msg_main.angle_increment; 
	 x_1[i_1] = scan_msg_main.ranges[i_1]*cos(angle_1[i_1]);
	 y_1[i_1] = scan_msg_main.ranges[i_1]*sin(angle_1[i_1]);
                
          if(!std::isnan(x_1[i_1]) && !std::isnan(y_1[i_1]) && (scan_msg_main.ranges[i_1] < 5.0)){
           count_i_1[l_1] = i_1;
           l_1= l_1 + 1;
          } // storing the ith value with pre-conditions

        } // storing the range values (end for loop)
        
        l_1= l_1 - 1;
        int i_corr_x_1 = rand()% (l_1);
        int i_corr_y_1 = rand()% (l_1);
        int aIndex_1 = count_i_1[i_corr_x_1]; 
        int bIndex_1 = count_i_1[i_corr_y_1];

        // sending the scan data
        Line model_1;
        int count_1 = 0;

        if ((aIndex_1!=bIndex_1) && (y_1[aIndex_1]!=0)&& (x_1[aIndex_1]!=0)&& (y_1[bIndex_1]!=0)&& (x_1[bIndex_1]!=0)){
          model_1.m = (y_1[bIndex_1] - y_1[aIndex_1])/(x_1[bIndex_1] - x_1[aIndex_1]);
          model_1.b = y_1[aIndex_1] - model_1.m * x_1[aIndex_1];
          }

        else { count_1 = 1; }

        if(count_1 == 0){   // check for aIndex and bIndex values

          for (int i_1 = 0; i_1 < (l_1); i_1++){
            int index_1 = count_i_1[i_1];
            double error_1 = y_1[index_1] - (model_1.m*x_1[index_1] + model_1.b); // error calculation

            if((thershold > error_1) && (-thershold < error_1) && (error_1 != 0)){  // check for threshold
            // std::cout << "error_1:" << abs(error_1) << "\n" << std::endl;
              current_best_inlierpoints_1[p_1].real_x = x_1[index_1];
              current_best_inlierpoints_1[p_1].real_y = y_1[index_1];
              p_1 = p_1 +1;

              }   

          } // for loop end
        
        final_count_1 = p_1-1;
        l_1 = 0;

        if(final_count_1 > d){ // selecting the inliers with max of points    

     if((final_count_1 > final_count_2) && (fabs(y_1[aIndex_1]) < 1.0) && (fabs(y_1[bIndex_1]) < 1.0)){
            final_Index_1[1].real_x = x_1[aIndex_1];
            final_Index_1[1].real_y = y_1[aIndex_1];
            final_Index_1[2].real_x = x_1[bIndex_1];
            final_Index_1[2].real_y = y_1[bIndex_1];

            measurement_points.range[0] = scan_msg_main.ranges[aIndex_1];
            measurement_points.bearing[0] = angle_1[aIndex_1];
            measurement_points.range[1] = scan_msg_main.ranges[bIndex_1];
            measurement_points.bearing[1] = angle_1[bIndex_1];

            final_count_2 = final_count_1;
            line_found_1 = true;
           }                 
          } // max inliers selection end

        // Assigning variables to zero to start over
        p_1 = 0;
        final_count_2 = 0;

        } //check for aIndex and bIndex values end
}

Point Line_detection_2(sensor_msgs::LaserScan scan_msgs, Point* line_pt_2){

        // x, y, theta calculation
	for (int i_2 = 540; i_2 <= 1079; i_2++){
	angle_2[i_2] = scan_msg_main.angle_min+i_2*scan_msg_main.angle_increment;
	x_2[i_2] = scan_msg_main.ranges[i_2]*cos(angle_2[i_2]);
	y_2[i_2] = scan_msg_main.ranges[i_2]*sin(angle_2[i_2]);

          if(!std::isnan(x_2[i_2]) && !std::isnan(y_2[i_2]) && (scan_msg_main.ranges[i_2] < 5.0)){
           count_i_2[l_2] = i_2;
           l_2 = l_2 + 1;                
          } // storing the ith value with pre-conditions
         } // storing the range values (end for loop)

        l_2= l_2 - 1;
        int i_corr_x_2 = rand()% (l_2);
        int i_corr_y_2 = rand()% (l_2);
        int aIndex_2 = count_i_2[i_corr_x_2]; 
        int bIndex_2 = count_i_2[i_corr_y_2];

        // sending the scan data
        Line model_2;
        int count_2 = 0;

        if ((aIndex_2!=bIndex_2) && (y_2[aIndex_2]!=0)&& (x_2[aIndex_2]!=0)&& (y_2[bIndex_2]!=0)&& (x_2[bIndex_2]!=0)){
         model_2.m = (y_2[bIndex_2] - y_2[aIndex_2])/(x_2[bIndex_2] - x_2[aIndex_2]);
         model_2.b = y_2[aIndex_2] - model_2.m * x_2[aIndex_2];
        }

        else { count_2 = 1; }

        if(count_2 == 0){   // check for aIndex and bIndex values

        for (int i_2 = 0; i_2 < (l_2); i_2++){
           int index_2 = count_i_2[i_2];
           double error_2 = y_2[index_2] - (model_2.m*x_2[index_2] + model_2.b); // error calculation

           if((thershold > error_2) && (error_2 > (-thershold))  && (error_2!= 0)){
           current_best_inlierpoints_2[p_2].real_x = x_2[index_2];
           current_best_inlierpoints_2[p_2].real_y = y_2[index_2];
           p_2 = p_2 +1;
           }   
         } // for loop end
        
        final_count_4 = p_2-1;
        l_2 = 0;

        if(final_count_4 > d){ // selecting the inliers with max of points    
         if(final_count_4 > final_count_5 && (fabs(y_2[aIndex_2]) < 1.0) && (fabs(y_2[bIndex_2]) < 1.0)){

            final_Index_2[1].real_x = x_2[aIndex_2];
            final_Index_2[1].real_y = y_2[aIndex_2];
            final_Index_2[2].real_x = x_2[bIndex_2];
            final_Index_2[2].real_y = y_2[bIndex_2];

            measurement_points.range[2] = scan_msg_main.ranges[aIndex_2];
            measurement_points.bearing[2] = angle_2[aIndex_2];
            measurement_points.range[3] = scan_msg_main.ranges[bIndex_2];
            measurement_points.bearing[3] = angle_2[bIndex_2];

            final_count_5 = final_count_4;
            line_found_2 = true;
          }            
        } // max inliers selection end

        // Assigning variables to zero to start over
        p_2 = 0;
        final_count_5 = 0;
        } //check for aIndex and bIndex values end
}


bool add(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     end_line = end_line + req.counter;
     if(end_line > finale_1){
     finale = 0; 
     ROS_INFO("service on time");
     finale_1 = end_line;
     }
 
     return true;
   }

int main(int argc, char** argv)
{
	ros::init(argc, argv, "guinea_pig");
	ros::NodeHandle n;

        ros::Rate r(10);

        // Subscribers
	ros::Subscriber scan_sub_test = n.subscribe("scan", 100, scanCallback);
        ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);

        // Publishers
        ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("line_marker_1", 10);
        ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("line_marker_2", 10);
        ros::Publisher marker_pub_3 = n.advertise<visualization_msgs::Marker>("final_line", 10);
        ros::Publisher point_pub = n.advertise<thorvald_2d_nav::scan_detected_line>("measurement_points", 10);
        ros::Publisher landmarks_pub = n.advertise<thorvald_2d_nav::landmarks>("landmark_points", 10);

        // Service Servers
        ros::ServiceServer service = n.advertiseService("/sub_goal_check", add);

        // Service Client
        ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_mode");

        tf2_ros::Buffer tfBuffer;
        tf2_ros::TransformListener tfListener(tfBuffer);
        geometry_msgs::TransformStamped transformStamped;
        double prev_max_line_1 = 0, prev_max_line_2 = 0, row_end = 0;
        landmarks_pos.landmark_check = 0; 
        geometry_msgs::PoseStamped left_line_1, left_line_1_transformed, left_line_2, left_line_2_transformed;
        geometry_msgs::PoseStamped right_line_1, right_line_1_transformed, right_line_2, right_line_2_transformed;
        thorvald_2d_nav::sub_goal end_row;

        while (ros::ok()){
	ros::spinOnce();
        
        line_detect:
        if(scan_msg_main.ranges.size() > 0 && (finale == 0)){ // check for new lines
std::cout << thorvald_estimated_pose.pose.pose.position.x << std::endl;
        // end of row detection
        if(thorvald_estimated_pose.pose.pose.position.x > 7.0){ 
        ROS_INFO("Reached End of Row"); 
        finale = 1;
        end_row.request.counter = 1;
        if (client.call(end_row)) goto line_publish;
        // ROS_INFO("client request");
        }
 
        ROS_INFO("Line Detection starts");
          line_detect_1:
          for (k=0; k <= 5000; k++){ // Number of iterations
          Line_detection_1(scan_msg_main, final_Index_1);
          }
          line_detect_2:
          for (k=0; k <= 5000; k++){ // Number of iterations
          Line_detection_2(scan_msg_main, final_Index_2);
          }

        if((line_found_1==false) || (fabs(final_Index_1[2].real_x - final_Index_1[1].real_x)< 1.0)){
        ROS_INFO("Line 1 has to be re-detected!");
        goto line_detect_1;
        }

        if((line_found_2==false) || (fabs(final_Index_2[2].real_x - final_Index_2[1].real_x)< 1.0)){
        ROS_INFO("Line 2 has to be re-detected!");
        goto line_detect_2;
        }

        ROS_INFO("New Line Detected");
        line_found_1 = false;
        line_found_2 = false;

        left_line_1.header.frame_id = "hokuyo";
        left_line_1.pose.position.x = final_Index_1[1].real_x;
        left_line_1.pose.position.y = final_Index_1[1].real_y;
        left_line_2.header.frame_id = "hokuyo";
        left_line_2.pose.position.x = final_Index_1[2].real_x;
        left_line_2.pose.position.y = final_Index_1[2].real_y;

        right_line_1.header.frame_id = "hokuyo";
        right_line_1.pose.position.x = final_Index_2[1].real_x;
        right_line_1.pose.position.y = final_Index_2[1].real_y;
        right_line_2.header.frame_id = "hokuyo";
        right_line_2.pose.position.x = final_Index_2[2].real_x;
        right_line_2.pose.position.y = final_Index_2[2].real_y;

        try{
        transformStamped = tfBuffer.lookupTransform("map", "hokuyo", ros::Time(0));
        }
        catch (tf2::TransformException &ex){
        ROS_WARN("%s",ex.what());
        ros::Duration(1.0).sleep();
        // continue;
        }

        tf2::doTransform(left_line_1, left_line_1_transformed, transformStamped);
        tf2::doTransform(left_line_2, left_line_2_transformed, transformStamped);
        tf2::doTransform(right_line_1, right_line_1_transformed, transformStamped);
        tf2::doTransform(right_line_2, right_line_2_transformed, transformStamped);

       // Create the vertices for the points and lines
        geometry_msgs::Point pt_1[2], pt_2[2], pt_3, max_line[2], min_line[2];
        max_line[1].x = std::max(left_line_1_transformed.pose.position.x,left_line_2_transformed.pose.position.x);
        max_line[2].x = std::max(right_line_1_transformed.pose.position.x,right_line_2_transformed.pose.position.x);
        min_line[1].x = std::min(left_line_1_transformed.pose.position.x,left_line_2_transformed.pose.position.x);
        min_line[2].x = std::min(right_line_1_transformed.pose.position.x,right_line_2_transformed.pose.position.x);

        if(((max_line[1].x - min_line[1].x)< 1.0) && ((max_line[2].x - min_line[2].x)< 1.0)){
        if(row_end <= 3){
        ROS_INFO("Trajectory Re-calculated!"); 
        row_end = row_end + 1;
        goto line_detect; }
        if(row_end > 3){
        ROS_INFO("Reached End of Row"); 
        finale = 1;
        goto line_publish;
        }
        }

        prev_max_line_1 = max_line[1].x;
        prev_max_line_2 = max_line[2].x;

        if(line_pt == 0){

        pt_1[1].x = left_line_1_transformed.pose.position.x; 
        pt_1[1].y = left_line_1_transformed.pose.position.y; 
        pt_1[2].x = left_line_2_transformed.pose.position.x; 
        pt_1[2].y = left_line_2_transformed.pose.position.y; 

        pt_2[1].x = right_line_1_transformed.pose.position.x; 
        pt_2[1].y = right_line_1_transformed.pose.position.y; 
        pt_2[2].x = right_line_2_transformed.pose.position.x; 
        pt_2[2].y = right_line_2_transformed.pose.position.y; 

         for(int q_1 = 1; q_1 <= 2; q_1++){
          line_strip_1.points.push_back(pt_1[q_1]); 
         }// for loop end for storing points

         for(int q_2 = 1; q_2 <= 2; q_2++){
          if(pt_2[q_2].x != 0 && pt_2[q_2].y != 0){
          line_strip_2.points.push_back(pt_2[q_2]); }
         }// for loop end for storing points

         if(((max_line[1].x - min_line[1].x)< 1.0) && ((max_line[2].x - min_line[2].x)< 1.0)){
        ROS_INFO("Trajectory not generated in a right manner!"); }
         else{
          pt_3.x = (min_line[1].x + min_line[2].x)/2; 
          pt_3.y = (left_line_1_transformed.pose.position.y + right_line_1_transformed.pose.position.y)/2;
         if(pt_3.x != 0 && pt_3.y != 0) final_line.points.push_back(pt_3);   
          pt_3.x = (max_line[1].x + max_line[2].x)/2; 
          pt_3.y = (left_line_2_transformed.pose.position.y + right_line_2_transformed.pose.position.y)/2; 
         if(pt_3.x != 0 && pt_3.y != 0) final_line.points.push_back(pt_3);  
        } // pt_3

        line_pt = 1;
        } // line_pt

        else{
        pt_1[1].x = max_line[1].x; 
        pt_1[1].y = left_line_1_transformed.pose.position.y;
        line_strip_1.points.push_back(pt_1[1]); 

        pt_2[1].x = max_line[2].x; 
        pt_2[1].y = right_line_1_transformed.pose.position.y; 
        line_strip_2.points.push_back(pt_2[1]); 

        if ( ((max_line[1].x - min_line[1].x)< 1.5) && ((max_line[2].x - min_line[2].x)< 1.5)){
        ROS_INFO("Trajectory not generated in a right manner!"); 
        }
        else{ 
        pt_3.x = (max_line[1].x + max_line[2].x)/2; 
        pt_3.y = (left_line_2_transformed.pose.position.y + right_line_2_transformed.pose.position.y)/2; 
        if(pt_3.x != 0 && pt_3.y != 0){
         final_line.points.push_back(pt_3); } 
        }

        } //line_pt else end

        landmarks_pos.pt_1.x = left_line_1_transformed.pose.position.x;
        landmarks_pos.pt_1.y = left_line_1_transformed.pose.position.y;
        landmarks_pos.pt_2.x = left_line_2_transformed.pose.position.x;
        landmarks_pos.pt_2.y = left_line_2_transformed.pose.position.y;

        landmarks_pos.pt_3.x = right_line_1_transformed.pose.position.x;
        landmarks_pos.pt_3.y = right_line_1_transformed.pose.position.y;
        landmarks_pos.pt_4.x = right_line_2_transformed.pose.position.x;
        landmarks_pos.pt_4.y = right_line_2_transformed.pose.position.y;

        landmarks_pos.pt_5.x = (min_line[1].x + min_line[2].x)/2;
        landmarks_pos.pt_5.y = (left_line_1_transformed.pose.position.y + right_line_1_transformed.pose.position.y)/2;
        landmarks_pos.pt_6.x = (max_line[1].x + max_line[2].x)/2;
        landmarks_pos.pt_6.y = (left_line_2_transformed.pose.position.y + right_line_2_transformed.pose.position.y)/2;
       //std::cout << "landmarks_pos.pt_5.x:" << landmarks_pos.pt_5.x << "\n" << "landmarks_pos.pt_6.x" << landmarks_pos.pt_6.x << "\n"  << std::endl;
        landmarks_pos.landmark_check = landmarks_pos.landmark_check + 1;
       
        line_strip_1.header.frame_id = "/map";
        line_strip_1.action = visualization_msgs::Marker::ADD;
        line_strip_1.pose.position.z = 0.75;
        line_strip_1.pose.orientation.w = 1.0;
        line_strip_1.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip_1.lifetime = ros::Duration(0.1);
        line_strip_1.id = 1;
        line_strip_1.scale.x = 0.05;
        line_strip_1.color.b = 1.0;
        line_strip_1.color.a = 1.0;

        line_strip_2.header.frame_id = "/map";
        line_strip_2.action = visualization_msgs::Marker::ADD;
        line_strip_2.pose.position.z = 0.75;
        line_strip_2.pose.orientation.w = 1.0;
        line_strip_2.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip_2.lifetime = ros::Duration(0.1);
        line_strip_2.id = 2;
        line_strip_2.scale.x = 0.05;
        line_strip_2.color.b = 1.0;
        line_strip_2.color.a = 1.0;

        final_line.header.frame_id = "/map";
        final_line.action = visualization_msgs::Marker::ADD;
        final_line.pose.position.z = 0.0;
        final_line.pose.orientation.w = 1.0;
        final_line.type = visualization_msgs::Marker::LINE_STRIP;
        final_line.lifetime = ros::Duration(0.1);
        final_line.id = 3;
        final_line.scale.x = 0.1;
        final_line.color.r = 1.0;
        final_line.color.a = 1.0;

        finale = 1;
      
        }// check for new lines

        line_publish:
        line_strip_1.header.stamp = ros::Time::now();
        line_strip_2.header.stamp = ros::Time::now();
        final_line.header.stamp = ros::Time::now();

        marker_pub_1.publish(line_strip_1);
        marker_pub_2.publish(line_strip_2);
        marker_pub_3.publish(final_line);
        point_pub.publish(measurement_points);
        landmarks_pub.publish(landmarks_pos);
        r.sleep();
	} // node shutdown
  return 0;
}

