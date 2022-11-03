#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>

// onnxruntime
#include <assert.h>
#include <vector>
#include <onnxruntime_cxx_api.h>

using namespace std;
using namespace cv;

int main()
{
    string label[] = {"0", "1", "2", "3", "4", "5"};
    //###############################c++ 调用 Onnx#####################################
    // c++ 调用onnx的推理结果
    // opencv 推理
    dnn::Net net = dnn::readNetFromONNX("../Lenet.onnx");                                                       // 加载训练好的识别模型
    Mat image = imread("../1503.png");                                                                          // 读取图片
    Mat blob = dnn::blobFromImage(image, double (1.0 / 255.0), Size(32, 32), false, true); // 由图片加载数据 这里还可以进行缩放、归一化等预处理
    net.setInput(blob);                                                                                         // 设置模型输入
    Mat predict = net.forward();                                                                                // 推理出结果
    double minValue, maxValue;                                                                                  // 最大值，最小值
    Point minIdx, maxIdx;                                                                                       // 最小值坐标，最大值坐标
    minMaxLoc(predict, &minValue, &maxValue, &minIdx, &maxIdx);                                             
    string output = label[maxIdx.x];
    cout << "output :" << output << endl;

    return 0;
}
