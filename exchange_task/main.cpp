#include"init.hpp"
#include"exchange.hpp"
#include"ArmorBox.hpp"

int main(){
    init Init;
    Exchange Rect;
    Rect_Points RB;
    Mat src;
    string path = "../exchange.avi";
    VideoCapture cap(path);
    while (cap.read(src))
    {
        imshow("original", src);
        waitKey(100);
        Mat info_img = src.clone();
        // static Mat src_armor=src.clone();
        //namedWindow("二值化");
        //createTrackbar("e and d","init",0,10,)
        Init.initImage(src);
        Rect.run(src);
        RB.sort_points(Rect.exchange_contours);
        //imshow("init",src);
    }
    return 1;
}