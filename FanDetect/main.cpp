#include"general.hpp"

int main()
{
    General G;
    Mat src;
    string path = "../energy.avi";
    VideoCapture cap(path);
    while(cap.read(src))
    {
        imshow("original", src);
        waitKey(20);
        G.run(src);
    }
    return 1;
}