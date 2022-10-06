#include "target.hpp"

void target::rect_info(Mat &src, vector<RotatedRect> contours)
{
    if (src.empty())
        return;
    for (const auto &contour : contours)
    {
        Point2f vertices[4];      //定义矩形的4个顶点
        contour.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    // imshow(windows_name, image2show);
}

bool target::setTarget(vector<RotatedRect> Rcontours, vector<RotatedRect> Fcontours)
{
    if (Rcontours.size() != 1 || Fcontours.size() != 1)
    {
        return false;
    }
    center_R = Rcontours[0];
    targetArmor = Fcontours[0];
    return true;
}

void target::calAngle(RotatedRect Armor, RotatedRect R)
{
    target_angle = static_cast<float>(180 / 3.14 * atan2((-1 * (Armor.center.y - R.center.y)), (Armor.center.x - R.center.x)));
}

void calDistance()
{
}

void drawRect()
{
}
/*
void target::draw(){
if(setTarget()==0)
imshow"window with "no target found"
if==1
draw()angle and distance
*/