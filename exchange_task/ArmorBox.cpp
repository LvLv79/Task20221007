#include "ArmorBox.hpp"

Rect_Points::Rect_Points()
{
    point_x = 0;
    point_y = 0;
}

int Rect_Points::sort_points(vector<RotatedRect> exchange_contours)
{
    if(exchange_contours.size()==0){
       return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        points_x[i]=exchange_contours[i].center.x;
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
    tl = exchange_contours[tl_index].center;
    br = exchange_contours[br_index].center;
    getOther(exchange_contours);
    cout<<"rect 4:"<<tl<<br<<bl<<tr<<endl;
    return 1;
}

void Rect_Points::getMaxOrMin(float* arr, int count, bool isMax)
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
        tl_index = max_index;
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
        br_index = min_index;
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
    if(result[2]<0){
        tr=tempPoints[0];
        bl=tempPoints[1];

    }
    else{
        tr=tempPoints[1];
        bl=tempPoints[0];
    }

    // vector 2 points to judge;
}

Rect_Points::~Rect_Points() {}