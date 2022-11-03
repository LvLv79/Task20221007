#include "compensate.hpp"

/**
 * @brief 若装甲板在枪管上，利用抛物线模型，求根公式解算得到补偿角度
 * 
 * @param v 子弹射速
 * @param s 枪管到装甲板的水平距离
 * @param h 枪管到装甲板的垂直距离
 */
void Compensate::solve_above(float v, float s, float h)
{
    compensate_angle = static_cast<float>(180 / 3.14 * atan2((pow(v, 2) - sqrt(pow(v, 4) - 9.8 * (2 * h * pow(v, 2) - 9.8 * pow(s, 2)))), (9.8 * s)));
}

/**
 * @brief 若装甲板在枪管下，利用抛物线模型，求根公式解算得到补偿角度
 * 
 * @param v 子弹射速
 * @param s 枪管到装甲板的水平距离
 * @param h 枪管到装甲板的垂直距离
 */
void Compensate::solve_below(float v, float s, float h)
{
    compensate_angle = static_cast<float>(180 / 3.14 * atan2((-pow(v, 2) + sqrt(pow(v, 4) + pow(9.8 * s, 2) + 2 * 9.8 * h * pow(v, 2))), (9.8 * s)));
}

/**
 * @brief 利用装甲板在图像坐标系的坐标与图像中心点判断装甲板相对于枪管的方位
 * 
 * @param aim 装甲板中心点
 * @return int 
 */
int Compensate::set(Point2f aim)
{
    if ((aim.y - image_center.y) > 0)
    {
        return 1;
    }

    if ((aim.y - image_center.y) < 0)
    {
        return 2;
    }

    else
    {
        return 0;
    }
}

/**
 * @brief 集成跑detector
 * 
 * @param aim 装甲板中心点
 * @param v 子弹射速
 * @param s 枪管到装甲板的水平距离
 * @param h 枪管到装甲板的垂直距离
 */
void Compensate::run(Point2f aim, float v, float s, float h)
{
    if (set(aim) == 1)
    {
        solve_above(v, s, h);
        cout<<"compensate_angle + :"<<(compensate_angle)/10<<endl;
    }

    if (set(aim) == 2)
    {
        solve_below(v, s, h);
        cout<<"compensate_angle - :"<<(compensate_angle)/10<<endl;
    }
    
    else{
        cout<<"no need for compensation"<<endl;
    }
}
