#pragma once
#ifndef ARMOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class ArmorDetect
{
public:
    void run(const Mat &src);

    vector<RotatedRect> Armorcontours;
    void ArmorDilate(Mat &src);
    int findArmors(const Mat &src);
    void showArmors(string windows_name, const Mat &src);
    void clearAll();

private:
    
};
#endif
