#include "test_row_transition.h"

// Laser Scan data
void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
        num_ranges = scan_msg->ranges.size();
        scan_msg_main.header.stamp = scan_msg->header.stamp;
        scan_msg_main.ranges = scan_msg->ranges;
        scan_msg_main.angle_min = scan_msg->angle_min;
        scan_msg_main.angle_increment = scan_msg->angle_increment;

} // callback end

// Thorvald Estimated Pose data
void robotposeCallback (const nav_msgs::Odometry::ConstPtr& pose_msg)
{
thorvald_pose.pose.pose = pose_msg->pose.pose;

tf::Quaternion quat(thorvald_pose.pose.pose.orientation.x,thorvald_pose.pose.pose.orientation.y, thorvald_pose.pose.pose.orientation.z, thorvald_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

// Pole detection
void Pole_detection(sensor_msgs::LaserScan scan_msg_poles, double itr_begin, double itr_end){

if(goal_found == false){

double thershold = 0.2;
int initial_count_1 = 0, initial_count_2 = 0;
double x[num_ranges], y[num_ranges], angle[num_ranges];
double range_1[num_ranges], count_angle_1[num_ranges], count_angle_2[num_ranges];
double array_1[num_ranges], array_2[num_ranges], array_3[num_ranges]; 
double Current_x_1, Current_y_1;
double sum_k[num_ranges];

//---------------------- FIRST MARKER ---------------------------//
	for (int i = itr_begin; i < (itr_end); i++){
           if((scan_msg_poles.ranges[i] < min_range)){
            initial_count_1 = initial_count_1 + 1;
            angle[initial_count_1] = scan_msg_poles.angle_min+i*scan_msg_poles.angle_increment;
            x[initial_count_1] = scan_msg_poles.ranges[i]*cos(angle[initial_count_1]);
            y[initial_count_1] = scan_msg_poles.ranges[i]*sin(angle[initial_count_1]);
            count_angle_1[initial_count_1] = i;
           }
         } // for loop 	

          int random_count_1 = rand()% (initial_count_1);
          double current_itr_1 = count_angle_1[random_count_1];
          current_range_1 = scan_msg_poles.ranges[current_itr_1];
          angle_1 = scan_msg_poles.angle_min + current_itr_1*scan_msg_poles.angle_increment;
          Current_x_1 = x[random_count_1];
          Current_y_1 = y[random_count_1];
        for (int j = 1 ; j <= (initial_count_1); j++){
          double itr_loop_1 = count_angle_1[j];
  	  // double obst_dist_1 = sqrt(pow(y[j]-Current_y_1,2) + pow(x[j]-Current_x_1,2)); // error calculation
  	  double obst_dist_1 = (current_range_1 - scan_msg_poles.ranges[itr_loop_1]); // error calculation
          if (thershold > fabs(obst_dist_1) ){
	     // sum_x_1+=x[j];
	     // sum_y_1+=y[j];
              k = k + 1;
              sum_k[k] = count_angle_1[j];
          }
          else{
            unfit = unfit + 1;
            array_1[unfit] = itr_loop_1;
          }         
        }

//---------------------- SECOND MARKER ---------------------------//
  if(unfit>0){
  double sum_q[num_ranges];
  int random_count_2 = rand()% (unfit);
  double current_itr_2 = array_1[random_count_2];
  current_range_2 = scan_msg_poles.ranges[current_itr_2];
  angle_2 = scan_msg_poles.angle_min + current_itr_2*scan_msg_poles.angle_increment;
  for (int p = 1 ; p <= (unfit); p++){
   double itr_loop_2 = array_1[p];
   double obst_dist_2 = (current_range_2 - scan_msg_poles.ranges[itr_loop_2]); // error calculation
   if (thershold > fabs(obst_dist_2)){
   q = q + 1;
   sum_q[q] = array_1[p];

   }
   else{
    unfit_1 = unfit_1 + 1;
    array_2[unfit_1] = itr_loop_2; 
    }         
   }  
  } 

//---------------------- THIRD MARKER ---------------------------//

  double sum_n[num_ranges];

	for (int r = 540; r <=840; r++){
           if((scan_msg_poles.ranges[r] < min_range)){
            initial_count_2 = initial_count_2 + 1;
            count_angle_2[initial_count_2] = r;
           }
         } // for loop 	

          int random_count_3 = rand()% (initial_count_2);
          double current_itr_3 = count_angle_2[random_count_3];
          current_range_3 = scan_msg_poles.ranges[current_itr_3];
          angle_3 = scan_msg_poles.angle_min + current_itr_3*scan_msg_poles.angle_increment;

        for (int m = 1 ; m <= (initial_count_2); m++){
          double itr_loop_3 = count_angle_2[m];
  	  double obst_dist_3 = (current_range_3 - scan_msg_poles.ranges[itr_loop_3]); // error calculation
          if (thershold > fabs(obst_dist_3) ){
	      // sum_x_1+=x[j];
	      // sum_y_1+=y[j];
              n = n + 1;
              sum_n[n] = count_angle_2[m];
          }       
        }


//---------------------- GOAL ---------------------------// 
geometry_msgs::PoseStamped pole_1, pole_1_transformed;
geometry_msgs::PoseStamped pole_2, pole_2_transformed;
geometry_msgs::PoseStamped pole_3, pole_3_transformed;

pole_1.header.frame_id = "hokuyo";
pole_1.pose.position.x = current_range_1*cos(angle_1);
pole_1.pose.position.y = current_range_1*sin(angle_1);

pole_2.header.frame_id = "hokuyo";
pole_2.pose.position.x = current_range_2*cos(angle_2);
pole_2.pose.position.y = current_range_2*sin(angle_2);

pole_3.header.frame_id = "hokuyo";
pole_3.pose.position.x = current_range_3*cos(angle_3);
pole_3.pose.position.y = current_range_3*sin(angle_3);

 try{
   transformStamped = tfBuffer.lookupTransform("map", "hokuyo", ros::Time(0));
 }
 catch (tf2::TransformException &ex){
   ROS_WARN("%s",ex.what());
   ros::Duration(1.0).sleep();
   // continue;
 }

tf2::doTransform(pole_1, pole_1_transformed, transformStamped);
tf2::doTransform(pole_2, pole_2_transformed, transformStamped);
tf2::doTransform(pole_3, pole_3_transformed, transformStamped);

  marker_1.header.frame_id = "map";
  marker_1.ns = "poles_1";
  marker_1.id = 1;
  marker_1.type = visualization_msgs::Marker::CYLINDER;
  marker_1.action = visualization_msgs::Marker::ADD;
  marker_1.pose.position.x = pole_1_transformed.pose.position.x;
  marker_1.pose.position.y = pole_1_transformed.pose.position.y;
  marker_1.pose.position.z = 0.75;
  marker_1.pose.orientation.w = 1.0;
  marker_1.scale.x = 0.05;
  marker_1.scale.y = 0.05;
  marker_1.scale.z = 0.2;
  marker_1.color.a = 1.0; // Don't forget to set the alpha!
  marker_1.color.b = 1.0;

  if(q>5){
  marker_2.header.frame_id = "map";
  marker_2.ns = "poles_2";
  marker_2.id = 2;
  marker_2.type = visualization_msgs::Marker::CYLINDER;
  marker_2.action = visualization_msgs::Marker::ADD;
  marker_2.pose.position.x = pole_2_transformed.pose.position.x;
  marker_2.pose.position.y = pole_2_transformed.pose.position.y;
  marker_2.pose.position.z = 0.75;
  marker_2.pose.orientation.w = 1.0;
  marker_2.scale.x = 0.05;
  marker_2.scale.y = 0.05;
  marker_2.scale.z = 0.2;
  marker_2.color.a = 1.0; // Don't forget to set the alpha!
  marker_2.color.b = 1.0;
  }

  marker_3.header.frame_id = "map";
  marker_3.ns = "poles_3";
  marker_3.id = 3;
  marker_3.type = visualization_msgs::Marker::CYLINDER;
  marker_3.action = visualization_msgs::Marker::ADD;
  marker_3.pose.position.x = pole_3_transformed.pose.position.x;
  marker_3.pose.position.y = pole_3_transformed.pose.position.y;
  marker_3.pose.position.z = 0.75;
  marker_3.pose.orientation.w = 1.0;
  marker_3.scale.x = 0.05;
  marker_3.scale.y = 0.05;
  marker_3.scale.z = 0.2;
  marker_3.color.a = 1.0; // Don't forget to set the alpha!
  marker_3.color.b = 1.0;
  
 if(unfit>0){

  if((marker_1.pose.position.y < marker_2.pose.position.y)&&(marker_1.pose.position.y < marker_3.pose.position.y)){
  nearest_pole_x = marker_1.pose.position.x;
  nearest_pole_y = marker_1.pose.position.y;
  next_nearest_pole_x = marker_2.pose.position.x;
  next_nearest_pole_y = std::fmin(marker_2.pose.position.y, marker_3.pose.position.y);
  farthest_pole_x = marker_3.pose.position.x;
  farthest_pole_y = std::fmax(marker_2.pose.position.y, marker_3.pose.position.y);
  }
  else{
  if(marker_2.pose.position.y < marker_3.pose.position.y) {
   nearest_pole_x = marker_2.pose.position.x;
   nearest_pole_y = marker_2.pose.position.y;
   next_nearest_pole_x = marker_3.pose.position.x;
   next_nearest_pole_y = std::fmin(marker_1.pose.position.y,marker_3.pose.position.y);
   farthest_pole_x = marker_3.pose.position.x;
   farthest_pole_y = std::fmax(marker_1.pose.position.y,marker_3.pose.position.y);
  }
  else{
  nearest_pole_x = marker_3.pose.position.x;
  nearest_pole_y = marker_3.pose.position.y;
  next_nearest_pole_x = marker_1.pose.position.x;
  next_nearest_pole_y = std::fmin(marker_1.pose.position.y,marker_2.pose.position.y);
  farthest_pole_x = marker_1.pose.position.x;
  farthest_pole_y = std::fmax(marker_1.pose.position.y,marker_2.pose.position.y);
  }
}

  marker_goal_1.header.frame_id = "map";
  marker_goal_1.ns = "poles_g";
  marker_goal_1.id = 3;
  marker_goal_1.type = visualization_msgs::Marker::CYLINDER;
  marker_goal_1.action = visualization_msgs::Marker::ADD;
  marker_goal_1.pose.position.x = ((nearest_pole_x + next_nearest_pole_x)/2) + 1.5;
  marker_goal_1.pose.position.y = (nearest_pole_y + next_nearest_pole_y)/2;
  marker_goal_1.pose.position.z = 0.75;
  marker_goal_1.pose.orientation.w = 1.0;
  marker_goal_1.scale.x = 0.05;
  marker_goal_1.scale.y = 0.05;
  marker_goal_1.scale.z = 0.3;
  marker_goal_1.color.a = 1.0; // Don't forget to set the alpha!
  marker_goal_1.color.g = 1.0;

  marker_goal_2.header.frame_id = "map";
  marker_goal_2.ns = "poles_g";
  marker_goal_2.id = 3;
  marker_goal_2.type = visualization_msgs::Marker::CYLINDER;
  marker_goal_2.action = visualization_msgs::Marker::ADD;
  marker_goal_2.pose.position.x = ((farthest_pole_x + next_nearest_pole_x)/2) + 1.5;
  marker_goal_2.pose.position.y = (farthest_pole_y + next_nearest_pole_y)/2;
  marker_goal_2.pose.position.z = 0.75;
  marker_goal_2.pose.orientation.w = 1.0;
  marker_goal_2.scale.x = 0.05;
  marker_goal_2.scale.y = 0.05;
  marker_goal_2.scale.z = 0.3;
  marker_goal_2.color.a = 1.0; // Don't forget to set the alpha!
  marker_goal_2.color.g = 1.0;

  switch(turn_side){
  case RIGHT: 
  goal_pt[1].position.x = marker_goal_2.pose.position.x;
  goal_pt[1].position.y = marker_goal_2.pose.position.y;
  goal_pt[2].position.x = marker_goal_1.pose.position.x;
  goal_pt[2].position.y = marker_goal_1.pose.position.y;
  break;

  case LEFT: 
  goal_pt[1].position.x = marker_goal_1.pose.position.x;
  goal_pt[1].position.y = marker_goal_1.pose.position.y;
  goal_pt[2].position.x = marker_goal_2.pose.position.x;
  goal_pt[2].position.y = marker_goal_2.pose.position.y;
  break;
 }

  goal_found = true; 
  }
}

}

double pure_pursuit(double obs_range, double obs_bearing){
double robotlength = 1.1;
double steeringAngle = atan(2*robotlength*sin(obs_bearing))/obs_range;
return steeringAngle;
}

bool change_row(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     row_transit_mode = row_transit_mode + req.counter;
     ROS_INFO("transition service on time");
     return true;
   }


int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_row_transition");
  ros::NodeHandle n;

  // Subscribers
  ros::Subscriber scan_sub_test = n.subscribe("scan", 100, scanCallback);
  ros::Subscriber pose_sub = n.subscribe("/thorvald_ii/odom", 100, robotposeCallback);

  // Publishers
  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);
  ros::Publisher vis_pub_1 = n.advertise<visualization_msgs::Marker>( "pole_marker_1", 1 );
  ros::Publisher vis_pub_2 = n.advertise<visualization_msgs::Marker>( "pole_marker_2", 1 );
  ros::Publisher vis_pub_3 = n.advertise<visualization_msgs::Marker>( "pole_marker_3", 1 );
  ros::Publisher vis_pub_5 = n.advertise<visualization_msgs::Marker>( "goal_marker_1", 1 );
  ros::Publisher vis_pub_6 = n.advertise<visualization_msgs::Marker>( "goal_marker_2", 1 );

  // Service Servers
  ros::ServiceServer service = n.advertiseService("/row_transition_mode", change_row);

  // Service Client
  ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_end_1");
  ros::ServiceClient client1 = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_end_2");

  ros::Rate r(1.0);

  tf2_ros::TransformListener tfListener(tfBuffer);

  while (ros::ok()){
  ros::spinOnce();

  if(row_transit_mode == 2){
  est_twist.linear.x = 0.0; 
  est_twist.angular.z = 0.0;
  twist_gazebo.publish(est_twist);
  goto stopover;
  }

  if ((scan_msg_main.ranges.size() > 0) && (row_transit_mode>0) && (row_transit_mode == row_transit)){ // scan check  

   if(turn_side == 1){
   min_itr = 1;
   max_itr = 540;
   }

   if(turn_side == 2){
   min_itr = 540;
   max_itr = 1079;
   }

  Pole_detection(scan_msg_main, min_itr , max_itr); // pole detection

  if(goal_found == true){
   goal_range = sqrt(pow((goal_pt[goal_transit].position.y - thorvald_pose.pose.pose.position.y),2) + pow((goal_pt[goal_transit].position.x - thorvald_pose.pose.pose.position.x),2));
   goal_bearing = atan2((goal_pt[goal_transit].position.y-thorvald_pose.pose.pose.position.y),(goal_pt[goal_transit].position.x - thorvald_pose.pose.pose.position.x)) - yaw;

   angular_velocity = pure_pursuit(goal_range, goal_bearing); //pure pursuit controller

   if(goal_range < 0.15){
    est_twist.linear.x = 0.0; 
    est_twist.angular.z = 0.0;

  switch(turn_side){ 
    case RIGHT:
    if(yaw>=(-(goal_transit*1.50))){
    est_twist.angular.z = -0.20; 
    turn_90=false;  
    }
    else if((yaw<=-3.0)&&(yaw>=-3.14)){ 
    est_twist.angular.z = fabs(yaw)-3.14; 
    }
    else{
    turn_90 = true;
    goal_transit = 2;
    est_twist.angular.z = 0.0;
    }
    break;

    case LEFT:
    if(yaw<=(goal_transit*1.50)){
    est_twist.angular.z = 0.20; 
    turn_90=false;  
    }
    else if((yaw>=3.0)&&(yaw<=3.14)){ 
    est_twist.angular.z = 3.14-yaw; 
    }
    else{
    turn_90 = true;
    goal_transit = 2;
    est_twist.angular.z = 0.0;
    }
    break;
   }

   } 
   else{
   est_twist.linear.x = linear_velocity; 
   est_twist.angular.z = 0;
   }

//  std::cout << "goal_range" << goal_range << "\n" << "yaw" << yaw << "\n" << std::endl;

   // Service for end of row transition
   if ((turn_90 = true) && (goal_transit==2) && ((yaw >= 3.12)||(yaw<=-3.12))){
     // std::cout << "final_yaw" << yaw << "\n"<< std::endl;
     end_row_transit.request.counter = 1;
     end_row_transit_1.request.counter = 1;
     est_twist.angular.z = 0;
     row_transit = 1 + row_transit_mode;

     switch(turn_side){
      case RIGHT: 
      turn_side = 2;
      ROS_INFO("Turning Right");
      break;

      case LEFT:
      turn_side = 1;
      ROS_INFO("Turning Left");
      break;
     }

     if (client.call(end_row_transit)){ 
     ROS_INFO("End of the row transition");
     goal_transit = 1;
     } 
     if (client1.call(end_row_transit_1)){} 
   }


  } // goal check 

  // publish the markers
  marker_1.header.stamp = ros::Time::now();
  marker_2.header.stamp = ros::Time::now();
  marker_3.header.stamp = ros::Time::now();
  marker_goal_1.header.stamp = ros::Time::now();
  marker_goal_2.header.stamp = ros::Time::now();

  vis_pub_1.publish(marker_1);
  vis_pub_2.publish(marker_2);
  vis_pub_3.publish(marker_3);
  vis_pub_5.publish(marker_goal_1);
  vis_pub_6.publish(marker_goal_2);

  twist_gazebo.publish(est_twist);
  } // scan check

  stopover:
  r.sleep();
  } // node shutdown
 return 0;
} // main loop end
