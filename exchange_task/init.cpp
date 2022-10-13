#include "init.hpp"

void init::Camera_init()
{
}

void init::initImage(Mat &src)
{
    vector<Mat> channels;
    split(src, channels);                                                     //分离通道
    threshold(channels.at(0) - channels.at(2), src, 100, 255, THRESH_BINARY); //二值化
    //  把一个3通道图像转换成3个单通道图像
}

/*vector<Point2f> init::setImagePoints(vector<Point>centers)
{
    
    POINTS_2D.emplace_back(armorVertices[1]);
    POINTS_2D.emplace_back(armorVertices[2]);
    POINTS_2D.emplace_back(armorVertices[3]);
    POINTS_2D.emplace_back(armorVertices[0]);
    return POINTS_2D;
}*/

vector<Point3f> init::setObjectPoints(double width, double height)
{
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    POINTS_3D.push_back(Point3f(-half_x, half_y, 0));  // tl top left
    POINTS_3D.push_back(Point3f(half_x, half_y, 0));   // tr top right
    POINTS_3D.push_back(Point3f(half_x, -half_y, 0));  // br below right
    POINTS_3D.push_back(Point3f(-half_x, -half_y, 0)); // bl below left

    return POINTS_3D;
}

void init::Solve(RotatedRect Armor)
{
    Camera_init();
    //setImagePoints(Armor);
    setObjectPoints(target_width, target_height);

    Mat _rvec, tVec;
    solvePnP(POINTS_3D, POINTS_2D, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);
    double x_pos = tVec.at<double>(0, 0);
    double y_pos = tVec.at<double>(1, 0);
    double z_pos = tVec.at<double>(2, 0);

    double tan_pitch = y_pos / sqrt(x_pos * x_pos + z_pos * z_pos);
    double tan_yaw = x_pos / z_pos;
    x_pitch = -atan(tan_pitch) * 180 / CV_PI;
    y_yaw = atan(tan_yaw) * 180 / CV_PI;
    cout<<"y_yaw:"<<y_yaw<<endl;
}