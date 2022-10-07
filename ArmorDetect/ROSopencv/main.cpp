#include<iostream>
using namespace std;
#include"Armor/ArmorDetect.hpp"
#include"Pose/AngleSolver.hpp"
#include"Camera/Camera.hpp"
#include<opencv2/opencv.hpp>

int main()
{
    while (1)
    {
        //if(button)break;
        Cam pp;
        cv::Mat pre_Frame;
        ArmorDetect dd;
        AngleSolver AS;
        bool detect_flag = false;
        pp.getImage();
        dd.findArmorPoint(pp.InitImg,1);
        AS.solveAngles(dd.ARMOR_POINTS_3D,dd.armorImagePoints,dd.ArmorCenter);
        //Point3d newPNP(KF.getPredict(AS.PNP.x,1),KF.getPredict(AS.PNP.y,2),KF.getPredict(AS.PNP.z,3));
        //cout<<"KF:"<<KF.getPredict(AS.PNP.x,1)<<KF.getPredict(AS.PNP.y,2)<<KF.getPredict(AS.PNP.z,3)<<endl;
        //std::cout<<"AS.newPNP:"<<AS.newPNP[0]<<endl;
        //AS.getAngle(AS.PNP);
            
        //circle(curr_Frame, center, 10, Scalar(255, 255, 0), 4);
        //serial code is expected to be updated


        //putText(oriimg,std::to_string(x_speed),Point(center.x+50,center.y+50),cv::FONT_HERSHEY_PLAIN,2,(255,0,0),2);
        //dd.ArmorCenter.clear();
        //pre_Frame = curr_Frame;
        cv::waitKey(100);
        }






    return 0;
}