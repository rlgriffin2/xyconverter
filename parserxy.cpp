#include "ros/ros.h"
#include <stdio.h>
#include <vector>
#include "std_msgs/String.h"
#include "xyconverter/Cartesian.h"
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>	//f<^or the splitting of coordinates
using namespace std;

xyconverter::Cartesian parsedxy;

vector<float> parsedCoords;
string rawData;
vector<string> rawCoords;
ros::Publisher parserxy_pub;

void parseFunc(const std_msgs::String::ConstPtr& msg){
	rawData = msg->data;


	boost::split(rawCoords, rawData, boost::is_any_of(","));

int j = 0;
	for(string s : rawCoords){
		for(int i = 0; i<s.length(); i++){
			if(s[i]=='(' || s[i] == ')' || s[i] == ','|| s[i] == ' '){
					s.erase(s.begin() + i);
			}
		}
		parsedCoords.push_back(stof(s));

		}

	vector<float> parsedVector(sizeof(parsedCoords));
	for(int i = 0; i<sizeof(parsedCoords); i++){
		parsedVector[i] = parsedCoords[i];
	}
	parsedxy.x = parsedCoords[0];
	parsedxy.y = parsedCoords[1];
	parsedxy.z = parsedCoords[2];
	parserxy_pub.publish(parsedxy);
	ROS_INFO("X: %f, Y: %f, Z: %f", parsedxy.x, parsedxy.y, parsedxy.z);
	parsedCoords.clear();

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "parser_node");
	ros::NodeHandle n;
	parserxy_pub = n.advertise<xyconverter::Cartesian>("parsed_coords", 1000);
	ros::Subscriber parserxy_sub = n.subscribe<std_msgs::String>("raw_coords", 1000, parseFunc);
	ros::Rate loop_rate(5);
	ros::spin();
}
