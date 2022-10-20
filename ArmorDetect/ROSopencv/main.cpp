#include<iostream>
using namespace std;
#include"Armor/ArmorDetect.hpp"
#include"Pose/AngleSolver.hpp"
#include"Camera/Camera.hpp"
#include<opencv2/opencv.hpp>

int main()
{
    Cam pp;
    cv::Mat pre_Frame;
        ArmorDetect dd;
        AngleSolver AS;
        string path = "../exchange.avi";
    	VideoCapture cap(path);
    while (1)
    {
        
        bool detect_flag = false;
        pp.getImage();
        dd.findArmorPoint(pp.InitImg,1);
        AS.solveAngles(dd.ARMOR_POINTS_3D,dd.armorImagePoints,dd.ArmorCenter);
        cv::waitKey(100);
        }






    return 0;
}
