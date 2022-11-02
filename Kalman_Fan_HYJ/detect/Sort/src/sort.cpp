#include "sort.hpp"

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
 * @brief using vector to judge bl and br
 *
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

void Sort::clear()
{
    Rect_points.clear();
    temp_Points.clear();
}

void Sort::run(RotatedRect Armor, RotatedRect R)
{
    clear();
    find_below(Armor, R);
    Rect_points.emplace_back(tl);
    Rect_points.emplace_back(tr);
    Rect_points.emplace_back(br);
    Rect_points.emplace_back(bl);
    //cout<<"Rect_points :"<<Rect_points<<endl;
}

