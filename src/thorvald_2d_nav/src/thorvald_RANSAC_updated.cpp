#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point.h>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <algorithm>
#include <cmath>
#include <visualization_msgs/Marker.h>

// ROS message includes
#include <thorvald_2d_nav/scan_detected_line.h>

using namespace std;

// Parameters 
geometry_msgs::Point n;
int k; // iterations need to find the best model
double thershold = 0.08;
int d = 10; // nearby point to fit the line
double best_model;
float x_1[360], y_1[360], angle_1, x_2[360], y_2[360], angle_2;
sensor_msgs::LaserScan scan_msg_main;
int p_1 = 0, l_1 = 0, c_1 = 0, a_1 = 0, b_1 = 0, p_2 = 0, l_2 = 0, c_2 = 0, a_2 = 0, b_2 = 0;
double current_range_1, current_range_2;
int final_count_1 = 0, final_count_2 = 0, final_count_3 = 0, final_count_4 = 0;
int count_i_1[360], count_i_2[360];
visualization_msgs::Marker line_strip_1, line_strip_2, final_line;

thorvald_2d_nav::scan_detected_line measurement_points;

// Our "data".
struct Point {
  double real_x; double real_y;
};

// Our "model".
struct Line {
  double m; double b;
};

Point best_inlierpoints_1[360];
Point current_best_inlierpoints_1[360];
Line final_line_1;
Point final_Index_1[2], current_Index_1[2];

Point best_inlierpoints_2[360];
Point current_best_inlierpoints_2[360];
Line final_line_2;
Point final_Index_2[2], current_Index_2[2];

// Laser Scan data
void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
  		size_t num_ranges = scan_msg->ranges.size();
                scan_msg_main.ranges = scan_msg->ranges;

               for (k=0; k < 50; k++){ // Number of iterations

//---------------------- FIRST HALF - START ---------------------------//
		for (int i_1 = 0; i_1 <= 90; i_1++){
			angle_1 = scan_msg->angle_min+i_1*scan_msg->angle_increment;
			x_1[i_1] = scan_msg->ranges[i_1]*cos(angle_1);
			y_1[i_1] = scan_msg->ranges[i_1]*sin(angle_1);

                if(!isnan(x_1[i_1]) && !isnan(y_1[i_1])){
                count_i_1[l_1] = i_1;
                l_1= l_1 + 1;
                }
                } // for loop 	

               int i_corr_x_1 = rand()% (l_1-1);
               int i_corr_y_1 = rand()% (l_1-1);
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

		 for (int i_1 = 0; i_1 < (l_1-1); i_1++){
                   int index_1 = count_i_1[i_1];
                   double error_1 = y_1[index_1] - (model_1.m*x_1[index_1] + model_1.b); // error calculation

                   if(thershold > abs(error_1) && error_1 != 0){
                   current_best_inlierpoints_1[p_1].real_x = x_1[index_1];
                   current_best_inlierpoints_1[p_1].real_y = y_1[index_1];
                   p_1 = p_1 +1;
                   }   
                  } // for loop end

               final_count_1 = p_1-1;
               l_1 = 0;

               if( ((p_1-1) > d)){ // selecting the inliers with max of points    
            
                if(c_1 == 0){
                 for(int q_1 = 0; q_1 < p_1; q_1++){
                  best_inlierpoints_1[a_1] = current_best_inlierpoints_1[q_1]; 
                  a_1 = a_1 +1; 
                  }  
                 c_1 = 1;
                 current_range_1 =  scan_msg->ranges[aIndex_1];
                 current_range_2 =  scan_msg->ranges[bIndex_1];
                 final_count_2 = a_1-1; 
                 } // if loop end

                 if(((final_count_1) > final_count_2) && (final_count_1 > d) && (c_1 < 100)){ // check for best model
                  for(int q_1 = 0; q_1 < final_count_1; q_1++){
                   best_inlierpoints_1[q_1] = current_best_inlierpoints_1[q_1]; 
                   current_Index_1[1].real_x = x_1[aIndex_1];
                   current_Index_1[1].real_y = y_1[aIndex_1];
                   current_Index_1[1].real_x = x_1[bIndex_1];
                   current_Index_1[1].real_y = y_1[bIndex_1]; 
                  }
                   c_1 = c_1 + 1;

                  if ((current_range_1 > scan_msg->ranges[aIndex_1]) && (current_range_2 > scan_msg->ranges[bIndex_1]) ){
                  final_Index_1[1].real_x = x_1[aIndex_1];
                  final_Index_1[1].real_y = y_1[aIndex_1];
                  final_Index_1[2].real_x = x_1[bIndex_1];
                  final_Index_1[2].real_y = y_1[bIndex_1]; 
                  }
                  else{
                  final_Index_1[1].real_x = current_Index_1[1].real_x;
                  }

                  }                 
                } // inliers selection end

                 a_1 = p_1;
                 p_1 = 0;
                 } //check for aIndex and bIndex values end

//---------------------- FIRST HALF - END ---------------------------//


//---------------------- SECOND HALF - START ---------------------------//

		for (int i_2 = 270; i_2 <= 360; i_2++){
			angle_2 = scan_msg->angle_min+i_2*scan_msg->angle_increment;
			x_2[i_2] = scan_msg->ranges[i_2]*cos(angle_2);
			y_2[i_2] = scan_msg->ranges[i_2]*sin(angle_2);

                if(!isnan(x_2[i_2]) && !isnan(y_2[i_2])){
                count_i_2[l_2] = i_2;
                l_2 = l_2 + 1;
                }
                } // for loop 	

               int i_corr_x_2 = rand()% (l_2-1);
               int i_corr_y_2 = rand()% (l_2-1);
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

		 for (int i_2 = 0; i_2 < (l_2-1); i_2++){
                   int index_2 = count_i_2[i_2];
                   double error_2 = y_2[index_2] - (model_2.m*x_2[index_2] + model_2.b); // error calculation

                   if(thershold > abs(error_2) && error_2 != 0){
                   current_best_inlierpoints_2[p_2].real_x = x_2[index_2];
                   current_best_inlierpoints_2[p_2].real_y = y_2[index_2];
                   p_2 = p_2 +1;
                   }   
                  } // for loop end

               final_count_3 = p_2-1;
               l_2 = 0;

               if( ((p_2-1) > d)){ // selecting the inliers with max of points                
                if(c_2 == 0){
                 for(int q_2 = 0; q_2 < p_2; q_2++){
                  best_inlierpoints_2[a_2] = current_best_inlierpoints_2[q_2]; 
                  a_2 = a_2 +1; 
                  }  
                 c_2 = 1;
                 final_count_4 = a_1-1; 
                } // if loop end

                 if(((final_count_3) > final_count_4) && (final_count_3 > d) && (c_2 < 100)){ // check for best model
                  for(int q_2 = 0; q_2 < final_count_3; q_2++){
                   best_inlierpoints_2[q_2] = current_best_inlierpoints_2[q_2]; 
                   }
                   c_2 = c_2 + 1;

                  final_Index_2[1].real_x = x_2[aIndex_2];
                  final_Index_2[1].real_y = y_2[aIndex_2];
                  final_Index_2[2].real_x = x_2[bIndex_2];
                  final_Index_2[2].real_y = y_2[bIndex_2]; 

                  // measurement_points.range[1] = scan_msg->ranges[aIndex_2];
                  // measurement_points.range[1] = scan_msg->ranges[bIndex_2];

                  // measurement_points.bearing[1] = scan_msg->angle_min+aIndex_2*scan_msg->angle_increment;
                  // measurement_points.bearing[2] = scan_msg->angle_min+bIndex_2*scan_msg->angle_increment;


                  }                 
                } // inliers selection end

                 a_2 = p_2;
                 p_2 = 0;
                 } //check for aIndex and bIndex values end


 } //iterations ended

//---------------------- SECOND HALF - END ---------------------------//



} // callback end

int main(int argc, char** argv)
{
	ros::init(argc, argv, "thorvald_RANSAC");
	ros::NodeHandle n;

        ros::Rate r(30);

        // Subscribers
	ros::Subscriber scan_sub = n.subscribe("scan_filtered", 100, scanCallback);

        // Publishers
        ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("line_marker_1", 10);
        ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("line_marker_2", 10);
        ros::Publisher marker_pub_3 = n.advertise<visualization_msgs::Marker>("final_line", 10);
        // ros::Publisher point_pub = n.advertise<thorvald_2d_nav::scan_detected_line>("measurement_points", 10);

        while (ros::ok()){

	ros::spinOnce();	

 if ((final_count_1 != 0) && line_strip_1.points.size() < 2){        
        line_strip_1.header.frame_id = "/laser";
        line_strip_1.header.stamp = ros::Time::now();
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
         for(int q_1 = 1; q_1 <= 2; q_1++){
        geometry_msgs::Point pt_1;

        pt_1.x = final_Index_1[q_1].real_x; 
        pt_1.y = final_Index_1[q_1].real_y; 
  
          if(pt_1.x != 0 && pt_1.y != 0){
           line_strip_1.points.push_back(pt_1); }            
         } // for loop end for storing points
        } // count check

 if ((final_count_3 != 0) && line_strip_2.points.size() < 2){        
        line_strip_2.header.frame_id = "/laser";
        line_strip_2.header.stamp = ros::Time::now();
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
         for(int q_2 = 1; q_2 <= 2; q_2++){
        geometry_msgs::Point pt_2;

        pt_2.x = final_Index_2[q_2].real_x; 
        pt_2.y = final_Index_2[q_2].real_y; 
  
          if(pt_2.x != 0 && pt_2.y != 0){
           line_strip_2.points.push_back(pt_2); }            
         } // for loop end for storing points
        } // count check

 if(line_strip_1.points.size() > 1 && line_strip_2.points.size() > 1){
        final_line.header.frame_id = "/laser";
        final_line.header.stamp = ros::Time::now();
        final_line.action = visualization_msgs::Marker::ADD;
        final_line.pose.orientation.w = 1.0;
        final_line.type = visualization_msgs::Marker::LINE_STRIP;
        final_line.lifetime = ros::Duration(0.1);
        final_line.id = 1;

       // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        final_line.scale.x = 0.03;

        // Line strip is blue
        final_line.color.b = 1.0;
        final_line.color.a = 1.0;

        // Create the vertices for the points and lines
         for(int q_3 = 1; q_3 <= 2; q_3++){
        geometry_msgs::Point pt_3;
        pt_3.x = (final_Index_1[q_3].real_x + final_Index_2[q_3].real_x)/2; 
        pt_3.y = (final_Index_1[q_3].real_y + final_Index_2[q_3].real_y)/2; 
  
        if(pt_3.x != 0 && pt_3.y != 0){
         final_line.points.push_back(pt_3); }  
         } // for loop end for storing points          

 } // count check

        // std::cout << "final_count_1" << final_Index_1[1].real_x << "\n" << "final_count_2" << final_Index_1[1].real_x << std::endl;

        // publish the lines
        marker_pub_1.publish(line_strip_1);
        marker_pub_2.publish(line_strip_2);
        marker_pub_3.publish(final_line);

        // point_pub.publish(measurement_points);
	} 

  r.sleep();
  return 0;
}

