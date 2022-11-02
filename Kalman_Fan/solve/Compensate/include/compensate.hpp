#pragma once
#ifndef R_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;

class Compensate
{

public:
    
    void run(Point2f aim, float v, float s, float h);
    
    float compensate_angle;

private:
    Point2f image_center = Point2f(240, 240);

    void solve_above(float shoot_speed, float distance, float height);
    void solve_below(float shoot_speed, float distance, float height);
    void newton_solution();
    int set(Point2f aim);


    
};

#endif