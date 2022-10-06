#include "R.hpp"
#include "Flow.hpp"
#include "target.hpp"


int main()
{
    Filter FL;
    Flow _flow;
    target tr;
    Mat src;
    string path = "../energy.avi";
    VideoCapture cap(path);
    while (cap.read(src))
    {
        imshow("original", src);
        waitKey(50);
        Mat info_img = src.clone();
        // static Mat src_armor=src.clone();
        FL.initImage(src);
        _flow.run(src);
        FL.run(src);
        tr.setTarget(src,FL.Rcontours, _flow.Fcontours);
    }
    return 1;
}

