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
    ~General() = default;

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

    bool findFlowStripFan(const Mat &src);
    void Practice(Mat &src);
    int findArmors(const Mat &src);
    int findFans(const Mat &src); //引用传递，str不能被修改，而且也不会调用拷贝构造函数
    void ArmorDilate(Mat &src);
    void fanDilate(Mat &src);
    void FlowStripDilate(cv::Mat &src);
    void FlowStripFanDilate(Mat &src);
    bool findFlowStripWeak(const Mat &src);
    bool isValidArmorContour(const vector<Point> &armor_contour);
    bool isValidFanContour(Mat &src, const vector<Point> &fanContours);
    bool isValidFlowStripContour(const vector<Point> &flow_strip_contour);
    bool isValidFlowStripFanContour(Mat &src, const vector<Point> &flow_strip_fan_contour);

    void showFans(string windows_name, const Mat &src);
    void showArmors(string windows_name, const Mat &src);
    void showFlowStripFan(string windows_name, const Mat& src);

    double pointDistance(cv::Point point_1, cv::Point point_2);

    RotatedRect flow_strip_fan;
    RotatedRect flow_strip;
    RotatedRect target_armor;

    Point circle_center_point;
    Point target_point;

    vector<RotatedRect> fans;
    vector<RotatedRect> armors;
    vector<RotatedRect> flow_strip_fans;
    vector<RotatedRect> flow_strips;
    int fans_cnt;
    int last_fans_cnt;
};

#endif // GENERAL_H