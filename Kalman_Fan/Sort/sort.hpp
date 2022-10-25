#pragma once
#ifndef R_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;

class Sort
{
public:
    void find_below(RotatedRect Armor, RotatedRect R);
    vector<Point2f> Rect_points;

private:
    void judge_below(float *arr, int count);
    void judge_23(RotatedRect R, vector<Point2f> temp_Points);
    int belowA_index;
    int belowB_index;
    Point2f tl;
    Point2f tr;
    Point2f bl;
    Point2f br;

    vector<Point2f> temp_Points;
};

#endif