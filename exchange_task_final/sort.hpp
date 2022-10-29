#pragma once
#ifndef SORT_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class Sort
{

public:
    void run(Point2f center, vector<vector<Point>> exchange_contours, Mat src);

    float x_pitch;
    float y_yaw;

private:
    int tl_index;
    int bl_index;
    int tr_index;
    int br_index;
    int max_index;
    float point_x;
    float point_y;
    float point_sum;
    Point2f tl;
    Point2f bl;
    Point2f tr;
    Point2f br;
    float points_x[4];
    float points_y[4];
    float points_sum[4];
    vector<Point2f> Corners;
    Point2f rect_center;

    vector<Point2f> POINTS_2D;
    vector<Point3f> POINTS_3D;
    float target_height = 480;
    float target_width = 848;
    double tVec_x;
    double tVec_y;
    double tVec_z;

    Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);

    const Point2f crossPointof(const Point2f &bl, const Point2f &tl, const Point2f &tr, const Point2f &br);
    vector<Point2f> setImagePoints(vector<Point2f> Rect_points);
    int sort_points(vector<Point2f> unsorted_corners);
    void getMaxOrMin(float *arr, int count, bool isMax);
    void getOther(vector<Point2f> unsorted_corners);
    vector<Point3f> setObjectPoints(double width, double height);
    void Solve(vector<Point2f> Corners);
    void Camera_init();

    void find_corner(Point2f center, vector<vector<Point>> exchange_contours);
    void getMax(vector<float> distance);

    void draw(Mat src,Point2f center);
    

    vector<Point2f> unsorted_corners;
    
};

#endif