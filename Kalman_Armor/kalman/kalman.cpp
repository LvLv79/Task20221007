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

int KF::run(float m_x, float m_y)
{
    if (!IsInitialize())
    {
        Eigen::VectorXd x_in(4, 1);
        x_in << m_x, m_y, 0.0, 0.0;
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
        last_point = Point2f(m_x,m_y);
        is_initialized_ = true;
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
    z << m_x, m_y;
    MeasurementUpdate(z);
    // get result
    Eigen::VectorXd x_out = GetX();
    cout << "kalman output x :" << x_out(0) << "y:" << x_out(1) << endl;
    adjust_point =  Point2f(x_out(0),x_out(1));
    delta_pointx = adjust_point.x - last_point.x;
    delta_pointy = adjust_point.y - last_point.y;
    if (abs(delta_pointx) > 10||abs(delta_pointy)>10)
    {
        is_initialized_ = false;
        cout<<"false"<<endl;
        return 1;
    }
    next_point = Point2f(adjust_point.x+delta_pointx,adjust_point.y+delta_pointy);
    last_point = adjust_point;
    return 1;
}

KF::~KF(){};