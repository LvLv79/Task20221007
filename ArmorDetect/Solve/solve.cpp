#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "solve.hpp"

AngleSolver::AngleSolver()
{
}

AngleSolver::~AngleSolver()
{
}

void AngleSolver::setArmorSize( double width, double height)
{
    POINTS_3D.clear();
	double half_x = width / 2.0;
	double half_y = height / 2.0;
	
	POINTS_3D.push_back(Point3f(-half_x, half_y, 0));   //tl top left
	POINTS_3D.push_back(Point3f(half_x, half_y, 0));	//tr top right
	POINTS_3D.push_back(Point3f(half_x, -half_y, 0));   //br below right
	POINTS_3D.push_back(Point3f(-half_x, -half_y, 0));  //bl below left

}

void AngleSolver::solveAngles(vector<Point2f> POINTS_2D, Point2f center)
{
    Mat _rvec;
    if (POINTS_2D.empty())
    {
        cout << "NO POINTS FOUND" << endl;
    }
    else
    {
        setArmorSize(230,63.5);
        double GUN_CAM_DISTANCE_Y = 0;
        Mat _rvec, tVec, _rmat;
        solvePnP(POINTS_3D, POINTS_2D, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);

        tVec.at<double>(1, 0) -= GUN_CAM_DISTANCE_Y;
        double x_pos = tVec.at<double>(0, 0);
        double y_pos = tVec.at<double>(1, 0);
        double z_pos = tVec.at<double>(2, 0);
        distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);

        double r_x = *_rvec.ptr(0);
        double r_y = *_rvec.ptr(1);
        double r_z = *_rvec.ptr(2);

        Rodrigues(_rvec, _rmat);
        _rmat.convertTo(_rmat, CV_64FC1);

        Eigen::Matrix3d rotated_matrix;

        cv2eigen(_rmat, rotated_matrix);
        Eigen::Vector3d euler_angles = rotated_matrix.eulerAngles(0, 1, 2);

        double x_pitch = euler_angles[0] * 180.f / CV_PI;
        double y_yaw = euler_angles[1] * 180.f / CV_PI;
        double z_row = euler_angles[2] * 180.f / CV_PI;

        PNP.x = x_pos;
        PNP.y = y_pos;
        PNP.z = z_pos;

        cout << "/////////////////////////////////////" << endl;
        cout << "x_pitch:" << x_pitch << endl;
        cout << "y_yaw:" << y_yaw << endl;
        cout << "z_row:" << z_row << endl;
        cout << "PNP" << PNP << endl;
        cout << "/////////////////////////////////////" << endl;
    }
}