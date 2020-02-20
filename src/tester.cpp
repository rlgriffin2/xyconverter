#include "ros/ros.h"
#include "std_msgs/String.h"
using namespace std;
int main(int argc, char **argv){
	ros::init(argc, argv, "tester_node");
	ros::NodeHandle n;
	ros::Publisher tester_pub = n.advertise<std_msgs::String>("test_topic", 1000);
	ros::Rate loop_rate(10);
  std_msgs::String msg;
  msg.data = "Teslas are the best car!";
  while(ros::ok()){
  tester_pub.publish(msg);
  ROS_INFO("Message sent: %s", msg.data.c_str());
  loop_rate.sleep();
  ros::spinOnce();
}}
