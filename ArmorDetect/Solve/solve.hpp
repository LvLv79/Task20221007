//#ifndef ARMOR
//#define ARMOR

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

using namespace cv;
using namespace ml;
using namespace std;

class AngleSolver
{
public:
    AngleSolver();
    ~AngleSolver();



    /**
     * @brief solve the angles using P4P or PinHole according to the distance
     */
    void solveAngles(vector<Point2f> POINTS_2D, Point2f center);

    void setArmorSize( double width, double height);

    // Results
    double distance;
    Point3d PNP;
    vector<Point3f> POINTS_3D;

private:
    cv::Matx<float, 3, 3> cameraMatrix = {1.6041191539594568e+03, 0., 6.3983687194220943e+02, 0.,
                                          1.6047833493341714e+03, 5.1222951297937527e+02, 0., 0., 1.};
    cv::Matx<float, 5, 1> distCoeffs = {-6.4910709385278609e-01, 8.6914328787426987e-01,
                                        5.1733428362687644e-03, -4.1111054148847371e-03, 0.};
};

//#endif