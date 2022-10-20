#include "kalman.hpp"

void KF::Initialization(Eigen::VectorXd x_in)
{
    x_ = x_in;
}

void KF::setT()
{
    next_time = getTickCount() / getTickFrequency();
    dt = (next_time - last_time) * 1000.0f;
    last_time = next_time;
}

void KF::setF(Eigen::MatrixXd F_in)
{
    F_ = F_in;
}

void KF::setP(Eigen::MatrixXd P_in)
{
    P_ = P_in;
}

void KF::setQ(Eigen::MatrixXd Q_in)
{
    Q_ = Q_in;
}

void KF::setH(Eigen::MatrixXd H_in)
{
    H_ = H_in;
}

void KF::setR(Eigen::MatrixXd R_in)
{
    R_ = R_in;
}

void KF::Prediction()
{
    x_ = F_ * x_;
    Eigen::MatrixXd Ft = F_.transpose();
    P_ = F_ * P_ * Ft + Q_;
}

void KF::MeasurementUpdate(const Eigen::VectorXd &z)
{
    Eigen::VectorXd y = z - H_ * x_;
    Eigen::MatrixXd S = H_ * P_ * H_.transpose() + R_;
    Eigen::MatrixXd K = P_ * H_.transpose() * S.inverse();
    x_ = x_ + (K * y);
    int size = x_.size();
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(size, size);
    P_ = (I - K * H_) * P_;
}

inline Point2f KF::calcPoint(Point2f center, double R, double angle)
{
    double pre_angle = angle / 180 * CV_PI;
    return center + Point2f((float)cos(pre_angle), (float)-sin(pre_angle)) * (float)R;
}

int KF::run(float angle, float m_y, Point2f center, double R)
{
    if (!IsInitialize())
    {
        Eigen::VectorXd x_in(4, 1);
        x_in << angle, m_y, 0.0, 0.0;
        Initialization(x_in);

        // state covariance matrix
        Eigen::MatrixXd P_in(4, 4);
        P_in << 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 100.0, 0.0,
            0.0, 0.0, 0.0, 100.0;
        setP(P_in);

        // process covariance matrix
        Eigen::MatrixXd Q_in(4, 4);
        Q_in << 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;
        setQ(Q_in);

        // measurement matrix
        Eigen::MatrixXd H_in(2, 4);
        H_in << 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0;
        setH(H_in);

        // R
        Eigen::MatrixXd R_in(2, 2);
        R_in << 0.0225, 0.0,
            0.0, 0.0225;
        setR(R_in);
        last_angle = angle;
        is_initialized_ = true;
        return 1;
    }
    setT();
    Eigen::MatrixXd F_in(4, 4);
    F_in << 1.0, 0.0, dt, 0.0,
        0.0, 1.0, 0.0, dt,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    setF(F_in);
    Prediction();

    Eigen::VectorXd z(2, 1);
    z << angle, m_y;
    MeasurementUpdate(z);
    // get result
    Eigen::VectorXd x_out = GetX();
    adjust_angle = x_out(0);
    cur_angle = adjust_angle - last_angle;
    next_angle = adjust_angle + cur_angle;
    last_angle = adjust_angle;
    predict_point = calcPoint(center, R, next_angle);
    return 1;
}

KF::~KF(){};