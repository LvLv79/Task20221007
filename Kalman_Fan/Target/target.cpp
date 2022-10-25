#include "target.hpp"

/**
 * @brief show image
 *
 * @param src
 * @param Rcontours center_R
 * @param Fcontours TargetArmor
 */
void target::setTarget(Mat &src, vector<RotatedRect> Rcontours, vector<RotatedRect> Fcontours)
{
    if (src.empty())
        return;
    static Mat image2show;
    // cout<<src.size()<<endl;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    }
    else if (src.type() == CV_8UC3) // RGB 彩色
    {
        image2show = src.clone();
    }

    if (Rcontours.size() != 1 || Fcontours.size() != 1)
    {
        kf.is_initialized_ = false;
        putText(image2show, "", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false); // title NOT FOUND 大标题 “没找到装甲板”
    }
    else
    {
        center_R = Rcontours[0];
        targetArmor = Fcontours[0];

        Cam_Init();
        sort.find_below(targetArmor,center_R);
        //setImagePoints(targetArmor);
        setObjectPoints(armor_width, armor_height);
        calDistance(POINTS_3D, sort.Rect_points);
        calAngle(targetArmor, center_R);
        calR(center_R.center, targetArmor.center);
        kf.run(target_angle, 0, center_R.center, center2R);
        //gravity.run(targetArmor.center, 500, distance, target_h);
        Point2f A_vertices[4];
        Point2f R_vertices[4]; //定义矩形的4个顶点
        targetArmor.points(A_vertices);
        center_R.points(R_vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
        {
            line(image2show, A_vertices[i], A_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
            line(image2show, R_vertices[i], R_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }
        putText(image2show, "target_angle: " + to_string(target_angle), Point2f(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "distance: " + to_string(distance), Point2f(15, 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "predict_angle: " + to_string(kf.next_angle), Point2f(15, 45), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "0 ", sort.Rect_points[0], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "1 ", sort.Rect_points[1], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "2 ", sort.Rect_points[2], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "3 ", sort.Rect_points[3], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        circle(image2show, targetArmor.center, 2, Scalar(0, 255, 0), 2, 8, 0);
        circle(image2show, kf.predict_point, 2, Scalar(255, 255, 0), 2, 8, 0);
    }
    imshow("info", image2show);
}
/**
 * @brief calculate angles between Armor_center and center_R
 *
 * @param Armor targetArmor
 * @param R center_R
 */
void target::calAngle(RotatedRect Armor, RotatedRect R)
{
    target_angle = static_cast<float>(180 / 3.14 * atan2((-1 * (Armor.center.y - R.center.y)), (Armor.center.x - R.center.x)));
}

vector<Point2f> target::setImagePoints(RotatedRect Armor)
{
    Point2f armorVertices[4];
    Armor.points(armorVertices);

    POINTS_2D.emplace_back(armorVertices[1]);
    POINTS_2D.emplace_back(armorVertices[2]);
    POINTS_2D.emplace_back(armorVertices[3]);
    POINTS_2D.emplace_back(armorVertices[0]);
    return POINTS_2D;
}

vector<Point3f> target::setObjectPoints(double width, double height)
{
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    POINTS_3D.push_back(Point3f(-half_x, half_y, 0));  // tl top left
    POINTS_3D.push_back(Point3f(half_x, half_y, 0));   // tr top right
    POINTS_3D.push_back(Point3f(half_x, -half_y, 0));  // br below right
    POINTS_3D.push_back(Point3f(-half_x, -half_y, 0)); // bl below left

    return POINTS_3D;
}

/**
 * @brief calculate distance between camera and target
 *
 * @param SMALL_ARMOR_POINTS_3D coordinate in world
 * @param targetContour coordinate in image
 */
void target::calDistance(vector<Point3f> SMALL_ARMOR_POINTS_3D, vector<Point2f> targetContour)
{
    Mat _rvec, tVec, _rmat;
    solvePnP(SMALL_ARMOR_POINTS_3D, targetContour, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);
    double x_pos = *_rvec.ptr(0);
    double y_pos = *_rvec.ptr(1);
    double z_pos = *_rvec.ptr(2);
    tVec_x = *tVec.ptr(0);
    tVec_y = *tVec.ptr(1);
    tVec_z = *tVec.ptr(2);

    target_h = tVec_y;

    Rodrigues(_rvec, _rmat);
    _rmat.convertTo(_rmat, CV_64FC1);
    tVec.convertTo(tVec, CV_64FC1);
    Eigen::Matrix3d rotated_matrix;
    Eigen::Vector3d transfer_vector;

    cv2eigen(_rmat, rotated_matrix);
    cv2eigen(_rvec, transfer_vector);

    // get euler_angle
    Eigen::Vector3d eular_angles = rotated_matrix.eulerAngles(0, 1, 2);

    distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
}

void target::calR(Point2f A, Point2f B)
{
    center2R = sqrt(abs(A.x - B.x) * abs(A.x - B.x) + abs(A.y - B.y) * abs(A.y - B.y));
}

void target::Cam_Init()
{
    cameraMatrix.at<double>(0, 0) = 1.6041191539594568e+03;
    cameraMatrix.at<double>(0, 1) = 0;
    cameraMatrix.at<double>(0, 2) = 6.3983687194220943e+02;
    cameraMatrix.at<double>(1, 1) = 6.3983687194220943e+02;
    cameraMatrix.at<double>(1, 2) = 5.1222951297937527e+02;
    cameraMatrix.at<double>(2, 2) = 1.;

    distCoeffs.at<double>(0, 0) = -6.4910709385278609e-01;
    distCoeffs.at<double>(1, 0) = 8.6914328787426987e-01;
    distCoeffs.at<double>(2, 0) = 5.1733428362687644e-03;
    distCoeffs.at<double>(3, 0) = -4.1111054148847371e-03;
    distCoeffs.at<double>(4, 0) = 0;

    return;
}
