#include "exchange.hpp"

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
    vector<vector<Point>> valid_contours;
    for (auto contour : contours)
    {
        if (!isValidCorner(contour))
        {
            continue; // only end one cycle
        }
        exchange_contours.emplace_back(minAreaRect(contour));
    }
    return static_cast<int>(exchange_contours.size());
}

/*const Point2f Exchange::crossPointof(const Point2f& bl,const Point2f& tl,const Point2f& tr, const Point2f& br){
	float a1 = tr.y - bl.y;
	float b1 = tr.x - bl.x;
	float c1 = bl.x*tr.y - tr.x*bl.y;

	float a2 = br.y - tl.y;
	float b2 = br.x - tl.x;
	float c2 = tl.x*br.y - br.x*tl.y;

	float d = a1 * b2 - a2 * b1;

	if (d == 0.0){
		return Point2f(FLT_MAX, FLT_MAX);
	}
	else{
		return cv::Point2f((b2*c1 - b1 * c2) / d, (c1*a2 - c2 * a1) / d);
	}
}*/

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

bool Exchange::isValidCorner(const vector<Point> Cornercontour)
{
    /*double cur_contour_area = contourArea(Cornercontour);
    if (cur_contour_area > Rcontour_max || cur_contour_area < Rcontour_min)
    {
        return false;
    }*/
    RotatedRect cur_rect = minAreaRect(Cornercontour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    float length_width_ratio = length / width;
    if (length_width_ratio < Cornercontour_hw_ratio_min || length_width_ratio > Cornercontour_hw_ratio_max)
    {
        return false;
    }
    return true;
}

void Exchange::Draw(const Mat &src)
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
    for (const auto &exchange_contour : exchange_contours)
    {
        Point2f vertices[4];               //定义矩形的4个顶点
        exchange_contour.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    if (exchange_contours.size() == 4)
    {
        for (const auto &exchange_contour : exchange_contours)
        {
            center.emplace_back(exchange_contour.center);
        }

        for (int i = 0; i < 4; i++)
        {
            line(image2show, center[i], center[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }
        imshow("Exchange", image2show);
    }
}

void Exchange::clearAll()
{
    exchange_contours.clear();
}

void Exchange::run(const Mat &src)
{
    clearAll();
    findCorner(src);
    Draw(src);
    cout << exchange_contours.size() << endl;
}
