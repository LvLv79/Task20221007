#pragma once
#ifndef TARGET_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

#define PI 3.14;
#define ENEMY_BLUE 0
#define ENEMY_RED 1

class target
{

public:
    RotatedRect targetArmor;
    RotatedRect center_R; 
    float target_angle;

    void rect_info(Mat &src, vector<RotatedRect> contours);
    void draw(string windows_name,Mat &src);
    bool setTarget(vector<RotatedRect> Rcontours,vector<RotatedRect> Fcontours);
    void drawAngle();
    void calAngle(RotatedRect Armor, RotatedRect R);
private:
};

#endif