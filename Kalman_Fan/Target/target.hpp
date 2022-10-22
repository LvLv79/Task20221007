#pragma once
#ifndef TARGET_H

#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <math.h>
#include <stdio.h>
#include"../kalman/kalman.hpp"
#include"../Compensate/compensate.hpp"

using namespace std;
using namespace cv;


class target
{

public:
    KF kf;
    Compensate gravity;
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

    double tVec_x;
    double tVec_y;
    double tVec_z;
    

    
    void Cam_Init();
    void calAngle(RotatedRect Armor, RotatedRect R);
    void calR(Point2f A,Point2f B);
    vector<Point2f> setImagePoints(RotatedRect Armor);
    vector<Point3f> setObjectPoints(double width, double height);
    void calDistance(vector<Point3f> SMALL_ARMOR_POINTS_3D, vector<Point2f> targetContour);
    
};

#endif