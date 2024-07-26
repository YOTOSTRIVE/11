#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include "ros/ros.h"
#include "robot_msgs/Move.h"
#include "string"
#include "libs/robot.h"
# include <std_msgs/Float32MultiArray.h>

class SubAndPub{
    public:
        SubAndPub(){
            client_ = n_.serviceClient<robot_msgs::Move>("/robot_driver/move_joint");
            sub_ = n_.subscribe<std_msgs::Float32MultiArray>("/trajectory/points", 10, &SubAndPub::trajectoryCallback,this);
        }

        void trajectoryCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
            {

                robot_msgs::Move srv;

            // 获取提取的数据

                int num_joints = 6; 

                for (size_t i = msg->data.size()-6; i < msg->data.size(); i += 2*num_joints)
                {

                srv.request.pose.clear();
                srv.request.mvvelo = 0.1;
                srv.request.mvacc = 0.01;
                    for (int j = 0; j < num_joints; j++)
                    {
                        
                        srv.request.pose.push_back(msg->data[i + j]);
                        
                    }
                    for (size_t k = 0; k < 6; k++)
                    {
                            ROS_INFO("Element %zu: %f", k, srv.request.pose[k]);
                    }
                    if(client_.call(srv)){
                        ROS_INFO("11");
                        ROS_INFO("Response from server message: %s",srv.response.message.c_str());
                        ROS_INFO("Response from server ret: %d",srv.response.ret);

                    }else{
                        break;
                    }
                }

            }
    private:
        ros::NodeHandle n_;
        ros::ServiceClient client_;
        ros::Subscriber sub_;

};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "trajectory_subscriber_node");
    SubAndPub subandpub;

    ros::spin(); // 循环等待接收消息

    return 0;
}
