#include<iostream>
using namespace std;
#include"Armor/ArmorDetect.hpp"
#include"Pose/AngleSolver.hpp"
#include"Camera/Camera.hpp"
#include<opencv2/opencv.hpp>
#include<visualization_msgs/Marker.h>
#include<geometry_msgs/PoseStamped.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_opencv");
    ros::NodeHandle n;
    //创建发布者，发布RVIZ图形
    ros::Publisher point_pub_ = n.advertise<visualization_msgs::Marker>("pnp_data",1);
    while (1)
    {
        //if(button)break;
        Cam pp;
        cv::Mat pre_Frame;
        ArmorDetect dd(n);
        AngleSolver AS;
        bool detect_flag = false;
        pp.getImage();
        dd.findArmorPoint(pp.InitImg,1);
        Point3d pnp = AS.solveAngles(dd.ARMOR_POINTS_3D,dd.armorImagePoints,dd.ArmorCenter);

        //创建长方体
        visualization_msgs::Marker marker;
        marker.scale.x = 0.1;
        marker.scale.y = 0.5;
        marker.scale.z = 0.3;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        marker.header.frame_id = "cam_link";
        marker.header.stamp = ros::Time::now();
        marker.ns = "pnp_box";
        marker.type = visualization_msgs::Marker::CUBE;
        marker.action = visualization_msgs::Marker::MODIFY;
        marker.pose.position.x = -pnp.z/100;
        marker.pose.position.y = pnp.x/100;
        marker.pose.position.z = pnp.y/100;
        marker.pose.orientation.x = AS.x;
        marker.pose.orientation.y = AS.y;
        marker.pose.orientation.z = -AS.z;
        marker.pose.orientation.w = AS.w;
        //发布图形话题
        point_pub_.publish(marker);
        cv::waitKey(100);
        }






    return 0;
}
