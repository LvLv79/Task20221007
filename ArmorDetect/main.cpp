#include <iostream>
#include <opencv2/opencv.hpp>
#include"Armor/Armor.hpp"
#include"kalman/kalman.hpp"
using namespace std;
using namespace cv;
int main()
{
    ArmorDetector ad;
    LightBar lb;
    ArmorBox ab;
    KF kf;
    string imgpath = "../1920.png";
    string videopath="../test.avi";
    VideoCapture capture(videopath);
    //Mat img = imread(imgpath,1); 
    Mat frame;
    while (true)
    {
        capture.read(frame);
        imshow("opencv_test", frame);
        waitKey(20);
        ad.run(frame);
        //kf.run(ab.center.x,ab.center.y);
        ad.showDebugInfo(1);    
    }
    //Mat img = imread(imgpath,1); 
    //ad.run(img);
    //ad.showDebugInfo(1);
    //waitKey(0);
    return 0;
}