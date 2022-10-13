#pragma once
#ifndef ARMOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
//#include <Eigen/Dense>

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

    int sort_points(vector<RotatedRect> exchange_contours);
    void getMaxOrMin(float*arr,int count,bool isMax);
    void getOther(vector<RotatedRect> exchange_contours);

public:
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
    vector<Rect_Points> R_points;
    // vector<float> points_x;
    float points_x[4];
    float points_y[4];
    float points_sum[4];
    //vector<float> points_y;
    //vector<float> points_sum;
    vector<float> Rect_points;
};

#endif