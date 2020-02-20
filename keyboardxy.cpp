#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream> //for cin/cout
using namespace std;
//Scan the console for the users input of (x, y) and then publish that data onto topic raw_coords
int main(int argc, char **argv){
	ros::init(argc, argv, "keyboard_node");
	ros::NodeHandle n;
	ros::Publisher keyboardxy_pub = n.advertise<std_msgs::String>("raw_coords", 1000);
	ros::Rate loop_rate(10);

	while(ros::ok()){
		string rawcoordinates;
		cout << "Please enter coordinates in the form of: x,y,z";
		getline(cin, rawcoordinates);
		std_msgs::String msg;
		msg.data = rawcoordinates;
		keyboardxy_pub.publish(msg);
		ros::spinOnce();
	}

}
