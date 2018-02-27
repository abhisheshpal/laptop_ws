#include "ros/ros.h"
#include "thorvald_2d_nav/GpsSwitch.h"
#include <cstdlib>
 
int main(int argc, char **argv)
  {
    ros::init(argc, argv, "gps_switch_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::GpsSwitch>("gps_switch");
    thorvald_2d_nav::GpsSwitch srv;
     srv.request.a = atoll(argv[1]);
    //srv.request.a = 5.0;

    if (client.call(srv))
     {
      ROS_INFO("Service completed");
     }
    else
     {
       ROS_ERROR("Failed to call service gps_switch");
       return 1;
     }
   
     return 0;
  }
