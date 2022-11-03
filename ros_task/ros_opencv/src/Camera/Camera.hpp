#pragma once
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include<iostream>

class Cam{
    private:
        
    public:
        cv::Mat InitImg;
        cv::Mat AdjustedImg;
        cv::Matx<float,3,3>cameraMatrix={1.2853517927598091e+03, 0., 3.1944768628958542e+02, 0.,
       1.2792339468697937e+03, 2.3929354061292258e+02, 0., 0., 1.};

        cv::Matx<float,5,1>distCoeffs={
        -6.3687295852461456e-01, -1.9748008790347320e+00,
       3.0970703651800782e-02, -2.1944646842516919e-03, 0.
        };
        void Cam_Init();
        bool getImage();
        void imgAdjust();
};