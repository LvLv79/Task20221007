#include "Flow.hpp"

/**
 * @brief find target armor
 * 筛选条件如下：
    ①装甲板没有子轮廓和同级轮廓，一定有父轮廓。
    ②面积范围与最小外接矩形的长宽比。
 * @param src 
 * @return int 
 */
int Flow::findFlow(const Mat &src)
{
    if (src.empty())
    {
        cout << "src empty!" << endl;
    }
    static Mat src_bin;
    src_bin = src.clone();
    vector<vector<Point>> contours;
    vector<cv::Vec4i> F_hierarchy;
    flowDilate(src_bin);
    findContours(src_bin, contours, F_hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    vector<vector<Point>> valid_child_contours;
    for (int i = 0; i < contours.size(); ++i)
    {
        auto hierarchy = F_hierarchy[i];
        if (hierarchy[0] == -1 &&
            hierarchy[1] == -1 &&
            hierarchy[2] == -1 &&
            hierarchy[3] != -1)
        {
            valid_child_contours.push_back(contours[i]);
        }
    }
    for (auto &contour : valid_child_contours)
    {
        if (!isValidFlow(contour))
        {
            continue; // only end one cycle
        }
        Fcontours.emplace_back(minAreaRect(contour));
    }
    return static_cast<int>(Fcontours.size());
    imshow("armor1", src_bin);
    return 1;
}

/**
 * @brief 对图像进行膨胀处理
 * 
 * @param src 
 */
void Flow::flowDilate(Mat &src)
{
    //膨胀
    int structElementSize = 2;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    dilate(src, src, element);
    //闭运算，消除扇叶上可能存在的小洞
    structElementSize = 3;
    element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    morphologyEx(src, src, MORPH_CLOSE, element);
}

/**
 * @brief 用长宽比和面积判断轮廓是否合适
 * 
 * @param flow_contours 
 * @return true 
 * @return false 
 */
bool Flow::isValidFlow(const vector<Point> flow_contours)
{
    double cur_contour_area = contourArea(flow_contours);
    if (cur_contour_area > Fcontour_max || cur_contour_area < Fcontour_min)
    {
        return false;
    }
    RotatedRect cur_rect = minAreaRect(flow_contours);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    float length_width_ratio = length / width;
    if (length_width_ratio < Fcontour_hw_ratio_min || length_width_ratio > Fcontour_hw_ratio_max)
    {
        return false;
    }
    return true;
}

/** 
 * @brief 输出debug信息
 * 
 * @param src 
 */
void Flow::showFlow(const Mat &src)
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
    for (const auto &Fcontour : Fcontours)
    {
        Point2f vertices[4];       //定义矩形的4个顶点
        Fcontour.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    imshow("windows_name", image2show);
}

/**
 * @brief 清空上一帧的轮廓
 * 
 */
void Flow::clear()
{
    Fcontours.clear();
}

/**
 * @brief 集成跑detetcor
 * 
 * @param src 
 */
void Flow::run(const Mat &src)
{
    clear();
    findFlow(src);
}