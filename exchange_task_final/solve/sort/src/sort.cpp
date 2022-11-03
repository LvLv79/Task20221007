#include "sort.hpp"

////////////////////////////////////////Sort///////////////////////////////////////////////////////////

/**
 * @brief 求出轮廓点距矩形中心点的距离的最大值的下标
 * 
 * @param distance the contours'point to the rect's center
 */
void Sort::getMax(vector<float> distance)
{
    max_index = 0;
    int temp = distance[0];
    int index = 0;

    for (int i = 1; i < distance.size(); i++)
    {
        if (temp < distance[i])
        {
            temp = distance[i];
            index = i;
        }
    }
    max_index = index;
}

/**
 * @brief pass through all of the contours'points, use distance to find the farthest point and set as corner
 * 遍历轮廓的所有点，找到离兑换站中心点距离最远的点设置为新的角点
 * @param center 
 * @param exchange_contours 
 */
void Sort::find_corner(Point2f center, vector<vector<Point>> exchange_contours)
{

    for (int i = 0; i < exchange_contours.size(); i++)
    {
        vector<float> distance;
        for (int j = 0; j < exchange_contours[i].size(); j++)
        {
            float h = sqrt(pow((exchange_contours[i][j].x - center.x), 2) + pow((exchange_contours[i][j].y - center.y), 2));
            distance.emplace_back(h);
        }
        getMax(distance);
        unsorted_corners.emplace_back(exchange_contours[i][max_index]);
    }
}

/**
 * @brief 找到坐标值和最大值和最小值对应点的位置（max_index、min_index）
 * 
 * @param arr 坐标值和数组
 * @param count 
 * @param isMax 最大值or最小值
 */
void Sort::getMaxOrMin(float *arr, int count, bool isMax)
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

/**
 * @brief 使用叉乘判断右上和左下两个点
 * 分别求出两个待选点与左上点的向量a2b_1和a2b_2,若叉乘得到的结果为负，则A点为右上，B点为左下，反之同理。
 * @param exchange_contours 角点的旋转矩形
 */
void Sort::getOther(vector<Point2f> unsorted_corners)
{
    vector<Point2f> tempPoints;
    for (int i = 0; i < 4; i++)
    {
        if (i == tl_index || i == br_index)
        {
            continue;
        }
        tempPoints.emplace_back(unsorted_corners[i]);
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
    Corners.emplace_back(tl);
    Corners.emplace_back(tr);
    Corners.emplace_back(br);
    Corners.emplace_back(bl);
    // vector 2 points to judge;
}

/**
 * @brief sum = point.x + point.y
 * the max_index of sum[max] is the index of below-right(br)
 * the min_index of sum[min] is the index of top-left(tl)
 * -------------------------------------------------------------
 * the other two point can be solve use multiplication cross
 * 
 * @param unsorted_corners 
 * @return int 
 */
int Sort::sort_points(vector<Point2f> unsorted_corners)
{
    if (unsorted_corners.size() == 0)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        points_x[i] = unsorted_corners[i].x;
    }

    for (int i = 0; i < 4; i++)
    {
        points_y[i] = unsorted_corners[i].y;
    }

    for (int i = 0; i < 4; i++)
    {
        points_sum[i] = points_x[i] + points_y[i];
    }

    getMaxOrMin(points_sum, 4, 1);
    getMaxOrMin(points_sum, 4, 0);
    tl = unsorted_corners[tl_index];
    br = unsorted_corners[br_index];
    getOther(unsorted_corners);
    cout << "rect 4:" << tl << tr << br << bl << endl;
    return 1;
}

/////////////////////////////////////Solve//////////////////////////////////////////////////////////////

void Sort::Camera_init()
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

/**
 * @brief set the 3D-points of the world coordinate
 * 
 * @param width exchange-rect's real width
 * @param height exchange-rect's real height
 * @return vector<Point3f> 
 */
vector<Point3f> Sort::setObjectPoints(double width, double height)
{
    POINTS_3D.clear();
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    POINTS_3D.push_back(Point3f(-half_x, half_y, 0));  // tl top left
    POINTS_3D.push_back(Point3f(half_x, half_y, 0));   // tr top right
    POINTS_3D.push_back(Point3f(half_x, -half_y, 0));  // br below right
    POINTS_3D.push_back(Point3f(-half_x, -half_y, 0)); // bl below left

    return POINTS_3D;
}

/**
 * @brief 解算出兑换站的pitch和yaw消息
 * 
 * @param Rect_points 
 */
void Sort::Solve(vector<Point2f> Corners)
{
    Camera_init();

    setObjectPoints(target_width, target_height);

    Mat _rvec, tVec, _rmat;
    solvePnP(POINTS_3D, Corners, cameraMatrix, distCoeffs, _rvec, tVec, false, 0);
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
    // cout << "y_yaw:" << y_yaw << endl;
    // cout << "x_pitch:" << x_pitch << endl;
}

////////////////////////////////////////Draw/////////////////////////////////////////////////

/**
 * @brief show the image for debug
 * 
 * @param src 
 * @param center 
 */
void Sort::draw(Mat src, Point2f center)
{
    line(src, tl, tr, Scalar(0, 0, 255), 2);
    line(src, tr, br, Scalar(0, 0, 255), 2);
    line(src, br, bl, Scalar(0, 0, 255), 2);
    line(src, tl, bl, Scalar(0, 0, 255), 2);

    circle(src, rect_center, 2, Scalar(0, 255, 0), 2, 8, 0);
    putText(src, "x: " + to_string(tVec_x), Point2f(center.x, center.y - 45), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(src, "y: " + to_string(tVec_y), Point2f(center.x, center.y - 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(src, "z: " + to_string(tVec_z), Point2f(center.x, center.y - 15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    putText(src, "x_pitch: " + to_string(x_pitch), Point2f(center.x, center.y), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);

    imshow("unsorted_corners", src);
}

/**
 * @brief 集成跑detector
 * 
 * @param exchange_contours 
 * @param src 
 * @param center
 */
void Sort::run(Point2f center, vector<vector<Point>> exchange_contours, Mat src)
{
    unsorted_corners.clear();
    Corners.clear();
    find_corner(center, exchange_contours);
    sort_points(unsorted_corners);
    Solve(Corners);
    draw(src, center);
}