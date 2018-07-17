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
   
int no = 0, total_waypoints = 3;
geometry_msgs::Pose current_waypoint_;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
geometry_msgs::PoseArray waypoints_;
std::string robot_frame_, world_frame_;

void computeWpOrientation(int no){
        for(int it = 0; it < total_waypoints; it++){
            double goal_direction = atan2(waypoints_.poses[it+1].position.y - waypoints_.poses[it].position.y,
                                          waypoints_.poses[it+1].position.x - waypoints_.poses[it].position.x);
        }

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


int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals_mb");
  ros::NodeHandle n;

  // Params
  n.param("robot_frame", robot_frame_, std::string("/base_link"));
  n.param("world_frame", world_frame_, std::string("/map"));
  n.param("/gps_waypoints_nav_mb/total_waypoints", total_waypoints, 3);
  std::string filename = "";
  n.getParam("/gps_waypoints_nav_mb/filename", filename);

   if(filename != ""){
   ROS_INFO_STREAM("Read waypoints data from " << filename);
    if(!readFile(filename)) {
    ROS_ERROR("Failed loading waypoints file");
    }
    else{
    waypoints_.poses[0].orientation = tf::createQuaternionMsgFromYaw(0);
    computeWpOrientation(no);
    }
    current_waypoint_ = waypoints_.poses[0];
    } 
    else{
    ROS_ERROR("waypoints file doesn't have name");
    }
  
     while(n.ok()){ 

     Next_pt:
     if(no<(total_waypoints)){ // number of iterations

     //tell the action client that we want to spin a thread by default
     MoveBaseClient ac("move_base", true);
   
     //wait for the action server to come up
     while(!ac.waitForServer(ros::Duration(5.0))){
       ROS_INFO("Waiting for the move_base action server to come up");
     }
   
     move_base_msgs::MoveBaseGoal goal;
   
     //we'll send a goal to the robot to move 1 meter forward
     goal.target_pose.header.frame_id = "map";
     goal.target_pose.header.stamp = ros::Time::now();
           
     goal.target_pose.pose.position.x =  current_waypoint_.position.x;
     goal.target_pose.pose.position.y =  current_waypoint_.position.y;
     goal.target_pose.pose.orientation = current_waypoint_.orientation;    
     ROS_INFO("SENDING GOAL!!!");
           
     ac.sendGoal(goal);
           
     ac.waitForResult();
   
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Waypoint Reached, Go to next waypoint");
      no = no + 1;
       if(no<(total_waypoints)){ 
       current_waypoint_ = waypoints_.poses[no];
       }
      goto Next_pt;
      }
      else{ 
      ROS_INFO("Failed to reach the goal");
      }

     } // number of iterations
    }
return 0;
 }
