#include "test_line_SLAM.h"

double dist_pt_l1[3], dist_pt_l2[3], result_1[2];
int min_itr[2], k, counter_sub;
double slope, expectedBearing, expectedRange;
geometry_msgs::Pose line_div_1,line_div_2;

// robot velocity data
void odometryvelCallback (const nav_msgs::Odometry::ConstPtr& odometry_vel){
robot_pose.pose.pose = odometry_vel->pose.pose;
robot_pose.twist.twist = odometry_vel->twist.twist;


counter_sub = 1;
}

// robot pose data
void odometryCallback (const geometry_msgs::Pose::ConstPtr& odomet){
thor_pose.position = odomet->position;
thor_pose.orientation = odomet->orientation;

tf::Quaternion quat(thor_pose.orientation.x,thor_pose.orientation.y, thor_pose.orientation.z, thor_pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

//line point data
void linepointsCallback(const thorvald_2d_nav::scan_detected_line::ConstPtr& line_points){

actual_meas.range.resize(6);
actual_meas.bearing.resize(6);

if (line_points->meas_update == true){
for (int num = 0; num < total_points; num++){
actual_meas.range[num] = line_points->range[num];
actual_meas.bearing[num] = line_points->bearing[num];
actual_meas.meas_update = line_points->meas_update;
}}

}

//line points 
void landmarksposeCallback (const thorvald_2d_nav::landmarks::ConstPtr& landmarks_msg)
{
landmarks_pose.x.resize(6);
landmarks_pose.y.resize(6);

if (landmarks_msg->landmark_check > 0){        
 for(int v=0; v<=5;v++){      
 landmarks_pose.x[v] = landmarks_msg->x[v];
 landmarks_pose.y[v] = landmarks_msg->y[v];
 }
landmarks_pose.landmark_check = landmarks_msg->landmark_check; 
landmarks_pose.row_number = landmarks_msg->row_number;
}

}

double normalizeangle(double bearing){
    if (bearing < -M_PI) {
        bearing += 2*M_PI;
    } else if (bearing > M_PI) {
        bearing -= 2*M_PI;
    }
}

//prediction step
void prediction_step(double dt){

  vx = robot_pose.twist.twist.linear.x;
  vy = robot_pose.twist.twist.linear.y;
  vth = robot_pose.twist.twist.angular.z;

  // Odometry Compensation   
  mu(0,0) = mu(0,0) + ((vx * cos(mu(2,0)) - vy * sin(mu(2,0)))*dt);
  mu(1,0) = mu(1,0) + ((vx * sin(mu(2,0)) + vy * cos(mu(2,0)))*dt);
  mu(2,0) = mu(2,0) + (vth*dt);
  mu(2,0)= normalizeangle(mu(2,0));

  MatrixXd Gt = MatrixXd(3,3);
  Gt << 1, 0, -vx * sin(mu(2,0)) - vy * cos(mu(2,0)),
        0, 1,  vx * cos(mu(2,0)) - vy * sin(mu(2,0)),
        0, 0,  0;

  R.topLeftCorner(3,3) << motion_noise, 0, 0,
                          0, motion_noise , 0,
                          0, 0,   motion_noise/10;

  cov.topLeftCorner(3,3) = Gt * cov.topLeftCorner(3,3) * Gt.transpose();
  cov.topRightCorner(3, 2*total_landmarks) = Gt * cov.topRightCorner(3, 2*total_landmarks);
  cov.bottomLeftCorner(2*total_landmarks, 3) = cov.topRightCorner(3, 2*total_landmarks).transpose();

  cov = cov + R; // Motion Noise

}

//correction step
void correction_step(double dt){

// Closest Point in the Line 1, Line 2
landmarks_pose.x[4] = (landmarks_pose.x[0]+landmarks_pose.x[1])/2;
landmarks_pose.y[4] = (landmarks_pose.y[0]+landmarks_pose.y[1])/2;
landmarks_pose.x[5] = (landmarks_pose.x[2]+landmarks_pose.x[3])/2;
landmarks_pose.y[5] = (landmarks_pose.y[2]+landmarks_pose.y[3])/2;

 
      for(int l1=0;l1<=1;l1++){
       dist_pt_l1[l1] = actual_meas.range[l1]-(thor_pose.position.x*cos(actual_meas.bearing[l1]))-(thor_pose.position.y*sin(actual_meas.bearing[l1])); 
       dist_pt_l2[l1] = actual_meas.range[l1+2]-(thor_pose.position.x*cos(actual_meas.bearing[l1+2]))-(thor_pose.position.y*sin(actual_meas.bearing[l1+2])); 
      }

      dist_pt_l1[2] = actual_meas.range[4]-(thor_pose.position.x*cos(actual_meas.bearing[4]))-(thor_pose.position.y*sin(actual_meas.bearing[4]));  
      dist_pt_l2[2] = actual_meas.range[5]-(thor_pose.position.x*cos(actual_meas.bearing[5]))-(thor_pose.position.y*sin(actual_meas.bearing[5])); 

      result_1[0] =  dist_pt_l1[0];
      min_itr[0] = 0;
      
      if((dist_pt_l1[1]<dist_pt_l1[0]) || (dist_pt_l1[2]<dist_pt_l1[0])){
        if(dist_pt_l1[1]< dist_pt_l1[2]){
        result_1[0] =  dist_pt_l1[1];
        min_itr[0] = 1;
        }
        else{
        result_1[0] =  dist_pt_l1[2];
        min_itr[0] = 4;
        }
      }

      result_1[1] =  dist_pt_l2[0];
      min_itr[1] = 2;
   
      if((dist_pt_l2[1]<dist_pt_l2[0]) || (dist_pt_l2[2]<dist_pt_l2[0])){
        if(dist_pt_l2[1]< dist_pt_l2[2]){
        result_1[1] =  dist_pt_l2[1];
        min_itr[1] = 3;
        }
        else{
        result_1[1] =  dist_pt_l2[2];
        min_itr[1] = 5;
        }
      }           

        std::cout << "min_itr[0]:" << min_itr[0] <<  "\n"<< "min_itr[1]:" << min_itr[1] <<  "\n" << std::endl;
      // Landmarks observation
     for (int z = 0; z < total_landmarks; z++){

      k = min_itr[z];

     if (landmarks_observed == false){
        mu((2*z)+3,0) =  thor_pose.position.x + actual_meas.range[k]*cos(actual_meas.bearing[k]);
        mu((2*z)+4,0) =  thor_pose.position.y + actual_meas.range[k]*sin(actual_meas.bearing[k]);
        if (z == (total_landmarks-1)){ landmarks_observed = true;}
      }

      Z(2*z,0) = actual_meas.range[k];
      Z((2*z)+1,0) = actual_meas.bearing[k];
      
      lambda_x = landmarks_pose.x[k] - thor_pose.position.x;
      lambda_y = landmarks_pose.y[k] - thor_pose.position.y;

      q = pow(lambda_x,2) + pow(lambda_y,2);

      line_theta(z,0) = normalizeangle(atan2(lambda_y,lambda_x));
      line_pho(z,0) = landmarks_pose.y[k]/sin(line_theta(z,0));

      // Transformation of Line from global co-ordinate into robot frame
      line_local(z,1) =  line_theta(z,0)- yaw;
      line_local(z,0) =  std::fabs(line_pho(z,0) - (thor_pose.position.x * cos(line_local(z,1))) - (thor_pose.position.y * sin(line_local(z,1))));

      expectedZ(2*z,0) = line_local(z,0);
      expectedZ((2*z)+1,0) = line_local(z,1);

     // std::cout << "z:" << z <<  "\n" << "Z(2*z,0):" << Z(2*z,0) <<  "\n"<< "expectedZ(2*z,0):" << expectedZ(2*z,0) <<  "\n" << std::endl;

      // Compute the Jacobian H of the measurement function h wrt the landmark location
       H((2*z),0) = sin(line_local(z,1));
       H((2*z)+1,0) = 0;
       H((2*z),1) = -cos(line_local(z,1));
       H((2*z)+1,1) = 0;
       H((2*z),2) = 0;
       H((2*z)+1,2) = -1; 

       H((2*z),(2*z)+3) = 1;
       H((2*z)+1,(2*z)+3) = 0;
       H((2*z),(2*z)+4) = thor_pose.position.x*sin(line_local(z,1))-thor_pose.position.y*cos(line_local(z,1));
       H((2*z)+1,(2*z)+4) = 1;       
      }	
		
      // Compute the Kalman gain
       K = cov*H.transpose()*(H*cov*H.transpose() + Q).inverse();

        // Compute the diference between the expected and recorded measurements.
       diff = Z - expectedZ;
       diff(1,0) = normalizeangle(diff(1,0));
       diff(3,0) = normalizeangle(diff(3,0));

	// Finish the correction step by computing the new mu and sigma.
       mu = mu + K*diff;
       mu(2,0)= normalizeangle(mu(2,0));

       cov = (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*cov ;
       // std::cout << "mu(3,0):" << "\t" << mu(3,0) << "\t" << " mu(4,0):" << "\t" <<  mu(4,0) << std::endl;
}      

int main(int argc, char** argv)
{
   ros::init(argc, argv, "floy3_line_SLAM");
   ros::NodeHandle n;
   ros::Rate r(10.0);

   // Subscribers
   ros::Subscriber landmarks_sub = n.subscribe("landmark_points", 100, landmarksposeCallback);
   ros::Subscriber odom_sub = n.subscribe("/thorvald_pose", 100, odometryCallback);
   ros::Subscriber odom_vel_sub = n.subscribe("/odometry/gazebo", 50, odometryvelCallback);
   ros::Subscriber point_sub = n.subscribe("measurement_points", 100, linepointsCallback);

   // Publishers
   ros::Publisher thorvald_pose_pub = n.advertise<nav_msgs::Odometry>("line_pose", 10);
   ros::Publisher marker_pub_1 = n.advertise<visualization_msgs::Marker>("landmark_marker_1", 10);
   ros::Publisher marker_pub_2 = n.advertise<visualization_msgs::Marker>("landmark_marker_2", 10);

   // Service Client
   // ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("sub_goal_check");

   cov.topLeftCorner(3,3) = robSigma;
   cov.topRightCorner(3, (2*total_landmarks)) = robMapSigma;
   cov.bottomLeftCorner((2*total_landmarks), 3) = robMapSigma.transpose();
   cov.bottomRightCorner((2*total_landmarks), (2*total_landmarks)) = mapSigma;

   current_time = ros::Time::now();
   last_time = ros::Time::now();
   int init_pose;

   // Markers
   visualization_msgs::Marker landmark_strip_1, landmark_strip_2;

   while (ros::ok()){

   ros::spinOnce();	

   if((landmarks_pose.landmark_check > 0)&&(counter_sub==1)&&(actual_meas.meas_update == true)){
   current_time = ros::Time::now();
   dt = (current_time - last_time).toSec();

   // initialzation position of the robot in the world frame
   if(init_pose==1){
   mu(0,0) = thor_pose.position.x;
   mu(1,0) = thor_pose.position.y;
   mu(2,0) = yaw;
   init_pose = 2;
   }

   // prediction step
   prediction_step(dt);

   // correction step
   correction_step(dt);

   // Robot pose estimation
   thorvald_estimated_pose.pose.pose.position.x = mu(0,0);
   thorvald_estimated_pose.pose.pose.position.y = mu(1,0);
   geometry_msgs::Quaternion q = tf::createQuaternionMsgFromYaw(mu(2,0));
   thorvald_estimated_pose.pose.pose.orientation = q;
   thorvald_estimated_pose.header.stamp = ros::Time::now();
   thorvald_estimated_pose.header.frame_id = "odom";
   thorvald_estimated_pose.child_frame_id = "base_link";

   landmark_strip_1.header.frame_id = "/map";
   landmark_strip_1.action = visualization_msgs::Marker::ADD;
   landmark_strip_1.pose.position.x = mu(3,0);
   landmark_strip_1.pose.position.y = mu(4,0);
   landmark_strip_1.pose.position.z = 0.75;
   landmark_strip_1.pose.orientation.w = 1.0;
   landmark_strip_1.type = visualization_msgs::Marker::CYLINDER;
   landmark_strip_1.lifetime = ros::Duration(0.1);
   landmark_strip_1.id = 1;
   landmark_strip_1.scale.x = 0.1;
   landmark_strip_1.scale.y = 0.1;
   landmark_strip_1.scale.z = 0.2;
   landmark_strip_1.color.g = 1.0;
   landmark_strip_1.color.a = 1.0;

   landmark_strip_2.header.frame_id = "/map";
   landmark_strip_2.action = visualization_msgs::Marker::ADD;
   landmark_strip_2.pose.position.x = mu(5,0);
   landmark_strip_2.pose.position.y = mu(6,0);
   landmark_strip_2.pose.position.z = 0.75;
   landmark_strip_2.pose.orientation.w = 1.0;
   landmark_strip_2.type = visualization_msgs::Marker::CYLINDER;
   landmark_strip_2.lifetime = ros::Duration(0.1);
   landmark_strip_2.id = 1;
   landmark_strip_2.scale.x = 0.1;
   landmark_strip_2.scale.y = 0.1;
   landmark_strip_2.scale.z = 0.2;
   landmark_strip_2.color.g = 1.0;
   landmark_strip_2.color.a = 1.0;

   landmark_strip_1.header.stamp = ros::Time::now();
   landmark_strip_2.header.stamp = ros::Time::now();

  thorvald_pose_pub.publish(thorvald_estimated_pose); 
  marker_pub_1.publish(landmark_strip_1);	
  marker_pub_2.publish(landmark_strip_2);
  last_time = current_time;
  } // spin check
  r.sleep();
  } 
  return 0;
}
