//#include <iostream>
#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "tf2_msgs/TFMessage.h"
#include <sstream>
#include "std_msgs/String.h"
#include <iostream>
#include <string>
using namespace std;

ros::Publisher *pub;

void tfCallback(const tf2_msgs::TFMessage::ConstPtr& msg)
{
	//string str;am itr(msg->transforms[0].child_frame_id.c_str());
	//itr >> str;
	if(msg->transforms[0].child_frame_id == "scanmatcher_frame")
{

        std_msgs::String position;
	position.data = "x:" + std::to_string(msg->transforms[0].transform.translation.x) + " " + " y:" + std::to_string(msg->transforms[0].transform.translation.y);
	pub->publish(position);

        //ROS_INFO("current Postion :  x : [%f] y : [%f] ",msg->transforms[0].transform.translation.x , msg->transforms[0].transform.translation.y);
}
}
	//istringstre
int main(int argc, char **argv)
{
    //cout << "Hello world!" << endl;
    ros::init(argc, argv, "tf_subscriber_node");
    ros::NodeHandle ntf;
    ros::Subscriber sub = ntf.subscribe("/tf",1000, tfCallback);
    pub = new ros::Publisher(ntf.advertise<std_msgs::String>("/position",1000));
    ros::spin ();
    return 0;
}
