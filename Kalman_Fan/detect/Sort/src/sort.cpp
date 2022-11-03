#include "sort.hpp"

/**
 * @brief 找出左下（bl）和右下（br）两个点
 * 1.先算出该点与中心R的距离，bl和br两个点一定为距离最小
 * 2.再算出两点和中心点的向量AR、BR,若AR叉乘BR为负数，则A点为bl,B点为br，反之同理。
 * @param Armor 
 * @param R 
 */
void Sort::find_below(RotatedRect Armor, RotatedRect R)
{
    Point2f temp[4];
    float distance[4];

    Armor.points(temp);
    for (int i = 0; i < 4; i++)
    {
        temp_Points.emplace_back(temp[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        distance[i] = abs(sqrt(pow((R.center.x - temp_Points[i].x), 2) + pow((R.center.y - temp_Points[i].y), 2)));
    }

    judge_below(distance, 4);
    judge_23(R, temp_Points);
}

/**
 * @brief 找出距离最小的两个点
 * 
 * @param arr 
 * @param count 
 */
void Sort::judge_below(float *arr, int count)
{
    int temp = arr[0];
    int A_index = 0;
    int B_index = 0;

    for (int i = 1; i < count; i++)
    {
        if (temp > arr[i])
        {
            temp = arr[i];
            A_index = i;
        }
    }
    belowA_index = A_index;
    int temp_distance=arr[A_index];
    arr[A_index] = 999;
    temp = 1000;
    for (int i = 1; i < count; i++)
    {
        if (temp > arr[i])
        {
            temp = arr[i];
            B_index = i;
        }
    }
    belowB_index = B_index;
    arr[A_index]=temp_distance;
}

/**
 * @brief 算出两点和中心点的向量AR、BR,若AR叉乘BR为负数，则A点为bl,B点为br，反之同理。
 * 
 * @param R R标的旋转矩形
 * @param temp_Points 待排序的四个点
 */
void Sort::judge_23(RotatedRect R, vector<Point2f> temp_Points)
{
    vector<Point2f> tempPoints;

    tempPoints.emplace_back(temp_Points[belowA_index]);
    tempPoints.emplace_back(temp_Points[belowB_index]);

    Vec3f a2b_1 = {tempPoints[0].x - R.center.x, tempPoints[0].y - R.center.y, 0};
    Vec3f a2b_2 = {tempPoints[1].x - R.center.x, tempPoints[1].y - R.center.y, 0};

    Vec3f result = a2b_2.cross(a2b_1);
    if (result[2] < 0)
    {
        br = tempPoints[1];
        bl = tempPoints[0];
    }
    else
    {
        br = tempPoints[0];
        bl = tempPoints[1];
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == belowA_index || i == belowB_index)
        {
            continue;
        }
        tempPoints.emplace_back(temp_Points[i]);
    }

    float h1 = abs(sqrt(pow((bl.x - tempPoints[2].x), 2) + pow((bl.y - tempPoints[2].y), 2)));
    float h2 = abs(sqrt(pow((bl.x - tempPoints[3].x), 2) + pow((bl.y - tempPoints[3].y), 2)));

    if (h1 < h2)
    {
        tl = tempPoints[2];
        tr = tempPoints[3];
    }
    else
    {
        tr = tempPoints[2];
        tl = tempPoints[3];
    }
}

/**
 * @brief 清除上一帧识别到的点
 * 
 */
void Sort::clear()
{
    Rect_points.clear();
    temp_Points.clear();
}

/**
 * @brief 集成跑detector
 * 
 * @param Armor 装甲板的旋转矩形
 * @param R R标的旋转矩形
 */
void Sort::run(RotatedRect Armor, RotatedRect R)
{
    clear();
    find_below(Armor, R);
    Rect_points.emplace_back(tl);
    Rect_points.emplace_back(tr);
    Rect_points.emplace_back(br);
    Rect_points.emplace_back(bl);
}

