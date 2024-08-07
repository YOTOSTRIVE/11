#include "ros/ros.h"

#include "robot_msgs/Move.h"

#include "string"

#include "libs/robot.h"

using namespace std;

const double PI = 3.1415926;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"move_joint_client");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_msgs::Move>("/robot_driver/move_joint");

    robot_msgs::Move srv;
    srv.request.pose.clear();
    srv.request.mvvelo = 0.1;
    srv.request.mvacc = 0.01;
//    srv.request.pose.push_back(18.909*PI/180);
//    srv.request.pose.push_back(100.932*PI/180);
//    srv.request.pose.push_back(65.263*PI/180);
//    srv.request.pose.push_back(114.719*PI/180);
//    srv.request.pose.push_back(-90.576*PI/180);
//    srv.request.pose.push_back(-31.437*PI/180);
    /* srv.request.pose.push_back(0*PI/180);
    srv.request.pose.push_back(20*PI/180);
    srv.request.pose.push_back(0*PI/180);
    srv.request.pose.push_back(0*PI/180);
    srv.request.pose.push_back(0*PI/180);
    srv.request.pose.push_back(0*PI/180); */
/*

positions[]
        positions[0]: 2.26716
        positions[1]: 1.49156
        positions[2]: 1.68951
        positions[3]: 0.459406
        positions[4]: -2.54302
        positions[5]: 1.45664

*/
    srv.request.pose.push_back(2.26716);
    srv.request.pose.push_back(1.49156);
    srv.request.pose.push_back(1.68951);
    srv.request.pose.push_back(0.45946);
    srv.request.pose.push_back(-2.54302);
    srv.request.pose.push_back(1.45664);


    //cout<<"ssssssssssssss"<<endl;

    if(client.call(srv))
    {
        ROS_INFO("Response from server message: %s",srv.response.message.c_str());
        ROS_INFO("Response from server ret: %d",srv.response.ret);
    }else{
        ROS_ERROR("failed to call /robot_driver/move_line");
        return 1;
    }

    return 0;

}
