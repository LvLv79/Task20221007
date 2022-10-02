#include "general.hpp"

//此函数用于寻找图像内所有的大风车扇叶
int General::findFans(const Mat &src)
{
    // src judgement first
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
    vector<vector<Point>> fanContours;
    fanDilate(src_bin);                       //图像膨胀，防止图像断开并更方便寻找
    findContours(src_bin, fanContours, 0, 1); // why 0 1,notCV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE
    for (auto &fanContour : fanContours)
    {
        // a function used to judge proper contours
        fans.emplace_back(minAreaRect(fanContours));
    }
    if (fans.size() < last_fans_cnt)
    {
        last_fans_cnt = static_cast<int>(fans.size()); // size_t to int
    }
    return static_cast<int>(fans.size());
}

bool General::isValidFanContour(Mat &src, const vector<Point> &fanContours)
{
    double cur_contour_area = contourArea(fanContours);
    if (cur_contour_area > wm_data.flow_area_min || cur_contour_area < wm_data.flow_area_max)
    {
        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(fanContours);//最小外接矩形（旋转矩形）
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    if (length < wm_data.flow_length_min || length > wm_data.flow_length_max || width < wm_data.flow_width_min || width > wm_data.flow_width_max)
    {
        return false;
        //矩形边长不合适
    }
    float length_width_radio = length / width;
    if (length_width_radio > wm_data.flow_length_max || length_width_radio < wm_data.flow_aim_min)
    {
        return false;
        //长宽比不合适
    }
    if (cur_contour_area / cur_size.area() < wm_data.flow_area_ratio_min)
    {
        return false;
        //轮廓对矩形的面积占有率不合适
    }
    return true;
}

void General::showFans(string windows_name,const Mat& src){
    if(src.empty())return;
    static Mat image2show;//static??????
    if(src.type()==CV_8UC1)//black and white
    {
        cvtColor(src,image2show,COLOR_GRAY2RGB);
    }
    else if(src.type()==CV_8UC3)
    {
        image2show=src.clone();
    }
    for(const auto& fan : fans){
        Point2f verticles[4];
        fan.points(verticles);
        for()
    }
}