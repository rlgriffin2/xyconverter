#include "ros/ros.h"
#include <cmath>
#include "xyconverter/Cartesian.h"
#include "xyconverter/Polar.h"
using namespace std;
using xyconverter::Polar;
using xyconverter::Cartesian;

ros::Publisher rphiconverted;
Polar polarCoordinates;
float* convertCoords(float x, float y, float z){
	static float convertedCoords[2];
	float r;
	float phi;
	r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	//theta = acos(z/(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))));
	phi = atan((sqrt(pow(x, 2) + pow(y, 2))/z));
	convertedCoords[0] = r;
	convertedCoords[1] = phi;
	return convertedCoords;
}

void subCallback(const Cartesian::ConstPtr& coords){
	float *ptr = convertCoords(coords->x, coords->y, coords->z);
	float polarCoords[2];
	polarCoords[0] = *ptr;
	polarCoords[1] = *++ptr;
	//polarCoords[1] = ++ptr;
	polarCoordinates.distance = polarCoords[0];
	polarCoordinates.angle = polarCoords[1];
		rphiconverted.publish(polarCoordinates);
		ROS_INFO("Distance: %f  Angle: %f", polarCoordinates.distance, polarCoordinates.angle);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "converter_node");

  ros::NodeHandle n;
	rphiconverted = n.advertise<Polar>("converted_coords", 1000);

  ros::Subscriber xyzconverter = n.subscribe<Cartesian>("parsed_coords" ,1000, subCallback);
	ros::Rate loop_rate(10);


		ros::spin();


}
