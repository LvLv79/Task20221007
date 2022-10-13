#pragma once
#ifndef SORT_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class Sort
{
public:
    void sort_points(vector<RotatedRect> exchange_contours);
    vector<float> bubbleSort(vector<float> &nums);

private:
    vector<float> points_x;
    vector<float> points_y;
    vector<float> points_sum;
    vector<float> points;
    int index;
};

#endif