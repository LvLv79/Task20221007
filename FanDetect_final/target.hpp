#pragma once
#ifndef TARGET_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace cv;


class target
{

public:
    RotatedRect targetArmor;
    RotatedRect center_R;

    void setTarget(Mat &src, vector<RotatedRect> Rcontours, vector<RotatedRect> Fcontours);
    

private:
    Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    vector<Point2f> POINTS_2D;
    vector<Point3f> POINTS_3D;
    float armor_height = 11;
    float armor_width = 10;
    float target_angle;
    float distance;

    
    void Cam_Init();
    void calAngle(RotatedRect Armor, RotatedRect R);
    vector<Point2f> setImagePoints(RotatedRect Armor);
    vector<Point3f> setObjectPoints(double width, double height);
    void calDistance(vector<Point3f> SMALL_ARMOR_POINTS_3D, vector<Point2f> targetContour);
    
};

#endif