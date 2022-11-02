#pragma once
#ifndef EXCHANGE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class Exchange
{
public:
    vector<RotatedRect> exchange_contours;
    vector<vector<Point>>corner_contours;
    float Cornercontour_area_max=200;
    float Cornercontour_area_min=10;

    int findCorner(const Mat &src);
    void run(const Mat &src);
    void Dilate(Mat &src);
    void clearAll();
    bool isValidCorner(const vector<Point> Cornercontour);
    //const Point2f Exchange::crossPointof(const Point2f& bl,const Point2f& tl,const Point2f& tr, const Point2f& br);

private:
    float Cornercontour_hw_ratio_min = 0;
    float Cornercontour_hw_ratio_max = 100;
};

#endif

// four corner four rotatedrect