#include "general.hpp"   //init hpp
extern McuData mcu_data; //一个c文件需要调用另一个c文件里的变量或者函数，而不能从.h文件中调用变量

General::General()
{
    initEnergy();
    initEnergyParam();
}

void General::initEnergy()
{
    show_img = true;
    // show_process = false;
    show_wrong = false;
    show_data = true;

    fans_cnt = 0;
    last_fans_cnt = 0;
}

void General::initEnergyParam()
{
    wm_data.BLUE_GRAY_THRESH = 100; //敌方蓝色时的阈值
    wm_data.RED_GRAY_THRESH = 180;  //敌方红色时的阈值

    wm_data.flow_strip_fan_contour_area_max = 2000;
    wm_data.flow_strip_fan_contour_area_min = 500;
    wm_data.flow_strip_fan_contour_length_max = 100;
    wm_data.flow_strip_fan_contour_length_min = 60;
    wm_data.flow_strip_fan_contour_width_max = 52;
    wm_data.flow_strip_fan_contour_width_min = 20;
    wm_data.flow_strip_fan_contour_hw_ratio_max = 2.8;
    wm_data.flow_strip_fan_contour_hw_ratio_min = 1.2;
    wm_data.flow_strip_fan_contour_area_ratio_max = 0.58;
    wm_data.flow_strip_fan_contour_area_ratio_min = 0.34;

    wm_data.flow_strip_contour_area_max = 700;
    wm_data.flow_strip_contour_area_min = 50;
    wm_data.flow_strip_contour_length_max = 55;
    wm_data.flow_strip_contour_length_min = 40;
    wm_data.flow_strip_contour_width_max = 20;
    wm_data.flow_strip_contour_width_min = 4;
    wm_data.flow_strip_contour_hw_ratio_max = 7;
    wm_data.flow_strip_contour_hw_ratio_min = 3;
    wm_data.flow_strip_contour_area_ratio_min = 0.6;
    wm_data.flow_strip_contour_intersection_area_min = 100;

    wm_data.Strip_Fan_Distance_max = 56; //流动条到装甲板距离参数
    wm_data.Strip_Fan_Distance_min = 28;

    wm_data.armor_contour_width_max = 52;
    wm_data.armor_contour_width_min = 20;
    wm_data.armor_contour_hw_ratio_max = 2.8;
    wm_data.armor_contour_hw_ratio_min = 1.2;
    wm_data.flow_strip_fan_contour_area_ratio_max = 0.58;
    wm_data.flow_strip_fan_contour_area_ratio_min = 0.34;

    wm_data.armor_contour_area_max = 2000;
    wm_data.armor_contour_area_min = 20;
    wm_data.armor_contour_length_max = 50;
    wm_data.armor_contour_length_min = 20;
    wm_data.armor_contour_width_max = 35;
    wm_data.armor_contour_width_min = 0;
    wm_data.armor_contour_hw_ratio_max = 2;
    wm_data.armor_contour_hw_ratio_min = 1.5;

    wm_data.flow_area_max = 8000; //扇叶筛选相关参数
    wm_data.flow_area_min = 1500;
    wm_data.flow_length_max = 100;
    wm_data.flow_length_min = 45;
    wm_data.flow_width_max = 52;
    wm_data.flow_width_min = 10;
    wm_data.flow_aim_max = 3.5;
    wm_data.flow_aim_min = 1.2;
    wm_data.flow_area_ratio_min = 0.6;
}

void General::clearAll()
{
    armors.clear();
    fans.clear();
}

void General::initImage(Mat &src)
{
    if (src.type() == CV_8UC3)
    {
        cvtColor(src, src, COLOR_BGR2GRAY); // why repeated in fandetect?
    }
    threshold(src, src, wm_data.BLUE_GRAY_THRESH, 255, THRESH_BINARY);
    /*if (mcu_data.enemy_color == ENEMY_RED)
    {
        threshold(src, src, wm_data.RED_GRAY_THRESH, 255, THRESH_BINARY);
    }*/
    // show process
    // if (show_energy || show_process)waitKey(1);??????
}