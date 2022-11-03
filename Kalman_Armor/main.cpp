#include <iostream>
#include <opencv2/opencv.hpp>
#include "Armor.hpp"
#include "kalman.hpp"
using namespace std;
using namespace cv;
int main()
{
    ArmorDetector ad;
    LightBar lb;
    ArmorBox ab;
    KF kf;
    string imgpath = "../1920.png";
    string videopath = "../test.avi";
    VideoCapture capture(videopath);
    Mat frame;
    while (true)
    {
        capture.read(frame);
        imshow("opencv_test", frame);
        if (waitKey(50) == 27)
        {
            if (waitKey(0) == 27)
            {
                break;
            }
        }

        ad.run(frame);
        ad.showDebugInfo(1);
    }
    return 0;
}