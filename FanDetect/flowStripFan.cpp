#include "general.hpp"

bool General::findFlowStripFan(const Mat &src)
{
    if (src.empty())
    {
        cout << "src empty!" << endl;
    }
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) // 3通道图像
    {
        cvtColor(src_bin, src_bin, COLOR_BGR2GRAY); //转换为灰度图
    }
    vector<vector<Point>> flow_strip_fan_contours;
    FlowStripFanDilate(src_bin);
    findContours(src_bin, flow_strip_fan_contours, 0, 1);
    vector<vector<Point>> candidate_flow_strip_fans;
    for (auto candidate_flow_strip_fan : candidate_flow_strip_fans)
    {
        if (!isValidFlowStripFanContour(src_bin, candidate_flow_strip_fan))
        {
            continue;
        }
        flow_strip_fans.emplace_back(minAreaRect(flow_strip_fan_contours));
    }
    if (flow_strip_fans.empty())
    {
        cout << "flow strip fan false!" << endl;
        return false;
    }

    return true;
}

bool General::isValidFlowStripFanContour(Mat &src, const vector<Point> &flow_strip_fans_contour)
{
    double cur_contour_area = contourArea(flow_strip_fans_contour);
    if (cur_contour_area > wm_data.flow_strip_fan_contour_area_max ||
        cur_contour_area < wm_data.flow_strip_fan_contour_area_min)
    {
        return false;
    }
    RotatedRect cur_rect = minAreaRect(flow_strip_fans_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
    if (length < wm_data.flow_strip_fan_contour_length_min || width < wm_data.flow_strip_fan_contour_width_min || length > wm_data.flow_strip_fan_contour_length_max || width > wm_data.flow_strip_fan_contour_width_max)
    {
        return false;
    }
    float length_width_ratio = length / width;
    if (length_width_ratio > wm_data.flow_strip_fan_contour_hw_ratio_max ||
        length_width_ratio < wm_data.flow_strip_fan_contour_hw_ratio_min)
    {
        return false;
    }
    if (cur_contour_area / cur_size.area() < wm_data.flow_strip_fan_contour_area_ratio_min || cur_contour_area / cur_size.area() > wm_data.flow_strip_fan_contour_area_ratio_max)
    {
        return false;
    }
    return true;
}

bool General::findFlowStripWeak(const Mat &src)
{
    if (src.empty())
    {
        if (show_wrong)
            cout << "empty!" << endl;
        return false;
    }
    cv::Mat src_bin;
    src_bin = src.clone();

    if (src_bin.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src_bin, src_bin, COLOR_GRAY2RGB);
    }
    std::vector<cv::RotatedRect> candidate_armors = armors;
    for (auto &candidate_armor : candidate_armors)
    {
        Point2f vertices[4];
        candidate_armor.size.height *= 1.3;//enlarge??
        candidate_armor.size.width *= 1.3;
        candidate_armor.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
        {
            line(src_bin, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 0), 20);
        }
    }
    cvtColor(src_bin, src_bin, COLOR_BGR2GRAY); //若读取三通道视频文件，需转换为单通道

    FlowStripDilate(src_bin); //图像膨胀，防止图像断开并更方便寻找
    if (show_process)
        imshow("weak Dilate", src_bin);

    std::vector<vector<Point>> flow_strip_contours;
    findContours(src_bin, flow_strip_contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for (auto &flow_strip_contour : flow_strip_contours)
    {
        if (!isValidFlowStripContour(flow_strip_contour))
        {
            continue;
        }
        flow_strips.emplace_back(cv::minAreaRect(flow_strip_contour));
    }

    if (flow_strips.empty())
    {
        if (show_wrong)
            cout << "weak flow strip false!" << endl;
        return false;
    }
    else
    {
        for (const auto &candidate_flow_strip : flow_strips)
        {
            for (const auto &candidate_armor : armors)
            {
                if (pointDistance(candidate_flow_strip.center, candidate_armor.center) <
                        wm_data.Strip_Fan_Distance_max ||
                    pointDistance(candidate_flow_strip.center, candidate_armor.center) >
                        wm_data.Strip_Fan_Distance_min)
                {
                    continue;
                }
                float angle_armor = candidate_armor.size.width > candidate_armor.size.height ? candidate_armor.angle : candidate_armor.angle - 90;
                float angle_strip = candidate_flow_strip.size.width > candidate_flow_strip.size.height ? candidate_flow_strip.angle : candidate_flow_strip.angle - 90;

                if (abs(angle_armor - angle_strip) < 60 || abs(angle_armor - angle_strip) > 120)
                {
                    continue;
                }
                target_armor = candidate_armor;
                target_point = candidate_armor.center;
                flow_strip = candidate_flow_strip;
                return true;
            }
        }
        if (show_wrong)
            cout << "weak flow strip false!" << endl;
        return false;
    }
}

bool General::isValidFlowStripContour(const vector<cv::Point> &flow_strip_contour)
{
    double cur_contour_area = contourArea(flow_strip_contour);
    if (cur_contour_area > wm_data.flow_strip_contour_area_max || cur_contour_area < wm_data.flow_strip_contour_area_min)
    {
        if (show_wrong)
            cout << "FlowStrip_cur_contour_area" << cur_contour_area << endl;
        if (show_wrong)
            cout << "FlowStrip area fail." << endl;
        return false;
    } //流动条面积筛选

    RotatedRect cur_rect = minAreaRect(flow_strip_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
    if (length > wm_data.flow_strip_contour_length_max || width > wm_data.flow_strip_contour_width_max || length < wm_data.flow_strip_contour_length_min || width < wm_data.flow_strip_contour_width_min)
    {
        if (show_wrong)
            cout << "length width fail." << endl;
        return false;
    } //流动条长宽筛选
    float length_width_aim = length / width;
    if (length_width_aim < wm_data.flow_strip_contour_hw_ratio_min || length_width_aim > wm_data.flow_strip_contour_hw_ratio_max)
    {
        if (show_wrong)
            cout << "length_width_aim fail." << endl;
        return false;
    } //长宽比筛选
    if (cur_contour_area / cur_size.area() < wm_data.flow_strip_contour_area_ratio_min)
    {
        if (show_wrong)
            cout << "cur_contour_area / cur_size.area() fail." << endl;
        return false;
    }
    return true;
}

void General::showFlowStripFan(string windows_name, const Mat& src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    }
    else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }

    Point2f strip_fan_vertices[4];      //定义矩形的4个顶点
    flow_strip_fan.points(strip_fan_vertices);   //计算矩形的4个顶点for (int i = 0; i < 4; i++)
    for (int i = 0; i < 4; i++)
        line(image2show, strip_fan_vertices[i], strip_fan_vertices[(i + 1) % 4], Scalar(127, 127, 255), 2);
    imshow(windows_name, image2show);
}