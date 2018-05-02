#include "test_RANSAC.h"

// Laser Scan data
void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
        num_ranges = scan_msg->ranges.size();
        scan_msg_main.header.stamp = scan_msg->header.stamp;
        scan_msg_main.ranges = scan_msg->ranges;
        scan_msg_main.angle_min = scan_msg->angle_min;
        scan_msg_main.angle_increment = scan_msg->angle_increment;
} // callback end

double normalizeangle(double bearing){
    if (bearing < -M_PI) {
        bearing += 2*M_PI;
    } else if (bearing > M_PI) {
        bearing -= 2*M_PI;
    }
}


// RANSAC for line detection
Point Line_detection_1(sensor_msgs::LaserScan scan_msgs, Point* line_pt_1){

        // x, y, theta calculation
	for (int i_1 = (num_ranges/4); i_1 <= (num_ranges/2); i_1++){
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
         if((final_count_1 > final_count_2) && (fabs(y_1[aIndex_1]) < 1.2) && (fabs(y_1[bIndex_1]) < 1.2)){
                    // std::cout << final_count_1 << std::endl;
            if(scan_msg_main.ranges[aIndex_1]<scan_msg_main.ranges[bIndex_1]){
            final_Index_1[1].real_x = x_1[aIndex_1];
            final_Index_1[1].real_y = y_1[aIndex_1];
            final_Index_1[2].real_x = x_1[bIndex_1];
            final_Index_1[2].real_y = y_1[bIndex_1];
            }
            else{
            final_Index_1[1].real_x = x_1[bIndex_1];
            final_Index_1[1].real_y = y_1[bIndex_1];
            final_Index_1[2].real_x = x_1[aIndex_1]; 
            final_Index_1[2].real_y = y_1[aIndex_1];
            }
             
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
	for (int i_2 = (num_ranges/2); i_2 <= 920; i_2++){
	angle_2[i_2] = scan_msg_main.angle_min+i_2*scan_msg_main.angle_increment;
	x_2[i_2] = scan_msg_main.ranges[i_2]*cos(angle_2[i_2]);
	y_2[i_2] = scan_msg_main.ranges[i_2]*sin(angle_2[i_2]);

          if(!std::isnan(x_2[i_2]) && !std::isnan(y_2[i_2]) && (scan_msg_main.ranges[i_2] < 5.5)){
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
         if(final_count_4 > final_count_5 && (fabs(y_2[aIndex_2]) < 1.2) && (fabs(y_2[bIndex_2]) < 1.2)){           

            if(scan_msg_main.ranges[aIndex_2]<scan_msg_main.ranges[bIndex_2]){ 
            final_Index_2[1].real_x = x_2[aIndex_2];
            final_Index_2[2].real_x = x_2[bIndex_2];
            final_Index_2[1].real_y = y_2[aIndex_2];
            final_Index_2[2].real_y = y_2[bIndex_2];
            }
            else{
            final_Index_2[1].real_x = x_2[bIndex_2];
            final_Index_2[2].real_x = x_2[aIndex_2];
            final_Index_2[1].real_y = y_2[bIndex_2];              
            final_Index_2[2].real_y = y_2[aIndex_2];             
            }

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
     if((end_line > finale_1) && (end_line < 3)){
     finale = 0; 
     ROS_INFO("End of previous line reached");
     finale_1 = end_line;
     }
 
     return true;
   }

bool row_transition(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     // end_row = end_row + req.counter; /////////// CHANGE IT ///////////
     row_no = row_no + req.counter;
     if(end_row > finale_2){
     finale = 0; 
     line_pt = 0;
     ROS_INFO("New Row Starts!");
     finale_2 = end_row;
     }
     return true;
   }

int main(int argc, char** argv)
{
	ros::init(argc, argv, "test_RANSAC");
	ros::NodeHandle n;

        ros::Rate r(10);

        // Subscribers
	ros::Subscriber scan_sub_test = n.subscribe("scan", 100, scanCallback);

        // Publishers
        ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("line_marker_1", 10);
        ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("line_marker_2", 10);
        ros::Publisher marker_pub_3 = n.advertise<visualization_msgs::Marker>("final_line", 10);
        ros::Publisher point_pub = n.advertise<thorvald_2d_nav::scan_detected_line>("measurement_points", 10);
        ros::Publisher landmarks_pub = n.advertise<thorvald_2d_nav::landmarks>("landmark_points", 10);
        ros::Publisher thor_pub = n.advertise<geometry_msgs::PoseStamped>("curr_thor", 10);

        // Service Servers
        ros::ServiceServer service1 = n.advertiseService("/sub_goal_check", add);
        ros::ServiceServer service2 = n.advertiseService("/row_transition_end_1", row_transition);

        // Service Client
        ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_mode");

        landmarks_pos.landmark_check = 0; 
        tf::StampedTransform transform;
        tf::TransformListener listener;
        tf2_ros::TransformListener tfListener(tfBuffer);
        meas_pts.range.resize(6);
        tf2_ros::TransformListener tfListener1(tfBuffer1);
        meas_pts.bearing.resize(6);
        
        while (ros::ok()){
	ros::spinOnce();
        
      if(scan_msg_main.ranges.size() > 0){
        // end of row detection
 /*       for (int l=360; l <=720; ++l){ // Number of iterations
         if(((scan_msg_main.ranges[l]) > min_range_view) && ((scan_msg_main.ranges[l]) < max_range) && (!std::isinf(scan_msg_main.ranges[l])) ){
         end_row_reach = end_row_reach + 1;
         // std::cout << "end_row_reach" << end_row_reach << "\n" << std::endl;
         }
        } */
// end_line = 2;
        if((end_line==2) && (new_row == false) && (finale == 0)){ /////// TAKE CARE /////////
        finale = 1;
        end_row_check.request.counter = 1;
        if (client.call(end_row_check)){ 
        ROS_INFO("Reached End of Row");
        new_row = true;
        goto line_publish;}
        }
       }

        line_detect:
        if(scan_msg_main.ranges.size() > 0 && (finale == 0)){ // check for new lines

          ROS_INFO("Line Detection starts");
	
          line_detect_1:
          for (k=0; k <= 10000; k++){ // Number of iterations
          Line_detection_1(scan_msg_main, final_Index_1);
          }
          line_detect_2:
          for (k=0; k <= 10000; k++){ // Number of iterations
          Line_detection_2(scan_msg_main, final_Index_2);
          } 

          try{
          transformStamped = tfBuffer.lookupTransform("map", "hokuyo", ros::Time(0));
          }
          catch (tf2::TransformException &ex){
          ros::Duration(1.0).sleep();
          }
 
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

            tf2::doTransform(left_line_1, left_line_1_trans, transformStamped);
            tf2::doTransform(left_line_2, left_line_2_trans, transformStamped);
            tf2::doTransform(right_line_1, right_line_1_trans, transformStamped);
            tf2::doTransform(right_line_2, right_line_2_trans, transformStamped);

            // std::cout << "left_line_1.pose.position.x :" << curr_pose_trans.pose.position.x << "\n" << "right_line_2.pose.position.x :" << curr_pose_trans.pose.position.y << "\n" << std::endl;

        if((line_found_1==false) || (fabs(left_line_2.pose.position.x - left_line_1.pose.position.x)< 1.0)){
        ROS_INFO("Line 1 has to be re-detected!");
        goto line_detect_1;
        }

        if((line_found_2==false) || (fabs(right_line_2.pose.position.x - right_line_1.pose.position.x)< 1.0)){
        ROS_INFO("Line 2 has to be re-detected!");
        goto line_detect_2;
        }

        ROS_INFO("New Line Detected");
        line_found_1 = false;
        line_found_2 = false;
        end_row_reach = 0;

       // Create the vertices for the points and lines
        geometry_msgs::Point pt_1[2], pt_2[2], pt_3[2];

        if(line_pt == 0){

        pt_1[1].x = left_line_1_trans.pose.position.x; 
        pt_1[1].y = left_line_1_trans.pose.position.y; 
        pt_1[2].x = left_line_2_trans.pose.position.x; 
        pt_1[2].y = left_line_2_trans.pose.position.y; 

        pt_2[1].x = right_line_1_trans.pose.position.x; 
        pt_2[1].y = right_line_1_trans.pose.position.y; 
        pt_2[2].x = right_line_2_trans.pose.position.x; 
        pt_2[2].y = right_line_2_trans.pose.position.y; 

        pt_3[1].x = (left_line_1_trans.pose.position.x + right_line_1_trans.pose.position.x)/2;
        pt_3[1].y = (left_line_1_trans.pose.position.y + right_line_1_trans.pose.position.y)/2;
        pt_3[2].x = (left_line_2_trans.pose.position.x + right_line_2_trans.pose.position.x)/2;
        pt_3[2].y = (left_line_2_trans.pose.position.y + right_line_2_trans.pose.position.y)/2; 

         for(int q_1 = 1; q_1 <= 2; q_1++){
          line_strip_1.points.push_back(pt_1[q_1]);
          line_strip_2.points.push_back(pt_2[q_1]); 
          final_line.points.push_back(pt_3[q_1]); 
         }// for loop end for storing points

        line_pt = 1;
        } // line_pt

        else{ 
        pt_1[1].x = left_line_2_trans.pose.position.x; 
        pt_1[1].y = left_line_2_trans.pose.position.y;  
        pt_2[1].x = right_line_2_trans.pose.position.x; 
        pt_2[1].y = right_line_2_trans.pose.position.y; 
        pt_3[1].x = (left_line_2_trans.pose.position.x + right_line_2_trans.pose.position.x)/2;
        pt_3[1].y = (left_line_2_trans.pose.position.y + right_line_2_trans.pose.position.y)/2;
 
        line_strip_1.points.push_back(pt_1[1]);
        line_strip_2.points.push_back(pt_2[1]); 
        final_line.points.push_back(pt_3[1]); 
        } //line_pt else end

        landmarks_pos.pt_1.x = left_line_1_trans.pose.position.x;
        landmarks_pos.pt_1.y = left_line_1_trans.pose.position.y;
        landmarks_pos.pt_2.x = left_line_2_trans.pose.position.x;
        landmarks_pos.pt_2.y = left_line_2_trans.pose.position.y;

        landmarks_pos.pt_3.x = right_line_1_trans.pose.position.x;
        landmarks_pos.pt_3.y = right_line_1_trans.pose.position.y;
        landmarks_pos.pt_4.x = right_line_2_trans.pose.position.x;
        landmarks_pos.pt_4.y = right_line_2_trans.pose.position.y;

        landmarks_pos.pt_5.x = (left_line_1_trans.pose.position.x + right_line_1_trans.pose.position.x)/2;
        landmarks_pos.pt_5.y = (left_line_1_trans.pose.position.y + right_line_1_trans.pose.position.y)/2;
        landmarks_pos.pt_6.x = (left_line_2_trans.pose.position.x + right_line_2_trans.pose.position.x)/2;
        landmarks_pos.pt_6.y = (left_line_2_trans.pose.position.y + right_line_2_trans.pose.position.y)/2;
        landmarks_pos.landmark_check = landmarks_pos.landmark_check + 1;
       
        line_strip_1.header.frame_id = "/map";
        line_strip_1.action = visualization_msgs::Marker::ADD;
        line_strip_1.pose.position.z = 0.90;
        line_strip_1.pose.orientation.w = 1.0;
        line_strip_1.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip_1.lifetime = ros::Duration(0.1);
        line_strip_1.id = 1;
        line_strip_1.scale.x = 0.05;
        line_strip_1.color.b = 1.0;
        line_strip_1.color.a = 1.0;

        line_strip_2.header.frame_id = "/map";
        line_strip_2.action = visualization_msgs::Marker::ADD;
        line_strip_2.pose.position.z = 0.90;
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

        try{
        transformStamped1 = tfBuffer1.lookupTransform("map", "base_link", ros::Time(0));
        }
        catch (tf2::TransformException &ex1){
        ROS_WARN("%s",ex1.what());
        ros::Duration(1.0).sleep();
        } 

        tf::Quaternion q = tf::createQuaternionFromRPY(0, 0, 0); 
        tf2::doTransform(curr_pose, curr_pose_trans, transformStamped1);
        curr_pose_trans.pose.orientation = transformStamped1.transform.rotation;
        tf::Quaternion quat(curr_pose_trans.pose.orientation.x,curr_pose_trans.pose.orientation.y, curr_pose_trans.pose.orientation.z, curr_pose_trans.pose.orientation.w);
        quat = quat.normalize();
        yaw = tf::getYaw(quat);
        // std::cout << "left_line_1.pose.position.x :" << curr_pose_trans.pose.orientation.w << "\n" << "right_line_2.pose.position.x :" << transformStamped1.transform.rotation.w << "\n" << std::endl;
// actual range and bearing calculation
meas_pts.range[0] = sqrt(pow((left_line_2_trans.pose.position.x-curr_pose_trans.pose.position.x),2)+pow((left_line_2_trans.pose.position.y-curr_pose_trans.pose.position.y),2)); 
meas_pts.bearing[0] = normalizeangle(atan2((left_line_2_trans.pose.position.y-curr_pose_trans.pose.position.y),(left_line_2_trans.pose.position.x-curr_pose_trans.pose.position.x)) - yaw);
meas_pts.range[1] = sqrt(pow((right_line_2_trans.pose.position.x-curr_pose_trans.pose.position.x),2)+pow((right_line_2_trans.pose.position.y-curr_pose_trans.pose.position.y),2)); 
meas_pts.bearing[1] = normalizeangle(atan2((right_line_2_trans.pose.position.y-curr_pose_trans.pose.position.y),(right_line_2_trans.pose.position.x-curr_pose_trans.pose.position.x)) - yaw);

left_l_c.position.x = (left_line_1_trans.pose.position.x + left_line_2_trans.pose.position.x)/2;
left_l_c.position.y = (left_line_1_trans.pose.position.y + left_line_2_trans.pose.position.y)/2;
right_l_c.position.x = (right_line_1_trans.pose.position.x + right_line_2_trans.pose.position.x)/2;
right_l_c.position.y = (right_line_1_trans.pose.position.y + right_line_2_trans.pose.position.y)/2;

meas_pts.range[2] = sqrt(pow((left_l_c.position.x-curr_pose_trans.pose.position.x),2)+pow((left_l_c.position.y-curr_pose_trans.pose.position.y),2));                
meas_pts.bearing[2] = normalizeangle(atan2((left_l_c.position.y-curr_pose_trans.pose.position.y),(left_l_c.position.x-curr_pose_trans.pose.position.x)) - yaw);
meas_pts.range[3] = sqrt(pow((right_l_c.position.x-curr_pose_trans.pose.position.x),2)+pow((right_l_c.position.y-curr_pose_trans.pose.position.y),2));                
meas_pts.bearing[3] = normalizeangle(atan2((right_l_c.position.y-curr_pose_trans.pose.position.y),(right_l_c.position.x-curr_pose_trans.pose.position.x)) - yaw);

meas_pts.range[4] = sqrt(pow((left_line_1_trans.pose.position.x-curr_pose_trans.pose.position.x),2)+pow((left_line_1_trans.pose.position.y-curr_pose_trans.pose.position.y),2));        
meas_pts.range[5] = sqrt(pow((right_line_1_trans.pose.position.x-curr_pose_trans.pose.position.x),2)+pow((right_line_1_trans.pose.position.y-curr_pose_trans.pose.position.y),2)); 
meas_pts.bearing[4] = normalizeangle(atan2((left_line_1_trans.pose.position.y-curr_pose_trans.pose.position.y),(left_line_1_trans.pose.position.x-curr_pose_trans.pose.position.x)) - yaw);
meas_pts.bearing[5] = normalizeangle(atan2((right_line_1_trans.pose.position.y-curr_pose_trans.pose.position.y),(right_line_1_trans.pose.position.x-curr_pose_trans.pose.position.x)) - yaw);

        line_strip_1.header.stamp = ros::Time::now();
        line_strip_2.header.stamp = ros::Time::now();
        final_line.header.stamp = ros::Time::now();
        meas_pts.header.stamp = ros::Time::now();
        landmarks_pos.header.stamp = ros::Time::now();
        curr_pose_trans.header.stamp = ros::Time::now();

        if(new_row == true){
        visualization_msgs::Marker empty_line_strip_1, empty_line_strip_2, empty_final_line;
        thorvald_2d_nav::scan_detected_line empty_meas_pts; 
        thorvald_2d_nav::landmarks empty_landmarks_pos;
        line_strip_1 = empty_line_strip_1;
        line_strip_2 = empty_line_strip_2;
        final_line = empty_final_line;
        meas_pts = empty_meas_pts;
        landmarks_pos = empty_landmarks_pos;
        marker_pub_1.publish(line_strip_1);
        marker_pub_2.publish(line_strip_2);
        marker_pub_3.publish(final_line);
        point_pub.publish(meas_pts);
        landmarks_pub.publish(landmarks_pos);
        new_row = false;
        }
        else{
        marker_pub_1.publish(line_strip_1);
        marker_pub_2.publish(line_strip_2);
        marker_pub_3.publish(final_line);
        point_pub.publish(meas_pts);
        landmarks_pub.publish(landmarks_pos);
        }   
 
        curr_pose_trans.header.frame_id = "/map";
        thor_pub.publish(curr_pose_trans);   
 
        r.sleep();
	} // node shutdown
  return 0;
}

