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
        Init.initImage(src);
        Rect.run(src);
        RB.run(Rect.exchange_contours,src);
        Init.Solve(RB.Rect_points);
    }
    return 1;
}