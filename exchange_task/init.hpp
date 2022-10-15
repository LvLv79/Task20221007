#pragma once
#ifndef INIT_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class init
{
public:
    void initImage(Mat &src);

private:
};

#endif