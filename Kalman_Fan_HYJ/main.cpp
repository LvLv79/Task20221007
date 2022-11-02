#include "R.hpp"
#include "Flow.hpp"
#include "target.hpp"
#include "kalman.hpp"

int main()
{
    Filter FL;
    Flow _flow;
    target tr;
    Sort sort;
    Mat src;
    string path = "../energy.avi";
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
        // static Mat src_armor=src.clone();
        FL.initImage(src);
        _flow.run(src);
        FL.run(src);
        //sort.run(FL.Rcontours, _flow.Fcontours, src);
        tr.setTarget(src, FL.Rcontours, _flow.Fcontours);
    }
    return 1;
}