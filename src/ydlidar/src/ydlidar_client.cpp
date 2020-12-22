/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client 
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 * 
 */

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include <iostream>
#include <string>

#define RAD2DEG(x) ((x)*180./M_PI)

ros::Publisher *pub;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    std_msgs::String str;
    int count = scan->scan_time / scan->time_increment;
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    //printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
  
    for(int i = 0; i < count; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
/*
	if(degree > -5 && degree< 5)
        printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
    
*/

        if(scan->ranges[i] < 0.2)
        str.data = "degree= "+ std::to_string(degree) +" "+"Distance= " + std::to_string(scan->ranges[i]);
        pub->publish(str);
        //printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    pub = new ros::Publisher(n.advertise<std_msgs::String>("/distance",1000));
    ros::spin();

    return 0;
}
