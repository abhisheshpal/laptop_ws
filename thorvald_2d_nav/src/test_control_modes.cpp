#include "test_control_modes.h"

// Thorvald Estimated Pose data
void robotposeCallback (const geometry_msgs::Pose::ConstPtr& pose_msg)
{
thor_est.pose.position = pose_msg->position;
thor_est.pose.orientation = pose_msg->orientation;

tf::Quaternion quat(thor_est.pose.orientation.x,thor_est.pose.orientation.y, thor_est.pose.orientation.z, thor_est.pose.orientation.w);
quat = quat.normalize();
yaw = tf::getYaw(quat);

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

counter_line = 1;
}

bool row_transition(thorvald_2d_nav::sub_goal::Request &req, thorvald_2d_nav::sub_goal::Response &res)
   {
     row_no = row_no + req.counter;
     next_row_check = true; 
     ROS_INFO("Navigate in New Row"); 
     return true;
   }

double control_law(double v, double _dt, geometry_msgs::PoseStamped hokuyo_pose){

   slope_1 = (landmarks_pose.y[1]-landmarks_pose.y[5])/(landmarks_pose.x[1]-landmarks_pose.x[5]); 
   slope_2 = (landmarks_pose.y[3]-landmarks_pose.y[5])/(landmarks_pose.x[3]-landmarks_pose.x[5]);

   dist_d[0] = landmarks_pose.y[1]-landmarks_pose.y[5]/sqrt(pow(slope_1,2)+1);
   dist_d[1] = landmarks_pose.y[3]-landmarks_pose.y[5]/sqrt(pow(slope_2,2)+1);

  // calculation of error
  q_x =  mini_goal_pts.x-hokuyo_pose.pose.position.x;
  q_y =  mini_goal_pts.y-hokuyo_pose.pose.position.y;
  position_error = sqrt(pow(q_x,2) + pow(q_y,2));
  angular_error = atan2(q_y,q_x)- yaw;
 
  if (angular_error > M_PI){
  angular_error -= 2*M_PI;}
  if (angular_error < -M_PI){
  angular_error += 2*M_PI;}

  // control law
  // double robotlength = 0.75;
  // double omega = atan(2*robotlength*sin(angular_error))/position_error;
  // double omega = v * pow(cos(angular_error),3) * (-(K_d*tan(angular_error)) - (K_p*position_error));

  dist_pt_1 = ((landmarks_pose.y[1]-landmarks_pose.y[0])*hokuyo_pose.pose.position.x)-((landmarks_pose.x[1]-landmarks_pose.x[0])*hokuyo_pose.pose.position.y)+(landmarks_pose.x[1]*landmarks_pose.y[0])-(landmarks_pose.y[1]*landmarks_pose.x[0]);
  dist_pt_2 = pow(landmarks_pose.y[1]-landmarks_pose.y[0],2) + pow(landmarks_pose.x[1]-landmarks_pose.x[0],2);
  dist_pt_f = abs(dist_pt_1)/sqrt(dist_pt_2);

  dist_pt_3 = ((landmarks_pose.y[3]-landmarks_pose.y[2])*hokuyo_pose.pose.position.x)-((landmarks_pose.x[3]-landmarks_pose.x[2])*hokuyo_pose.pose.position.y)+(landmarks_pose.x[3]*landmarks_pose.y[2])-(landmarks_pose.y[3]*landmarks_pose.x[2]);
  dist_pt_4 = sqrt(pow(landmarks_pose.y[3]-landmarks_pose.y[2],2) + pow(landmarks_pose.x[3]-landmarks_pose.x[2],2));
  dist_pt_f1 = abs(dist_pt_3)/dist_pt_4;

  /* asq = sqrt(pow(landmarks_pose.x[1]-hokuyo_pose.pose.position.x,2) + pow(landmarks_pose.y[1]-hokuyo_pose.pose.position.y,2)); 
   bsq = sqrt(pow(landmarks_pose.x[0]-hokuyo_pose.pose.position.x,2) + pow(landmarks_pose.y[0]-hokuyo_pose.pose.position.y,2));
   csq = sqrt(pow(landmarks_pose.x[0]-landmarks_pose.x[1],2) + pow(landmarks_pose.y[0]-landmarks_pose.y[1],2));

   ang_err = acos((asq + bsq - csq)/2*sqrt(asq*bsq));*/

   omega_exp = K_d * (dist_d[0]-dist_pt_f) * _dt +  K_d * (dist_d[1]-dist_pt_f1)*_dt;

  //  std::cout << "ang_err:" << ang_err << "\n" << std::endl;
 
   _integral += angular_error * _dt;
  omega = K_p * angular_error *_dt + K_d *(angular_error - lastError)* _dt;
  lastError = angular_error;
  // std::cout << "angular_error:" << _dt << "\n" << "omega:" << omega << "\n" << std::endl;
  if (omega > M_PI){
  omega -= 2*M_PI;}
  if(omega < -M_PI){
  omega += 2*M_PI;}
  
   if((fabs(position_error) <= 0.2) && (c<=Total_Points)){
   // ROS_INFO("New Mini-Goal Initiated");
   mini_goal_pts.x = Points[c].position.x;
   mini_goal_pts.y = Points[c].position.y;
   c = c + 1;
   mini_goal = true;
  }

  return omega_exp;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_control_modes");
  ros::NodeHandle n;

  // Subscribers
  ros::Subscriber landmarks_sub = n.subscribe("landmark_points", 100, landmarksposeCallback);
  ros::Subscriber pose_sub = n.subscribe("thorvald_pose", 100, robotposeCallback);

  // Publishers
  ros::Publisher twist_gazebo = n.advertise<geometry_msgs::Twist>( "/nav_vel", 100);

  // Service Servers
  ros::ServiceServer service2 = n.advertiseService("/row_transition_end_2", row_transition);

  // Service Client
  ros::ServiceClient client = n.serviceClient<thorvald_2d_nav::sub_goal>("/sub_goal_check");

  ros::Rate r(1.0);
  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();
  double linear_velocity = 0.2, angular_velocity = 0;
  tf::StampedTransform transform;
  tf::TransformListener listener;
  tf2_ros::TransformListener tfListener(tfBuffer);
  double dt;

  while (ros::ok()){

  ros::spinOnce();

  if((counter_line > 0) && (landmarks_pose.landmark_check > 0)){ // generated line check

  current_time = ros::Time::now();	
  dt = (current_time - last_time).toSec();

  if((landmarks_pose.landmark_check > line_count) || ((next_row_check == true)&&(landmarks_pose.row_number > row_count))){
   line_count = landmarks_pose.landmark_check;
   row_count = landmarks_pose.row_number;
    for(int i=1;i<=Total_Points;i++){
    Points[i].position.x = ((thor_est.pose.position.x) *(1-(float(i)/Total_Points))) + ((landmarks_pose.x[5]) *(float(i)/Total_Points));

    if(landmarks_pose.y[5]>0.0){
     if(landmarks_pose.y[5]>1.0){
     Points[i].position.y = (thor_est.pose.position.y *(1-(float(i)/Total_Points))) + ((landmarks_pose.y[5]-1.0) *(float(i)/Total_Points)); 
     }
     else{ 
     Points[i].position.y = (thor_est.pose.position.y *(1-(float(i)/Total_Points))) + ((1.0-landmarks_pose.y[5]) *(float(i)/Total_Points)); 
     }
    }
    else{ 
    Points[i].position.y = (thor_est.pose.position.y *(1-(float(i)/Total_Points))) + ((landmarks_pose.y[5]+1.0) *(float(i)/Total_Points)); 
    } 
  }
  std::cout << "Points[Total_Points].y:" << Points[Total_Points].position.y << "\n" << std::endl;
  mini_goal_pts.x = Points[1].position.x;
  mini_goal_pts.y = Points[1].position.y;
  mini_goal = true;
  ROS_INFO("Assigned new Sub-goal");
  next_row_check = false;
  }

   if(mini_goal==true){ // final min-goal check

       try{
       transformStamped = tfBuffer.lookupTransform("base_link", "hokuyo", ros::Time(0));
       }
       catch (tf2::TransformException &ex){
       ROS_WARN("%s",ex.what());
       ros::Duration(1.0).sleep();
       }

       tf2::doTransform(thor_est, thor_est_trans, transformStamped);
       thor_est_trans.header.frame_id = "/hokuyo";  
 
   angular_velocity = control_law(linear_velocity, dt, thor_est_trans); // control law

   if(fabs(Points[Total_Points].position.y - thor_est_trans.pose.position.y) <= 0.5){
   counter_1 = 1;
   mini_goal = false;
   est_twist.linear.x = 0;
   est_twist.angular.z = 0;
   ROS_INFO("Final Mini-Goal Reached");
   }
   else{
   est_twist.linear.x = 0.3;
   est_twist.angular.z = angular_velocity;
    } 

   twist_gazebo.publish(est_twist);
   } // final min-goal check

   if(counter_1 == 1){
   goal_count.request.counter = 1;
   if (client.call(goal_count)){
   counter_1 = 2;
   }}
  } // generated line check

   last_time = current_time;
 }
  return 0;
}
