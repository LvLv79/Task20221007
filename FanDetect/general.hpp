#pragma once
#ifndef GENERAL_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "param_define.hpp"

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class General
{
    General();
    ~General();

public:
private:
    WindmillParam wm_data;
    McuData mcu_data;

    void initEnergy();//能量机关初始化
    void initEnergyParam();//能量机关参数初始化


    int findArmors();
    int findFans(const Mat &src); //引用传递，str不能被修改，而且也不会调用拷贝构造函数
    void fanDilate(Mat &src);
    bool isValidFanContour(Mat &src, const vector<Point> &fanContours);

    vector<RotatedRect> fans;
    int last_fans_cnt;
};

#endif // GENERAL_H