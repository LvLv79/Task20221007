#include "Flow.hpp"

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

void Flow::clear()
{
    Fcontours.clear();
}

void Flow::run(const Mat &src)
{
    clear();
    findFlow(src);
    showFlow(src);
}

// activate:hierarchy[i][0]!=-1||hierarchy[i][1]!=1
// not-activate:hierarchy[i][0]=-1&&hierarchy[i][1]=1