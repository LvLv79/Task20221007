#pragma once
#ifndef FLOW_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class Flow
{
public:
    void run(const Mat &src);
    vector<RotatedRect> Fcontours;

private:
    int findFlow(const Mat &src);
    void flowDilate(Mat &src);
    bool isValidFlow(const vector<Point> flow_contours);
    void showFlow(const Mat &src);
    void clear();

    float Fcontour_max = 1500;
    float Fcontour_min = 500;
    float Fcontour_hw_ratio_max = 2;
    float Fcontour_hw_ratio_min = 1;
};

#endif