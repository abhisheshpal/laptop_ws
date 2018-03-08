#include <ros/ros.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <tf/tf.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Float64MultiArray.h>
#include <visualization_msgs/Marker.h>

sensor_msgs::LaserScan scan_msg_main;
int dummy = 0;

// Laser Scan data
void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
        // size_t num_ranges = scan_msg->ranges.size();
        scan_msg_main.ranges = scan_msg->ranges;
        scan_msg_main.angle_min = scan_msg->angle_min;
        scan_msg_main.angle_increment = scan_msg->angle_increment;
} // callback end

int main(int argc, char** argv)
{
	ros::init(argc, argv, "laser_points");
	ros::NodeHandle n;

        ros::Rate r(1);

        // Subscribers
	ros::Subscriber scan_sub_test = n.subscribe("scan", 100, scanCallback);

        int point_count = 0;

        // Publishers
        // ros::Publisher marker_pub_1 = n.advertise<std_msgs::Int64>("total_points_count", 10);

        while (ros::ok()){

	ros::spinOnce();

        if (scan_msg_main.ranges.size() > 0 && (dummy == 0)){  

	for (int i_1 = 270; i_1 <= 960; i_1++){ // check the min to max angles 

          if((scan_msg_main.ranges[i_1] > 0) && (scan_msg_main.ranges[i_1] < 1.5) ){
          point_count = point_count + 1;
          } // if loop end
        } // laser scan loop end
        dummy = 1;
        std::cout << "pt_count" << point_count << std::endl;
        }

	} // node shutdown

  r.sleep();
  return 0;
}

