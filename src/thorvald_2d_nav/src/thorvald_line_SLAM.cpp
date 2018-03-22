#include "thorvald_line_SLAM.h"
   
// robot velocity data
void odometryvelCallback (const geometry_msgs::Twist::ConstPtr& odometry_vel){
odom_vel.linear = odometry_vel->linear;
}

// robot pose data
void odometryCallback (const nav_msgs::Odometry::ConstPtr& odometry){

robot_pose.pose.pose = odometry->pose.pose;
robot_pose.twist.twist = odometry->twist.twist;

tf::Quaternion quat(robot_pose.pose.pose.orientation.x,robot_pose.pose.pose.orientation.y, robot_pose.pose.pose.orientation.z, robot_pose.pose.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

}

//line point data
void linepointsCallback(const thorvald_2d_nav::scan_detected_line::ConstPtr& line_points){

if (line_points->range.size() > 0){
for (int num = 0; num < total_landmarks; num++){
measured_points_range[num] = line_points->range[num];
measured_points_bearing[num] = line_points->bearing[num];
}}

}

//line points 
void landmarksposeCallback (const thorvald_2d_nav::landmarks::ConstPtr& landmarks_msg)
{

if (landmarks_msg->landmark_check > 0){        
landmarks_pose.pt_1.x = landmarks_msg->pt_1.x;
landmarks_pose.pt_1.y = landmarks_msg->pt_1.y;
landmarks_pose.pt_2.x = landmarks_msg->pt_2.x;
landmarks_pose.pt_2.y = landmarks_msg->pt_2.y;
landmarks_pose.pt_3.x = landmarks_msg->pt_3.x;
landmarks_pose.pt_3.y = landmarks_msg->pt_3.y;
landmarks_pose.pt_4.x = landmarks_msg->pt_4.x;
landmarks_pose.pt_4.y = landmarks_msg->pt_4.y;
landmarks_pose.pt_5.x = landmarks_msg->pt_5.x;
landmarks_pose.pt_5.y = landmarks_msg->pt_5.y;
landmarks_pose.pt_6.x = landmarks_msg->pt_6.x;
landmarks_pose.pt_6.y = landmarks_msg->pt_6.y;
landmarks_pose.landmark_check = landmarks_msg->landmark_check;

// calculation of estimated range and bearing
line_pho(0,0) = sqrt(pow(landmarks_pose.pt_1.x,2) + pow(landmarks_pose.pt_1.y,2));
line_theta(0,0) = atan2(landmarks_pose.pt_1.y,landmarks_pose.pt_1.x);
line_pho(1,0) = sqrt(pow(landmarks_pose.pt_2.x,2) + pow(landmarks_pose.pt_2.y,2));
line_theta(1,0) = atan2(landmarks_pose.pt_2.y,landmarks_pose.pt_2.x);

line_pho(2,0) = sqrt(pow(landmarks_pose.pt_3.x,2) + pow(landmarks_pose.pt_3.y,2));
line_theta(2,0) = atan2(landmarks_pose.pt_3.y,landmarks_pose.pt_3.x);
line_pho(3,0) = sqrt(pow(landmarks_pose.pt_4.x,2) + pow(landmarks_pose.pt_4.y,2));
line_theta(3,0) = atan2(landmarks_pose.pt_4.y,landmarks_pose.pt_4.x);
}

}

double normalizeangle(double bearing){
if (bearing > M_PI){
bearing = M_PI;}
if(bearing < -M_PI){
bearing = -M_PI;}
}

//prediction step
void prediction_step(MatrixXd& mu1,MatrixXd& cov1,MatrixXd& line_local1,MatrixXd& line_local_fixed1,double dt){

  vx = (odom_vel.linear.x + odom_vel.linear.y)/2;
  vy = 0.0;
  vth = (odom_vel.linear.y - odom_vel.linear.x)/d;

  // Odometry Compensation 
  double delta_x = (vx * cos(mu1(2,0)) - vy * sin(mu1(2,0))) * dt;
  double delta_y = (vx * sin(mu1(2,0)) + vy * cos(mu1(2,0))) * dt;
  double delta_th = vth * dt;

  mu1(0,0) = mu1(0,0) + delta_x;
  mu1(1,0) = mu1(1,0) + delta_y;
  mu1(2,0) = mu1(2,0) + delta_th;
  mu1(2,0)= normalizeangle(mu1(2,0));

  MatrixXd Gt = MatrixXd(3,3);
  Gt << 1, 0, -vx * sin(mu1(2,0)) - vy * cos(mu1(2,0)),
        0, 1,  vx * cos(mu1(2,0)) - vy * sin(mu1(2,0)),
        0, 0,  0;

  R.topLeftCorner(3,3) << motion_noise, 0, 0,
                          0, motion_noise , 0,
                          0, 0,   motion_noise/10;

  cov1.topLeftCorner(3,3) = Gt * cov1.topLeftCorner(3,3) * Gt.transpose();
  cov1.topRightCorner(3, 2*total_landmarks) = Gt * cov1.topRightCorner(3, 2*total_landmarks);
  cov1.bottomLeftCorner(2*total_landmarks, 3) = cov1.topRightCorner(3, 2*total_landmarks).transpose();

  cov1 = cov1 + R; // Motion Noise

   // std::cout << "mu1" << "\t" << mu1(0,0) << "\t" << "mu1" << "\t" << mu1(1,0) << "\t" << "mu1" << "\t" << mu1(2,0) << std::endl;
   // std::cout << "cov_x" << "\t" << cov1(1,0) << "\t" << "cov_y" << "\t" << cov1(0,1) << std::endl;

}

//correction step
void correction_step(MatrixXd mu_2, MatrixXd cov_2, MatrixXd line_local_2, MatrixXd line_local_fixed_2, double dt){
           
      // Landmarks observation
     for (int z = 0; z < total_landmarks; z++){

        // Transformation of Line from global co-ordinate into robot frame
      if (landmarks_observed == false){
        line_local_2(z,0) =  line_pho(z,0) - (robot_pose.pose.pose.position.x * cos(line_theta(z,0))) - (robot_pose.pose.pose.position.y * sin(line_theta(z,0)));
        line_local_2(z,1) =  line_theta(z,0) - yaw + (3.14/2);
        if (z == total_landmarks){ landmarks_observed = true;}
      }

      Z(2*z,0) = measured_points_range[z];
      Z((2*z)+1,0) = measured_points_bearing[z];

      lambda_x = line_local_2(z,0) - robot_pose.pose.pose.position.x;
      lambda_y = line_local_2(z,1) - robot_pose.pose.pose.position.y;
      q = pow(lambda_x,2) + pow(lambda_y,2);

      double expectedRange = sqrt(q);
      double expectedBearing = normalizeangle((lambda_y/lambda_x) - yaw);
      expectedZ(2*z,0) = expectedRange;
      expectedZ((2*z)+1,0) = expectedBearing;

   //std::cout << "line_pho(2,0)" << "\t" << line_pho(2,0) << "\t" << "line_pho(3,0)" << "\t" << line_pho(3,0) << "\t" << "line_theta(2,0)" << "\t" << line_theta(2,0) << std::endl;
   // std::cout << "expectedRange" << "\t" << line_pho(z,0) << "\t" << "Z" << "\t" <<  Z(2*z,0) << std::endl;

      // Compute the Jacobian H of the measurement function h wrt the landmark location
       H((2*z),0) = 1/q * (-sqrt(q)*lambda_x);
       H((2*z)+1,0) = 1/q * lambda_y;
       H((2*z),1) = 1/q * (-sqrt(q)*lambda_y);
       H((2*z)+1,1) = 1/q * (-lambda_y);
       H((2*z),2) = 0;
       H((2*z)+1,2) = -q;

       H((2*z),2*z+3) = 1/q * (sqrt(q)*lambda_x);
       H((2*z)+1,2*z+3) = 1/q * (-lambda_y);
       H((2*z),2*z+4) = 1/q * (sqrt(q)*lambda_y);
       H((2*z)+1,2*z+4) = 1/q * (lambda_x);       
      }	
		
      // Compute the Kalman gain
       K = cov_2*H.transpose()*(H*cov_2*H.transpose() + Q).inverse();

        // Compute the diference between the expected and recorded measurements.
       diff = Z - expectedZ;
        // diff = normalize_all_bearings(diff);

	// Finish the correction step by computing the new mu and sigma.
       mu_2 = mu_2 + K*diff;
       cov_2 =  (MatrixXd::Identity((2*total_landmarks+3),(2*total_landmarks+3))- K*H)*cov_2 ;
       mu_2(2,0)= normalizeangle(mu_2(2,0));
}


int main(int argc, char** argv)
{
   ros::init(argc, argv, "thorvald_line_SLAM");
   ros::NodeHandle n;
   ros::Rate r(10.0);

   // Subscribers
   ros::Subscriber landmarks_sub = n.subscribe("landmark_points", 100, landmarksposeCallback);
   ros::Subscriber odom_sub = n.subscribe("/thorvald_ii/odom", 100, odometryCallback);
   ros::Subscriber odom_vel_sub = n.subscribe("/odom_topic", 50, odometryvelCallback);
   ros::Subscriber point_sub = n.subscribe("measurement_points", 100, linepointsCallback);

   // Publishers
   ros::Publisher thorvald_pose_pub = n.advertise<geometry_msgs::Pose>("thorvald_pose", 10);

   // Service Client
   ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("sub_goal_check");

   cov.topLeftCorner(3,3) = robSigma;
   cov.topRightCorner(3, (2*total_landmarks)) = robMapSigma;
   cov.bottomLeftCorner((2*total_landmarks), 3) = robMapSigma.transpose();
   cov.bottomRightCorner((2*total_landmarks), (2*total_landmarks)) = mapSigma;

   current_time = ros::Time::now();
   last_time = ros::Time::now();

   while (ros::ok()){

   ros::spinOnce();	

   current_time = ros::Time::now();
   double dt = (current_time - last_time).toSec();

   // prediction step
   prediction_step(mu, cov, line_local, line_local_fixed, dt);
 
   // correction step
   correction_step(mu, cov, line_local, line_local_fixed, dt);

   // Robot pose estimation
   thorvald_estimated_pose.position.x = mu(0,0);
   thorvald_estimated_pose.position.y = mu(1,0);
   geometry_msgs::Quaternion q = tf::createQuaternionMsgFromYaw(mu(2,0));
   thorvald_estimated_pose.orientation = q;

   // sub-goal check
   double goal = landmarks_pose.pt_6.x;
   if ((thorvald_estimated_pose.position.x - goal) < sub_goal_thershold){  //sub-goal thershold
   goal_count.request.counter = 1;
   ROS_INFO("client request");
   }

  thorvald_pose_pub.publish(thorvald_estimated_pose); 
  last_time = current_time;
  r.sleep();
  } 
  return 0;
}
