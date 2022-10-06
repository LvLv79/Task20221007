#include "general.hpp"

using namespace std;
using namespace cv;

void General::run(Mat &src)
{
    clearAll();
    initImage(src);
    //findArmors(src);
    /*if (!findFlowStripFan(src)) {//寻找图中流动条所在的扇叶
		if (!findFlowStripWeak(src)) return;
	}*/
    findFans(src);
    cout<<armors.size()<<endl;
    //showArmors("armors", src);
    //showFlowStripFan("flowstrip",src);
    showFans("Fans", src);
}
