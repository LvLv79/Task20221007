#include"general.hpp"

//----------------------------------------------------------------------------------------------------------------------
// 此函数用于计算两点之间距离
// ---------------------------------------------------------------------------------------------------------------------
double General::pointDistance(cv::Point point_1, cv::Point point_2) {
	double distance = 0;
	distance = sqrt(pow(static_cast<double>(point_1.x - point_2.x), 2) + pow(static_cast<double>(point_1.y - point_2.y), 2));
	return distance;
}
