#include"general.hpp"
extern McuData mcu_data;//一个c文件需要调用另一个c文件里的变量或者函数，而不能从.h文件中调用变量

General::General(){
    initEnergy();
    initEnergyParam();
}
General::~General()=default;

void General::initEnergy(){
    last_fans_cnt = 0;
}

void General::initEnergyParam(){
    wm_data.BLUE_GRAY_THRESH = 100;//敌方蓝色时的阈值
    wm_data.RED_GRAY_THRESH = 180;//敌方红色时的阈值

    wm_data.flow_area_max = 5000;//扇叶筛选相关参数
    wm_data.flow_area_min = 1500;
    wm_data.flow_length_max =100;
    wm_data.flow_length_min = 45;
    wm_data.flow_width_max = 52;
    wm_data.flow_width_min = 10;
    wm_data.flow_aim_max=3.5;
    wm_data.flow_aim_min=1.2;
    wm_data.flow_area_ratio_min=0.6;
}