#pragma once
#ifndef INIT_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class init
{
public:
    void initImage(Mat &src);

    void Solve(RotatedRect Armor);
    float x_pitch;
    float y_yaw;

private:
    Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    vector<Point2f> POINTS_2D;
    vector<Point3f> POINTS_3D;
    vector<Point2f> setImagePoints(vector<Point>centers);
    vector<Point3f> setObjectPoints(double width, double height);
    float target_height = 288;
    float target_width = 288;
    void Camera_init();
};

#endif