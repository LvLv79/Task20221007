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

/**
 * @brief sum = point.x + point.y（坐标值和）
 * the max_index of sum[max] is the index of 右下点(br)
 * the min_index of sum[min] is the index of 左上点(tl)
 * -------------------------------------------------------------
 * the other two point can be solve use multiplication cross
 * 
 * @param exchange_contours 
 * @return int 
 */
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

/**
 * @brief 找到坐标值和最大值和最小值对应点的位置（max_index、min_index）
 * 
 * @param arr 坐标值和数组
 * @param count 
 * @param isMax 最大值or最小值
 */
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

/**
 * @brief 使用叉乘判断右上和左下两个点
 * 分别求出两个待选点与左上点的向量a2b_1和a2b_2,若叉乘得到的结果为负，则A点为右上，B点为左下，反之同理。
 * @param exchange_contours 角点的旋转矩形
 */
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

    Vec3f result = a2b_2.cross(a2b_1);//multiplication cross
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
}

/**
 * @brief 找到兑换站的中心点
 * 
 * @param bl 左下
 * @param tl 左上
 * @param tr 右上
 * @param br 右下
 * @return const Point2f 
 */
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

/**
 * @brief 设置兑换站在世界坐标系下的点
 * 
 * @param width 兑换站的真实宽度
 * @param height 兑换站的真实长度
 * @return vector<Point3f> 
 */
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

/**
 * @brief 将Point转换为Point2f传入solvePNP
 * 
 * @param Rect_points 
 * @return vector<Point2f> 
 */
vector<Point2f> Rect_Points::setImagePoints(vector<Point> Rect_points)
{

    POINTS_2D.emplace_back(Rect_points[1]);
    POINTS_2D.emplace_back(Rect_points[2]);
    POINTS_2D.emplace_back(Rect_points[3]);
    POINTS_2D.emplace_back(Rect_points[0]);
    return POINTS_2D;
}

/**
 * @brief 集成跑detector
 * 
 * @param exchange_contours 
 * @param src 
 */
void Rect_Points::run(vector<RotatedRect> exchange_contours, const Mat &src)
{
    sort_points(exchange_contours);
    rect_center = crossPointof(bl, tl, tr, br);
}

Rect_Points::~Rect_Points() {}