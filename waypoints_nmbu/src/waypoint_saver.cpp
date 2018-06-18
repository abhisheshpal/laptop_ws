#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <vector>
#include <fstream>
#include <string>

int total_waypts = 10;
sensor_msgs::Joy joy_msgs;
std::vector<geometry_msgs::PointStamped> waypoints_;
geometry_msgs::PoseStamped finish_pose_;
int save_joy_button_;
std::string filename, world_frame_, robot_frame_;

void waypointsJoyCallback(const sensor_msgs::Joy &joy_msg){
joy_msgs.buttons.resize(15);

if(joy_msg.buttons.size()>0){
for(int bns = 0; bns<(joy_msg.buttons.size()); bns++){
joy_msgs.buttons[bns] = joy_msg.buttons[bns];
}}

}	

int main(int argc, char *argv[]){
    ros::init(argc, argv, "waypoints_saver");
    ros::NodeHandle nh_;
    ros::Rate r(1);

    ros::Subscriber waypoints_joy_sub_ = nh_.subscribe("/teleop_joy/joy", 10, &waypointsJoyCallback);
  
    std::string filename = "";
    nh_.param("/waypoint_saver/filename", filename, filename);
    nh_.param("/waypoint_saver/save_joy_button", save_joy_button_, 0);
    nh_.param("robot_frame", robot_frame_, std::string("/base_link"));
    nh_.param("world_frame", world_frame_, std::string("/map"));

    tf::TransformListener tf_listener_;
    ros::Duration duration_min(2.0);
    ros::Time time_current, time_last;
    time_current = ros::Time::now();
    time_last = ros::Time::now();

    while(nh_.ok()){

    ros::spinOnce();

    time_current = ros::Time::now();
    if(joy_msgs.buttons.size()>0){
    
     if(joy_msgs.buttons[save_joy_button_] == 1 && ((time_current-time_last) > duration_min)){
     tf::StampedTransform robot_gl;
     try{
     tf_listener_.lookupTransform(world_frame_, robot_frame_, ros::Time(0.0), robot_gl);
     geometry_msgs::PointStamped point;
     point.point.x = robot_gl.getOrigin().x();
     point.point.y = robot_gl.getOrigin().y();
     point.point.z = robot_gl.getOrigin().z();
     waypoints_.push_back(point);
     time_last = time_current;
     ROS_INFO("New waypoint saved");
     }catch(tf::TransformException &e){
     ROS_WARN_STREAM("tf::TransformException: " << e.what());
     }
     if(waypoints_.size()>total_waypts){
     std::ofstream ofs(filename.c_str(), std::ios::out);   
     if(ofs.is_open())
     {     
     ofs << "waypoints:" << std::endl;
     for(int i=0; i < waypoints_.size(); i++){
      ofs << "    " << "- point:" << std::endl;
      ofs << "        x: " << waypoints_[i].point.x << std::endl;
      ofs << "        y: " << waypoints_[i].point.y << std::endl;
      ofs << "        z: " << waypoints_[i].point.z << std::endl;
     }
      } 
      ROS_INFO_STREAM("Writing waypoints data to " << filename);
      ofs.close();
     }
    }
   }
   r.sleep();
  }
  return 0;
}
