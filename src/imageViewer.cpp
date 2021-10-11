//____________________________________//
#include <iostream>                   //
#include <vector>                     //
#include <opencv2/opencv.hpp>         //
#include <unistd.h>                   //
//____________________________________//
#include "ros/ros.h"                  //
#include "sensor_msgs/Image.h"        //
#include "std_msgs/UInt32.h"          //
//____________________________________//


using namespace std;
using namespace cv;

void imageViewer_leftCam_Callback(const sensor_msgs::Image::ConstPtr& msg){
    //__________________________________________________________//
    vector<uint8_t> img;                                        //
    img = msg->data;                                            // Read raw image data
    //__________________________________________________________//
    Mat leftImg = Mat(400, 400, CV_8UC3, img.data()).clone();	// Fill the Mat object    * Image size (400,400,3)
    cvtColor(leftImg, leftImg, CV_RGB2BGR);
    //__________________________________________________________//
    imshow("Left Camera", leftImg);								// Display image
    waitKey(500);                                               // refresh the image in every 500 milliseconds
    destroyWindow("Left Camera");								//
    //__________________________________________________________//
}


void imageViewer_rightCam_Callback(const sensor_msgs::Image::ConstPtr& msg){
    //__________________________________________________________//
    vector<uint8_t> img;                                        //
    img = msg->data;                                            // Read raw image data
    //__________________________________________________________//
    Mat right_BGR = Mat(400, 400, CV_8UC3, img.data()).clone();	// Fill the Mat object    * Image size (400,400,3)
    cvtColor(right_BGR, right_BGR, CV_RGB2BGR);
    //__________________________________________________________//
    imshow("Right Camera", right_BGR);            	            // Display image
    waitKey(500);                                               // refresh the image in every 500 milliseconds
    destroyWindow("Right Camera");	                            //
    //__________________________________________________________//
}


int main(int argc, char **argv){
	//__________________________________________________________________________________________________________//
	cout << "1 _ RGB-8-bit Image viewer is working" << endl;                                        			//
	//__________________________________________________________________________________________________________//
	ros::init(argc, argv,"image_viewer");                                                   					//
	cout << "2 _ ROS is initialized " << endl;																	//
	ros::NodeHandle n1, n2;                                                                  					// create a RosNode object
	cout << "3 _ ROS_Nodes are created " << endl;																	//
	ros::Subscriber sub1 = n1.subscribe("/stereo/left/image_rect_color", 10, imageViewer_leftCam_Callback);		// topic name, queue size, callback fcn
	ros::Subscriber sub2 = n2.subscribe("/stereo/right/image_rect_color", 10, imageViewer_rightCam_Callback);	// topic name, queue size, callback fcn
	cout << "4 _ Subscribers are created " << endl;																//
	ros::spin();                                                                             					//
	cout << "5 _ ROS spin" << endl;																				//
	//__________________________________________________________________________________________________________//

	return 0;        
}
