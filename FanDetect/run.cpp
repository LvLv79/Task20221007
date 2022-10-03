#include "general.hpp"

using namespace std;
using namespace cv;

void General::run(Mat &src)
{
    clearAll();
    initImage(src);
    if (show_process)
        imshow("bin", src);
    fans_cnt = findFans(src);
    if (findArmors(src) < 1)
        return;
    // cout<<fans_cnt<<endl;
    showArmors("armors", src);
}
