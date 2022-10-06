#include "general.hpp"

int General::findArmors(const Mat &src)
{
    if (src.empty())
    {
        // if(show_wrong)cout<<"empty!"<<endl;
        return 0;
    }
    static Mat dst;
    dst = src.clone();
    if (src.type() == CV_8UC3)
    {
        cvtColor(dst, dst, COLOR_BGR2GRAY);
    }
    vector<vector<Point>> armors_contours;
    vector<Vec4i> hierarchys;
    vector<vector<Point>> armors_contours_externel;
    ArmorDilate(dst);
    findContours(dst, armors_contours, 1, 1); // CV_RETR_LIST：检索所有的轮廓，并将其放入list中
    findContours(dst, armors_contours_externel, 0, 1);                            // CV_RETR_EXTERNAL：只检索最外面的轮廓；
    //去除外轮廓
    
    for (int i = 0; i < armors_contours_externel.size(); i++)
    {
        int external_contour_size = armors_contours_externel[i].size(); // pick one external
        for (int j = 0; j < armors_contours.size(); j++)
        {
            int all_size = armors_contours[j].size(); // compare with all contours
            if (external_contour_size == all_size)
            {
                swap(armors_contours[j], armors_contours[armors_contours.size() - 1]);
                armors_contours.pop_back(); //清除掉流动条
                break;                      // just one would fit, if found, then break
            }
        }
    }

    for (auto armor_contour : armors_contours)
    {
        if (!isValidArmorContour(armor_contour))
        {
            continue; // only end one cycle
        }
        armors.emplace_back(minAreaRect(armor_contour));
    }
    return static_cast<int>(armors.size());
}

bool General::isValidArmorContour(const vector<Point> &armor_contour)
{
    double cur_contour_area = contourArea(armor_contour);
    if (cur_contour_area > wm_data.armor_contour_area_max || cur_contour_area < wm_data.armor_contour_area_min)
    {
        return false;
    }
    RotatedRect cur_rect = minAreaRect(armor_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
    float width = cur_size.height > cur_size.width ? cur_size.width : cur_size.height;
    /*if (length < wm_data.armor_contour_length_min || length > wm_data.armor_contour_length_max || width < wm_data.armor_contour_width_min || width > wm_data.armor_contour_width_max)
    {
        return false;
    }*/
    float length_width_ratio = length / width;
    if (length_width_ratio < wm_data.armor_contour_hw_ratio_min || length_width_ratio > wm_data.armor_contour_hw_ratio_max)
    {
        return false;
    }
    return true;
}

void General::showArmors(string windows_name, const Mat &src)
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
    for (const auto &armor : armors)
    {
        Point2f vertices[4];    //定义矩形的4个顶点
        armor.points(vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    imshow(windows_name, image2show);
}

/*for (int i = 0; i < armors_contours.size(); ++i)
    {
        armors_contours[i];
        auto hierarchy = hierarchys[i];
        if (hierarchy[2] == -1 &&
            hierarchy[3] != -1)
        {
            continue;
        }
    }*/
