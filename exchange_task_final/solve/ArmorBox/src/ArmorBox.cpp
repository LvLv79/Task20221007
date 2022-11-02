#include "ArmorBox.hpp"

Rect_Points::Rect_Points()
{
    point_x = 0;
    point_y = 0;
}

void Rect_Points::Camera_init()
{
    cameraMatrix.at<double>(0, 0) = 5.9763827661155904e+02;
    cameraMatrix.at<double>(0, 1) = 0;
    cameraMatrix.at<double>(0, 2) = 4.1575511901601089e+02;
    cameraMatrix.at<double>(1, 1) = 5.9922205940008985e+02;
    cameraMatrix.at<double>(1, 2) = 2.6769310598084320e+02;

    distCoeffs.at<double>(0, 0) = 5.9365728086275861e-02;
    distCoeffs.at<double>(1, 0) = 6.3271114889939875e-02;
    distCoeffs.at<double>(2, 0) = 5.5006940318826766e-03;
    distCoeffs.at<double>(3, 0) = -3.5032524991503678e-03;
    distCoeffs.at<double>(4, 0) = 0;

    return;
}

int Rect_Points::sort_points(vector<RotatedRect> exchange_contours)
{
    if (exchange_contours.size() == 0)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        points_x[i] = exchange_contours[i].center.x;
    }

    for (int i = 0; i < 4; i++)
    {
        points_y[i] = exchange_contours[i].center.y;
    }

    for (int i = 0; i < 4; i++)
    {
        points_sum[i] = points_x[i] + points_y[i];
    }

    getMaxOrMin(points_sum, 4, 1);
    getMaxOrMin(points_sum, 4, 0);
    tl = exchange_contours[tl_index].center;
    br = exchange_contours[br_index].center;
    getOther(exchange_contours);
    //cout << "rect 4:" << tl << tr << br << bl << endl;
    return 1;
}

void Rect_Points::getMaxOrMin(float *arr, int count, bool isMax)
{
    int temp = arr[0];
    int max_index = 0;
    int min_index = 0;

    if (isMax)
    {
        for (int i = 1; i < count; i++)
        {
            if (temp < arr[i])
            {
                temp = arr[i];
                max_index = i;
            }
        }
        br_index = max_index;
    }
    else
    {
        for (int i = 1; i < count; i++)
        {
            if (temp > arr[i])
            {
                temp = arr[i];
                min_index = i;
            }
        }
        tl_index = min_index;
    }
}

void Rect_Points::getOther(vector<RotatedRect> exchange_contours)
{
    vector<Point2f> tempPoints;
    for (int i = 0; i < 4; i++)
    {
        if (i == tl_index || i == br_index)
        {
            continue;
        }
        tempPoints.emplace_back(exchange_contours[i].center);
    }

    Vec3f a2b_1 = {tempPoints[0].x - tl.x, tempPoints[0].y - tl.y, 0};
    Vec3f a2b_2 = {tempPoints[1].x - tl.x, tempPoints[1].y - tl.y, 0};

    Vec3f result = a2b_2.cross(a2b_1);
    if (result[2] < 0)
    {
        tr = tempPoints[0];
        bl = tempPoints[1];
    }
    else
    {
        tr = tempPoints[1];
        bl = tempPoints[0];
    }
    Rect_points.emplace_back(tl);
    Rect_points.emplace_back(tr);
    Rect_points.emplace_back(br);
    Rect_points.emplace_back(bl);
    // vector 2 points to judge;
}

const Point2f Rect_Points::crossPointof(const Point2f &bl, const Point2f &tl, const Point2f &tr, const Point2f &br)
{
    float a1 = tr.y - bl.y;
    float b1 = tr.x - bl.x;
    float c1 = bl.x * tr.y - tr.x * bl.y;

    float a2 = br.y - tl.y;
    float b2 = br.x - tl.x;
    float c2 = tl.x * br.y - br.x * tl.y;

    float d = a1 * b2 - a2 * b1;

    if (d == 0.0)
    {
        return Point2f(FLT_MAX, FLT_MAX);
    }
    else
    {
        return Point2f((b2 * c1 - b1 * c2) / d, (c1 * a2 - c2 * a1) / d);
    }
}

vector<Point3f> Rect_Points::setObjectPoints(double width, double height)
{
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    POINTS_3D.push_back(Point3f(-half_x, half_y, 0));  // tl top left
    POINTS_3D.push_back(Point3f(half_x, half_y, 0));   // tr top right
    POINTS_3D.push_back(Point3f(half_x, -half_y, 0));  // br below right
    POINTS_3D.push_back(Point3f(-half_x, -half_y, 0)); // bl below left

    return POINTS_3D;
}

vector<Point2f> Rect_Points::setImagePoints(vector<Point> Rect_points)
{

    POINTS_2D.emplace_back(Rect_points[1]);
    POINTS_2D.emplace_back(Rect_points[2]);
    POINTS_2D.emplace_back(Rect_points[3]);
    POINTS_2D.emplace_back(Rect_points[0]);
    return POINTS_2D;
}

void Rect_Points::Solve(vector<Point> Rect_points)
{
    Camera_init();

    setImagePoints(Rect_points);
    setObjectPoints(target_width, target_height);

    Mat _rvec, tVec, _rmat;
    solvePnP(POINTS_3D, POINTS_2D, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);
    double x_pos = *_rvec.ptr(0);
    double y_pos = *_rvec.ptr(1);
    double z_pos = *_rvec.ptr(2);
    tVec_x = *tVec.ptr(0);
    tVec_y = *tVec.ptr(1);
    tVec_z = *tVec.ptr(2);

    Rodrigues(_rvec, _rmat);
    _rmat.convertTo(_rmat, CV_64FC1);
    tVec.convertTo(tVec, CV_64FC1);

    double tan_pitch = y_pos / sqrt(x_pos * x_pos + z_pos * z_pos);
    double tan_yaw = x_pos / z_pos;
    x_pitch = -atanf(tan_pitch) * 180.f / CV_PI;
    y_yaw = atanf(tan_yaw) * 180.f / CV_PI;
    float distance = sqrt(tVec_x * tVec_x + tVec_y * tVec_y + tVec_z * tVec_z);
    //cout << "y_yaw:" << y_yaw << endl;
    //cout << "x_pitch:" << x_pitch << endl;
}

void Rect_Points::draw(const Mat &src)
{
    if (src.empty())
        return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    }
    else if (src.type() == CV_8UC3) // RGB 彩色
    {
        image2show = src.clone();
    }
    line(image2show, tl, tr, Scalar(0, 0, 255), 2);
    line(image2show, tr, br, Scalar(0, 0, 255), 2);
    line(image2show, br, bl, Scalar(0, 0, 255), 2);
    line(image2show, tl, bl, Scalar(0, 0, 255), 2);
    circle(image2show, rect_center, 2, Scalar(0, 255, 0), 2, 8, 0);
    putText(image2show, "x: " + to_string(tVec_x), Point2f(rect_center.x, rect_center.y - 45), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(image2show, "y: " + to_string(tVec_y), Point2f(rect_center.x, rect_center.y - 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(image2show, "z: " + to_string(tVec_z), Point2f(rect_center.x, rect_center.y-15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(image2show, "x_pitch: " + to_string(x_pitch), Point2f(rect_center.x, rect_center.y), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    imshow("Exchange", image2show);
}

void Rect_Points::run(vector<RotatedRect> exchange_contours, const Mat &src)
{
    sort_points(exchange_contours);
    rect_center = crossPointof(bl, tl, tr, br);
    Solve(Rect_points);
    //draw(src);
}

Rect_Points::~Rect_Points() {}