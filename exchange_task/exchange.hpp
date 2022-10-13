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
    vector<RotatedRect> exchange_rect;
    vector<RotatedRect> exchange_contours;
    vector<Point> center;
    Point2f exchange_rect_point;

    int findCorner(const Mat &src);
    void Draw(const Mat &src);
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