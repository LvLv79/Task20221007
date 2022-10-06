#include "Armor.hpp"

void ArmorDetect::ArmorDilate(Mat &src)
{
    Mat element1 = getStructuringElement(MORPH_RECT, Size(5, 5));   //设置内核1
    Mat element2 = getStructuringElement(MORPH_RECT, Size(25, 25)); //设置内核2
    morphologyEx(src, src, MORPH_OPEN, element1);                   //开运算
    floodFill(src, Point(0, 0), Scalar(0));                         //漫水
    morphologyEx(src, src, MORPH_CLOSE, element2);                  //闭运算
}

int ArmorDetect::findArmors(const Mat &src)
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
    vector<Vec4i> A_hierarchy;
    ArmorDilate(src_bin);
    findContours(src_bin, contours, A_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE); //找轮廓
    int area[25] = {0};
    for (auto contour : contours)
    {
        double cur_area = contourArea(contour);
        if (cur_area < 2000)
        {
            continue; // only end one cycle
        }
        Armorcontours.emplace_back(minAreaRect(contour));
    }
    return static_cast<int>(Armorcontours.size());
}

void ArmorDetect::showArmors(string windows_name, const Mat &src)
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
    for (const auto &Armorcontour : Armorcontours)
    {
        Point2f vertices[4];           //定义矩形的4个顶点
        Armorcontour.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    imshow(windows_name, image2show);
}

void ArmorDetect::clearAll()
{
    Armorcontours.clear();
}

void ArmorDetect::run(const Mat &src)
{
    clearAll();
    findArmors(src);
    showArmors("Armors", src);
}