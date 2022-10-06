#include "R.hpp"

int Filter::findR(const Mat &src)
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
    RDilate(src_bin);
    findContours(src_bin, contours, R_hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    vector<vector<Point>> valid_child_contours;
    for (int i = 0; i < contours.size(); ++i)
    {

        auto hierarchy = R_hierarchy[i];
        if ((hierarchy[0] != -1 ||
             hierarchy[1] != -1) &&
            hierarchy[2] == -1 &&
            hierarchy[3] == -1)
        {
            valid_child_contours.push_back(contours[i]);
        }
    }
    for (auto contour : valid_child_contours)
    {
        if (!isValidR(contour))
        {
            continue; // only end one cycle
        }
        Rcontours.emplace_back(minAreaRect(contour));
    }
    return static_cast<int>(Rcontours.size());
}

/**
 * @brief judge whether R is valid
 *
 * @param Rcontour contour of the R
 * @return flag
 */
bool Filter::isValidR(const vector<Point> Rcontour)
{
    double cur_contour_area = contourArea(Rcontour);
    if (cur_contour_area > Rcontour_max || cur_contour_area < Rcontour_min)
    {
        return false;
    }
    RotatedRect cur_rect = minAreaRect(Rcontour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    float length_width_ratio = length / width;
    if (length_width_ratio < Rcontour_hw_ratio_min || length_width_ratio > Rcontour_hw_ratio_max)
    {
        return false;
    }
    return true;
}

void Filter::RDilate(Mat &src)
{
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(4, 4));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(4, 4));

    erode(src, src, element_erode_1);
    dilate(src, src, element_dilate_1);
}

void Filter::initImage(Mat &src)
{
    vector<Mat> channels;
    split(src, channels);                                                         //分离通道
    threshold(channels.at(0) - channels.at(2), src, 100, 255, THRESH_BINARY); //二值化
    //  把一个3通道图像转换成3个单通道图像
}

void Filter::showR(const Mat &src)
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
    for (const auto &Rcontour : Rcontours)
    {
        Point2f vertices[4];       //定义矩形的4个顶点
        Rcontour.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    imshow("R", image2show);
}

void Filter::clearAll()
{
    Rcontours.clear();
}

void Filter::run(Mat&src){
    clearAll();
    findR(src);
    showR(src);

}




//activate:hierarchy[i][0]!=-1||hierarchy[i][1]!=1
//not-activate:hierarchy[i][0]=-1&&hierarchy[i][1]=1
