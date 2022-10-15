#include "init.hpp"

void init::initImage(Mat &src)
{
    vector<Mat> channels;
    split(src, channels);                                                     //分离通道
    threshold(channels.at(0) - channels.at(2), src, 100, 255, THRESH_BINARY); //二值化
    int structElementSize = 3;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    dilate(src, src, element);
    structElementSize = 2;
    element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
    morphologyEx(src, src, MORPH_RECT, element);
    //  把一个3通道图像转换成3个单通道图像
}