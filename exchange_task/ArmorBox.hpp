#pragma once
#ifndef ARMOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1
class Rect_Points
{
public:
    Rect_Points();
    /**
     *@brief: Parametrical constructor of armorBox 装甲板有参构造函数
     *@param: two LightBar  左右两个灯条
     */
    ~Rect_Points();

    
    
    void run(vector<RotatedRect> exchange_contours,const Mat &src);

    float x_pitch;
    float y_yaw;
    
    
private:
    int tl_index;
    int bl_index;
    int tr_index;
    int br_index;
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
    vector<Point> Rect_points;
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

    const Point2f crossPointof(const Point2f& bl,const Point2f& tl,const Point2f& tr, const Point2f& br);
    vector<Point2f> setImagePoints(vector<Point> Rect_points);
    int sort_points(vector<RotatedRect> exchange_contours);
    void getMaxOrMin(float*arr,int count,bool isMax);
    void getOther(vector<RotatedRect> exchange_contours);
    vector<Point3f> setObjectPoints(double width, double height);
    void Camera_init();
    void draw(const Mat &src);
    void Solve(vector<Point> Rect_points);
};

#endif