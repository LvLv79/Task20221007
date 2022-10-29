#include "init.hpp"
#include "exchange.hpp"
#include "ArmorBox.hpp"
#include "sort.hpp"

int main()
{
    init Init;
    Exchange Rect;
    Rect_Points RB;
    Sort corner;
    Mat src;
    string path = "../exchange.avi";
    VideoCapture cap(path);
    while (cap.read(src))
    {
        imshow("original", src);
        if (waitKey(50) == 27)
        {
            if (waitKey(0) == 27)
            {
                break;
            }
        }
        Mat info_img = src.clone();
        Init.initImage(src);
        Rect.run(src);
        RB.run(Rect.exchange_contours, src);
        corner.run(RB.rect_center, Rect.corner_contours, info_img);
    }
    return 1;
}