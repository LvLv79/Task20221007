#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>


#define UNIT_PIXEL_W 0.000375
#define UNIT_PIXEL_H 0.000375
using namespace cv;
using namespace std;

class AngleSolver
{
public:
	AngleSolver();
	~AngleSolver();



	/**
	* @brief solve the angles using P4P or PinHole according to the distance
	*/
	Point3d solveAngles(vector<Point3f> POINTS_3D,vector<Point2f> POINTS_2D,Point2f center);



	// calculated by solvePnP
	//s[R|t]=s'  s->world coordinate;s`->camera coordinate
	//Mat rVec;    //rot rotation between camera and target center
	//Mat tVec;  //trans tanslation between camera and target center

	//Results
	double distance;
	Point3d PNP;

	double w;
	double x;
	double y;
	double z;


private:
    double GUN_CAM_DISTANCE_Y=-6;
	
};
