#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/MarkerArray.h>
#include <yaml-cpp/yaml.h>
#include <nav_msgs/Odometry.h>

#include <vector>
#include <fstream>
#include <string>
#include <exception>
#include <math.h>
#include <limits>

// ROS message includes
#include <thorvald_2d_nav/sub_goal.h>

int row_transit_mode = 0, turn_side = 1, row_no = 0;
geometry_msgs::Twist nav_velocities;
geometry_msgs::PoseArray waypoints_;
geometry_msgs::Pose current_waypoint_, curr_pose_;
nav_msgs::Odometry odom_curr;
geometry_msgs::Pose last_waypoint_;
std::string robot_frame_, world_frame_;
double q_x, q_y, position_error_, angular_error_;
geometry_msgs::PointStamped curr_pose; 
int total_waypoints = 1, no = 0, present_waypoints = 1;
std::string filename;
double yaw, yaw1, K_p = 0.05, sub_count = 0;
double lin_vel_max = 0.2, ang_vel_max = 1.57;
thorvald_2d_nav::sub_goal end_row_transit, end_row_transit_1, end_row_transit_2;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void computeWpOrientation(int no){
       // for(int it = 0; it < total_waypoints; it++){
         //   double goal_direction = atan2(waypoints_.poses[it+1].position.y - waypoints_.poses[it].position.y,
           //                               waypoints_.poses[it+1].position.x - waypoints_.poses[it].position.x);
        //}

        waypoints_.poses[1].orientation = tf::createQuaternionMsgFromYaw(3.14);
        waypoints_.poses[2].orientation = tf::createQuaternionMsgFromYaw(1.57);
       // waypoints_.poses[3].orientation = tf::createQuaternionMsgFromYaw(0);
        waypoints_.header.frame_id = world_frame_;
        waypoints_.header.stamp = ros::Time::now();
    }

   bool readFile(const std::string &filename){
        waypoints_.poses.clear();
        try{
            std::ifstream ifs(filename.c_str(), std::ifstream::in);
            if(ifs.good() == false){
                return false;            
            }

            YAML::Node node;           
            node = YAML::Load(ifs);
            const YAML::Node &wp_node_tmp = node["waypoints"];
            const YAML::Node *wp_node = wp_node_tmp ? &wp_node_tmp : NULL;

            geometry_msgs::Pose pose;
            if(wp_node != NULL){
                for(int i=0; i < wp_node->size(); i++){
                    
                     std::string point_x = (*wp_node)[i]["point"]["x"].as<std::string>();
                     std::string point_y = (*wp_node)[i]["point"]["y"].as<std::string>();
                     std::string point_z = (*wp_node)[i]["point"]["z"].as<std::string>();
                     
                     pose.position.x = std::stof(point_x);
                     pose.position.y = std::stof(point_y);
                     pose.position.z = std::stof(point_z);
                     waypoints_.poses.push_back(pose);
                }
            
            }
            else{
                return false;
             } 
       }

       catch(YAML::ParserException &e){
       ROS_ERROR("waypoint file cannot be opened!");
       }
   return true;
  } 

   double normalize_angle(double angle_n){
    if(angle_n > M_PI){
    angle_n = angle_n - 2*M_PI;
    }
    if(angle_n < -M_PI){
    angle_n = angle_n + 2*M_PI;
    }
   return angle_n;
   }

   void odomcallback(const nav_msgs::Odometry &odom_msg){
   odom_curr.pose = odom_msg.pose;
   odom_curr.twist = odom_msg.twist;

   tf::Quaternion quat1(odom_curr.pose.pose.orientation.x,odom_curr.pose.pose.orientation.y, odom_curr.pose.pose.orientation.z, odom_curr.pose.pose.orientation.w);
   quat1 = quat1.normalize();
   yaw1 = tf::getYaw(quat1);
   sub_count = 1;
   }

   void roboposcallback(const geometry_msgs::Pose &rob_pose_msg){
   curr_pose_.position = rob_pose_msg.position;
   curr_pose_.orientation = rob_pose_msg.orientation;

   tf::Quaternion quat(curr_pose_.orientation.x,curr_pose_.orientation.y, curr_pose_.orientation.z, curr_pose_.orientation.w);
   quat = quat.normalize();
   yaw = tf::getYaw(quat);
   sub_count = 1;
   }

   geometry_msgs::Twist waypoint_control(geometry_msgs::Pose current_goal, double pos_err, double ang_err){
   nav_velocities.linear.x = K_p * pos_err;
   nav_velocities.angular.z = K_p * ang_err;

   if(nav_velocities.linear.x > lin_vel_max) nav_velocities.linear.x = lin_vel_max;
   if(nav_velocities.angular.z > ang_vel_max) nav_velocities.angular.z = ang_vel_max;

   return nav_velocities;
   }


bool change_row(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     row_transit_mode = row_transit_mode + req.counter;
     ROS_INFO("transition service on time");
     if(row_transit_mode == 2){
     no = 2;
     present_waypoints = 2;
     current_waypoint_ = waypoints_.poses[no];}
     
     if((row_transit_mode%2) == 0){
     turn_side = 2;
     }
     else{
     turn_side = 1;
     }
     return true;
   }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gps_waypoints_nav_mb_sim");
  ros::NodeHandle n;
  ros::Rate r(1); // 1 hz

  // Publishers
  ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/nav_vel",1);
  ros::Publisher waypoints_loc_ = n.advertise<geometry_msgs::PoseArray>("/way_pts",1);

  // Subscribers
  ros::Subscriber odom_gaz_sub_ = n.subscribe("/odometry/filtered/local",1, &odomcallback);
  ros::Subscriber robo_pos_sub_ = n.subscribe("/thorvald_pose",1, &roboposcallback);
 
  // Service Servers
  ros::ServiceServer service = n.advertiseService("/row_transition_mode", change_row);

  // Service Client
  ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_end_1");
  ros::ServiceClient client1 = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_end_2");
  ros::ServiceClient client2 = n.serviceClient<thorvald_2d_nav::sub_goal>("/row_transition_end_3");
  
  // Params
  n.param("robot_frame", robot_frame_, std::string("/base_link"));
  n.param("world_frame", world_frame_, std::string("/map"));
  n.param("/gps_waypoints_nav_mb/total_waypoints", total_waypoints, 2);
  std::string filename = "";
  n.getParam("/gps_waypoints_nav_mb/filename", filename);

   if(filename != ""){
   ROS_INFO_STREAM("Read waypoints data from " << filename);
    if(!readFile(filename)) {
    ROS_ERROR("Failed loading waypoints file");
   }
    else{
    last_waypoint_ = waypoints_.poses[total_waypoints];
    waypoints_.poses[0].orientation = tf::createQuaternionMsgFromYaw(1.57);
    computeWpOrientation(no);
    }
   current_waypoint_ = waypoints_.poses[0];
   } 
   else{
   ROS_ERROR("waypoints file doesn't have name");
   }
  
  while(n.ok()){

  ros::spinOnce();

   if((sub_count==1) && (row_transit_mode>row_no)){ // sub check
      
      Next_pt:
      if(no<(present_waypoints+1)){ 
           // tell the action client that we want to spin a thread by default
           MoveBaseClient ac("move_base", true);

           // wait for the action server to come up
           while(!ac.waitForServer(ros::Duration(5.0))){
           ROS_INFO("Waiting for the move_base action server to come up");
           }

           // Declaring move base goal
           move_base_msgs::MoveBaseGoal goal;
           
           // we'll send a goal to the robot to move 2 meters forward
           goal.target_pose.header.frame_id = "map";
           goal.target_pose.header.stamp = ros::Time::now();
           goal.target_pose.pose.position.x =  current_waypoint_.position.x;
           goal.target_pose.pose.position.y =  current_waypoint_.position.y;
           goal.target_pose.pose.orientation = current_waypoint_.orientation;    
           ROS_INFO("SENDING GOAL!!!");
           ac.sendGoal(goal);
           ac.waitForResult();

           if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("Goal Reached");
            ROS_INFO("Go to next waypoint");
            no = no + 1;
            if(no<(present_waypoints+1)){ 
            current_waypoint_ = waypoints_.poses[no];
            }
            goto Next_pt;
           }
           else{ 
           ROS_INFO("Failed to reach the goal");
           }     
         }

         else{
          end_row_transit.request.counter = 1;
          end_row_transit_1.request.counter = 1;
          end_row_transit_2.request.counter = 1;
          if (client.call(end_row_transit)){ 
          ROS_INFO("End of Row Transition_1");
          } 
          if (client1.call(end_row_transit_1)){
          ROS_INFO("End of Row Transition_2");
          }
          if (client2.call(end_row_transit_2)){}
          nav_velocities.linear.x  = 0;
          nav_velocities.angular.z = 0;
          row_no = row_transit_mode;
         }
        } // sub check

  cmd_vel_pub_.publish(nav_velocities);
  waypoints_loc_.publish(waypoints_);
  r.sleep();
  }

return 0;
}
