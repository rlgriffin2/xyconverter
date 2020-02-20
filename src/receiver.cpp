#include "ros/ros.h"
#include "std_msgs/String.h"
using namespace std;

void callbackFunc(const std_msgs::String::ConstPtr& msg){
  ROS_INFO("Message received: [%s]", msg->data.c_str());
}

int main(int argc, char **argv){
	ros::init(argc, argv, "receiver_node");
	ros::NodeHandle n;
  ros::Subscriber tester_sub = n.subscribe("test_topic", 1000, callbackFunc);
  ros::spin();
  return 0;
}
