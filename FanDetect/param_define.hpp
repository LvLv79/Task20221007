#include <iostream>

struct WindmillParam
{
    int RED_GRAY_THRESH;
    int BLUE_GRAY_THRESH;

    float armor_contour_area_max;
    float armor_contour_area_min;
    float armor_contour_length_max;
    float armor_contour_length_min;
    float armor_contour_width_max;
    float armor_contour_width_min;
    float armor_contour_hw_ratio_max;
    float armor_contour_hw_ratio_min;


    float flow_area_max;
    float flow_area_min;
    float flow_length_max;
    float flow_length_min;
    float flow_width_max;
    float flow_width_min;
    float flow_aim_max;
    float flow_aim_min;
    float flow_area_ratio_min;
};

struct McuData
{
    uint8_t enemy_color; // char
};