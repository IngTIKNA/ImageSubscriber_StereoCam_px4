#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#include "ros/ros.h"
#include "stereo_msgs/DisparityImage.h"
#include "std_msgs/UInt32.h"




using namespace std;

void disparityCallback(const stereo_msgs::DisparityImage::ConstPtr& msg){
	double x = msg->image.width;                                                                 //msg->image->data
    double y = msg->image.height;                                                                //msg->image->data
    vector<uint8_t> img;
    img = msg->image.data;

    cv::Mat disMap = cv::Mat(800, 800, CV_8UC1, img.data()).clone();

    ROS_INFO("x: %f,  y:  %f", x, y);
    cout << "Image size : " << sizeof(img[2]) / sizeof(unsigned char) << endl;
    //cout << "disparityCallback is called!" << endl;


    cv::imshow("Disparity Map", disMap);
    cv::waitKey(300);
    cv::destroyWindow("Disparity Map");
}

/*
void pointcloud_sizeCallback(const std_msgs::UInt32::ConstPtr& msg){
    double x = msg->data;                                                                 //msg->image->data

    //ROS_DEBUG("x: %f,  y:  %f", x, y);
    ROS_INFO("Pointcloud size: %f", x);
    //ROS_WARN("x: %f,  y:  %f", x, y);

    cout << "disparityCallback is called!" << endl;
}
*/

int main(int argc, char **argv){

        cout << "1 _ Disparity mapper is working" << endl;
        //_______________________________________________________________________________________//
        ros::init(argc, argv,"disparity_mapper");                                                //
        cout << "2 _ ROS is initialized " << endl;
        ros::NodeHandle n1, n2;                                                                       // create a RosNode object
        cout << "3 _ ROS_Node is created " << endl;
        ros::Subscriber sub1 = n1.subscribe("/stereo/disparity", 10, disparityCallback);              // topic name, queue size, callback fcn
        cout << "4 _ Subscriber is created " << endl;
        ros::spin();                                                                             //
        cout << "5 _ ROS spin" << endl;
        //_______________________________________________________________________________________//

	return 0;        
}
