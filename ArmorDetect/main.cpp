#include <iostream>
#include <opencv2/opencv.hpp>
#include"Armor/Armor.hpp"
#include"Solve/solve.hpp"
using namespace std;
using namespace cv;
int main()
{
    ArmorDetector ad;
    LightBar lb;
    ArmorBox ab;
    AngleSolver as;
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
        as.solveAngles(ad.armors[0].armorVertices,ad.armors[0].center);
        ad.showDebugInfo(1);    
    }
    //Mat img = imread(imgpath,1); 
    //ad.run(img);
    //ad.showDebugInfo(1);
    //waitKey(0);
    return 0;
}