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

public:
    void run(Mat &src);
    General();
    ~General();

private:
    WindmillParam wm_data;
    McuData mcu_data;

    bool show_img;
    bool show_process;
    bool show_wrong;
    bool show_data;

    void initEnergy();      //能量机关初始化
    void initEnergyParam(); //能量机关参数初始化
    void clearAll();
    void initImage(Mat &src);

    int findArmors(const Mat&src);
    int findFans(const Mat &src); //引用传递，str不能被修改，而且也不会调用拷贝构造函数
    void ArmorDilate(Mat&src);
    void fanDilate(Mat &src);
    bool isValidArmorContour(const vector<Point>&armor_contour);
    bool isValidFanContour(Mat &src, const vector<Point> &fanContours);

    void showFans(string windows_name, const Mat &src);
    void showArmors(string windows_name, const Mat& src);

    vector<RotatedRect> fans;
    vector<RotatedRect>armors;
    int fans_cnt;
    int last_fans_cnt;
};

#endif // GENERAL_H