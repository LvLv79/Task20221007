#pragma once
#ifndef R_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class Filter
{

public:
    void run(Mat &src);
    void initImage(Mat &src);
    vector<RotatedRect> Rcontours;

private:
    void showR(const Mat &src);
    int findR(const Mat &src);
    bool isValidR(const vector<Point> Rcontour);
    void RDilate(cv::Mat &src);
    void clearAll();

    float Rcontour_max = 200;
    float Rcontour_min = 90;
    float Rcontour_hw_ratio_max = 1.2;
    float Rcontour_hw_ratio_min = 0.8;
};

#endif