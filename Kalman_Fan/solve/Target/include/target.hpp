#pragma once
#ifndef TARGET_H

#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <math.h>
#include <stdio.h>
#include "kalman.hpp"
#include "compensate.hpp"
#include "sort.hpp"

using namespace std;
using namespace cv;

class target
{

public:
    KF kf;
    Compensate gravity;
    Sort sort;
    RotatedRect targetArmor;
    RotatedRect center_R;

    void setTarget(Mat &src, vector<RotatedRect> Rcontours, vector<RotatedRect> Fcontours);

private:
    Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    vector<Point2f> POINTS_2D;
    vector<Point3f> POINTS_3D;
    float armor_height = 127;
    float armor_width = 230;
    float distance;
    float center2R;
    float target_angle;
    float target_h;
    float tVec_x;
    float tVec_y;
    float tVec_z;

    float x_pitch;
    float y_yaw;

    // total
    void Cam_Init();
    void calAngle(RotatedRect Armor, RotatedRect R);
    void calR(Point2f A, Point2f B);
    vector<Point3f> setObjectPoints(double width, double height);
    vector<Point2f> Rect_points_temp;
    void calDistance(vector<Point3f> SMALL_ARMOR_POINTS_3D, vector<Point2f> targetContour);
};

#endif