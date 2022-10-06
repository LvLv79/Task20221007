#include "R.hpp"
#include "Flow.hpp"
#include "Armor.hpp"
#include "target.hpp"

int main()
{
    Filter FL;
    Flow _flow;
    ArmorDetect ad;
    target tr;
    Mat src;
    string path = "/home/lvlv/Desktop/fanPratice/energy.avi";
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
        if (tr.setTarget(FL.Rcontours, _flow.Fcontours) == 0)
        {
            cout << "Armor Not Found!" << endl;
        }
        else
        {
            tr.calAngle(tr.targetArmor,tr.center_R);
            cout<<tr.target_angle<<endl;

        }
    }
    return 1;
}
