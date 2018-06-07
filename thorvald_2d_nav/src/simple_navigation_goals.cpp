#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_datatypes.h>

#include <boost/thread.hpp>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>

// geometry_msgs::Pose goal_1;
// double counter_no = 0;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
/*int i = 0;

double x [2] = {-0.731294, 0.62}; 
double y [2] = {1.61555, 1.61555};

int lenght0f_Array = sizeof(x) / sizeof(x[0]);

void spinThread(){
  ros::spin();
}

// Laser Scan data
void fgoalCallback (const visualization_msgs::Marker::ConstPtr& goal_msg)
{
goal_1.position.x = goal_msg->pose.position.x;
goal_1.position.y = goal_msg->pose.position.y;
counter_no = 1;
  // std::cout << "goal_1.position.x:" << goal_1.position.x << "\n" << std::endl;
  //  std::cout << "goal_1.position.y:" << goal_1.position.y << "\n" << std::endl;
}*/

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  // ros::NodeHandle n;

  // Subscribers
  // ros::Subscriber scan_sub_test = n.subscribe("goal_marker_1", 100, fgoalCallback);

  // boost::thread spin_thread = boost::thread(boost::bind(&spinThread));

 // MoveBaseClient ac("pose_base_controller");
 //give some time for connections to register
 // sleep(2.0);
 // while (ros::ok()){
 // ros::spinOnce();

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
  ROS_INFO("Waiting for the move_base action server to come up");
  }

  //Declaring move base goal
  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 2 meters forward
  goal.target_pose.header.frame_id = "odom";
  goal.target_pose.header.stamp = ros::Time::now();
  // if(counter_no == 1){
 // for( int i = 0; i <= 0; i++){
 // ROS_INFO("anc");
  //if(i==0){
  goal.target_pose.pose.position.x =  -0.746;
  goal.target_pose.pose.position.y =  1.615;
  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(0);
 // }
 /* if(i==1){
  goal.target_pose.pose.position.x =  0.62;
  goal.target_pose.pose.position.y =  1.615;
  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(0);
  }*/
  // std::cout << "goal.target_pose.pose.position.x:" <<  goal.target_pose.pose.position.x << "\n" << std::endl;
  // std::cout << "goal.target_pose.pose.position.y:" << goal.target_pose.pose.position.y << "\n" << std::endl;
  ROS_INFO("Sending Goal");
  ac.sendGoal(goal);
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to the desired goal");    
  }
  else{
  ROS_INFO("The base failed to move to the desired goal");
  }

// } //callback check


 // } // node shutdown check
  return 0;
}

