#include "ros/ros.h"
#include "thorvald_2d_nav/GpsSwitch.h"
#include <sensor_msgs/NavSatFix.h>

sensor_msgs::NavSatFix gps_pt;
int count = 0;
char new_gps;

  
void fixCallback(const sensor_msgs::NavSatFix gps_msg){
gps_pt = gps_msg;
}


bool add(thorvald_2d_nav::GpsSwitch::Request &req, thorvald_2d_nav::GpsSwitch::Response &res)
   {
     ROS_INFO("waiting for: x= %ld seconds", (long int)req.a);
     ros::Duration(req.a).sleep();
     res.gps_switch = 1;
     count = 1;
     return true;
   }
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "gps_switch_server");
     ros::NodeHandle n;
     ros::Rate r(1); // 1 hz
   
     ros::ServiceServer service = n.advertiseService("gps_switch", add);
     ros::Subscriber gps_sub = n.subscribe("gps/fix", 100, fixCallback);
     ros::Publisher gps_pub = n.advertise<sensor_msgs::NavSatFix>( "new_gps/fix", 1 );

     while(ros::ok()){
      
      if (count == 0){
       gps_pub.publish(gps_pt);
       } 
      else{
       gps_pub.publish(gps_pt);
       } 

      ros::spinOnce();	
      r.sleep();

     }
   
     return 0;
   }
