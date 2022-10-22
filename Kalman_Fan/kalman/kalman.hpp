#pragma once
#ifndef KALMAN_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

#define PI 3.14;

class KF
{
public:
    // Constructor
    KF()
    {
        is_initialized_ = false;
    };
    // Destructor
    ~KF();

    Eigen::VectorXd GetX()
    {
        return x_;
    }

    bool IsInitialize()
    {
        return is_initialized_;
    }

    void Initialization(Eigen::VectorXd x_in);

    int run(float angle, float m_y, Point2f center, double R);

    vector<Point2f> center_next;
    float adjust_angle;
    Point2f predict_point;

    // flag of initialization;
    bool is_initialized_;

private:

    double dt;
    double next_time;
    double last_time;
    float last_angle;
    float cur_angle;
    float next_angle;

    // state vector
    Eigen::VectorXd x_;
    Eigen::MatrixXd F_; // t0-t
    Eigen::MatrixXd P_;
    Eigen::MatrixXd Q_;
    Eigen::MatrixXd H_;
    Eigen::MatrixXd R_;

    void setT();
    void setF(Eigen::MatrixXd F_in);
    void setP(Eigen::MatrixXd P_in);
    void setQ(Eigen::MatrixXd Q_in);
    void setH(Eigen::MatrixXd H_in);
    void setR(Eigen::MatrixXd R_in);
    void Prediction();
    void MeasurementUpdate(const Eigen::VectorXd &z);
    inline Point2f calcPoint(Point2f center, double R, double angle);
};

#endif