#include "init.hpp"

void init::Camera_init()
{
    cameraMatrix.at<double>(0, 0) = 1.1527e+03;
    cameraMatrix.at<double>(0, 1) = 0;
    cameraMatrix.at<double>(0, 2) = 618.6327;
    cameraMatrix.at<double>(1, 1) = 1.1527e+03;
    cameraMatrix.at<double>(1, 2) = 361.1508;

    distCoeffs.at<double>(0, 0) = 0.0741;
    distCoeffs.at<double>(1, 0) = -0.0685;
    distCoeffs.at<double>(2, 0) = 0;
    distCoeffs.at<double>(3, 0) = 0;
    distCoeffs.at<double>(4, 0) = 0;

    return;
}

void init::initImage(Mat &src)
{
    vector<Mat> channels;
    split(src, channels);                                                     //分离通道
    threshold(channels.at(0) - channels.at(2), src, 100, 255, THRESH_BINARY); //二值化
    int structElementSize = 3;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    dilate(src, src, element);
    structElementSize = 2;
    element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    morphologyEx(src, src, MORPH_RECT, element);
    //  把一个3通道图像转换成3个单通道图像
}

vector<Point2f> init::setImagePoints(vector<Point> Rect_points)
{

    POINTS_2D.emplace_back(Rect_points[1]);
    POINTS_2D.emplace_back(Rect_points[2]);
    POINTS_2D.emplace_back(Rect_points[3]);
    POINTS_2D.emplace_back(Rect_points[0]);
    return POINTS_2D;
}

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

void init::Solve(vector<Point> Rect_points)
{
    Camera_init();

    setImagePoints(Rect_points);
    setObjectPoints(target_width, target_height);

    Mat _rvec, tVec;
    solvePnP(POINTS_3D, POINTS_2D, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);
    double x_pos = *_rvec.ptr(0);
    double y_pos = *_rvec.ptr(1);
    double z_pos = *_rvec.ptr(2);
    Rodrigues(_rvec,_rvec);
    

    double tan_pitch = y_pos / sqrt(x_pos * x_pos + z_pos * z_pos);
    double tan_yaw = x_pos / z_pos;
    x_pitch = -atanf(tan_pitch) * 180.f/ CV_PI;
    y_yaw = atanf(tan_yaw) * 180.f/ CV_PI;
    float distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
    cout << "y_yaw:" << y_yaw << endl;
    cout << "x_pitch:" << x_pitch << endl;
}