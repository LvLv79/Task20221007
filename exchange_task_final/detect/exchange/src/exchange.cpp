/**
 * @file exchange.cpp
 * @author lvlv (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "exchange.hpp"

/**
 * @brief 识别角点轮廓
 * 
 * @param src srcimg
 * @return int 
 */
int Exchange::findCorner(const Mat &src)
{
    if (src.empty())
    {
        cout << "src empty!" << endl;
    }
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3)
    {
        cvtColor(src_bin, src_bin, COLOR_BGR2GRAY);
    }
    vector<vector<Point>> contours;
    vector<cv::Vec4i> R_hierarchy;
    Dilate(src_bin);
    findContours(src_bin, contours, R_hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (auto contour : contours)
    {
        if (!isValidCorner(contour))
        {
            continue; // only end one cycle
        }
        corner_contours.emplace_back(contour);
        exchange_contours.emplace_back(minAreaRect(contour));
    }
    return static_cast<int>(exchange_contours.size());
}

/**
 * @brief 对图像进行腐蚀膨胀操作
 * 
 * @param src 
 */
void Exchange::Dilate(Mat &src)
{
    //膨胀
    int structElementSize = 2;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    // dilate(src, src, element);
    //闭运算，消除扇叶上可能存在的小洞
    structElementSize = 3;
    element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    morphologyEx(src, src, MORPH_CLOSE, element);
}

/**
 * @brief 用长宽比和轮廓面积判断轮廓是否合适
 * 
 * @param Cornercontour 
 * @return true 
 * @return false 
 */
bool Exchange::isValidCorner(const vector<Point> Cornercontour)
{
    float cur_area = contourArea(Cornercontour);
    RotatedRect cur_rect = minAreaRect(Cornercontour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    float length_width_ratio = length / width;
    if (length_width_ratio < Cornercontour_hw_ratio_min || length_width_ratio > Cornercontour_hw_ratio_max)
    {
        return false;
    }
    if (cur_area < Cornercontour_area_min || cur_area > Cornercontour_area_max)
    {
        return false;
    }
    return true;
}

/**
 * @brief 清除上一帧的轮廓
 * 
 */
void Exchange::clearAll()
{
    exchange_contours.clear();
    corner_contours.clear();
}

/**
 * @brief 集成跑detector
 * 
 * @param src 
 */
void Exchange::run(const Mat &src)
{
    clearAll();
    findCorner(src);
}
