#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "AngleSolver.hpp"
#include "../Camera/Camera.hpp"

AngleSolver::AngleSolver()
{
}
AngleSolver::~AngleSolver()
{
}

Point3d AngleSolver::solveAngles(vector<Point3f> POINTS_3D,vector<Point2f> POINTS_2D,Point2f center)
{
	Cam p1;
	p1.Cam_Init();
	Mat _rvec;
	if(POINTS_2D.empty())
	{
		cout<<"NO POINTS FOUND"<<endl;
	}
	else
	{
		Mat _rvec, tVec, _rmat;
		solvePnP(POINTS_3D, POINTS_2D, p1.cameraMatrix, p1.distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);

		GUN_CAM_DISTANCE_Y = 0;
		tVec.at<double>(1, 0) -= GUN_CAM_DISTANCE_Y;
		double x_pos = tVec.at<double>(0, 0);
		double y_pos = tVec.at<double>(1, 0);
		double z_pos = tVec.at<double>(2, 0);
		distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
		// cout<<"bbbbbbb"<<distance<<endl;
		// cout<<tVec<<endl;
		PNP.x = x_pos;
		PNP.y = y_pos;
		PNP.z = z_pos;

		Rodrigues(_rvec, _rmat);
		_rmat.convertTo(_rmat, CV_64FC1);
		tVec.convertTo(tVec, CV_64FC1);

		Eigen::Matrix3d rotated_matrix;
		cv2eigen(_rmat,rotated_matrix);

		Eigen::Vector3d euler_angles = rotated_matrix.eulerAngles(0,1,2);
		double x_pitch = euler_angles[0]* 180.f / CV_PI;
		double y_yaw = (euler_angles[1]* 180.f / CV_PI)/10;
		double z_row = (euler_angles[2]* 180.f / CV_PI)/10;

		double cy = cos(y_yaw * 0.5);
		double sy = sin(y_yaw * 0.5);
		double cp = cos(x_pitch * 0.5);
		double sp = sin(x_pitch * 0.5);
		double cr = cos(z_row * 0.5);
		double sr = sin(z_row * 0.5); 

		x = cr * cp * cy + sr * sp * sy;
		w = cr * sp * cy + sr * cp * sy;
		y = cr * cp * sy - sr * sp * cy;
		z = cr * cp * cy + sr * sp * sy;

		// w = cr * cp * cy + sr * sp * sy;
		// x = sr * cp * cy - cr * sp * sy;
		// y = cr * sp * cy + sr * cp * sy;
		// z = cr * cp * sy - sr * sp * cy;
		
		cout << "/////////////////////////////////////" << endl;
		cout << "x_pitch:" << x_pitch << endl;
		cout << "y_yaw:" << y_yaw << endl;
		cout << "z_row:" << z_row << endl;
		cout << "w:" << w << endl;
		cout << "x:" << x << endl;
		cout << "y:" << y << endl;
		cout << "z:" << z << endl;
		cout << "PNP" << PNP << endl;
		cout << "/////////////////////////////////////" << endl;
	}
	return PNP;
}



