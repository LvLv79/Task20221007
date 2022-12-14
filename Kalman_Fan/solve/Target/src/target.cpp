#include "target.hpp"

/**
 * @brief 显示debug信息
 * @param src
 * @param Rcontours R标
 * @param Fcontours 目标装甲板
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
        sort.run(targetArmor, center_R);
        setObjectPoints(armor_width, armor_height);
        calDistance(POINTS_3D, sort.Rect_points);
        calAngle(targetArmor, center_R);
        calR(center_R.center, targetArmor.center);
        kf.run(target_angle, 0, center_R.center, center2R);
        gravity.run(targetArmor.center, 50, distance, target_h);
        Point2f A_vertices[4];
        Point2f R_vertices[4]; //定义矩形的4个顶点
        targetArmor.points(A_vertices);
        center_R.points(R_vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
        {
            line(image2show, A_vertices[i], A_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
            line(image2show, R_vertices[i], R_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }
        putText(image2show, "target_angle: " + to_string(kf.adjust_angle), Point2f(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "distance: " + to_string(distance), Point2f(15, 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "predict_angle: " + to_string(kf.next_angle), Point2f(15, 45), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "target_angle: " + to_string((gravity.compensate_angle)/10), Point2f(15, 60), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        // putText(image2show, "predict_point: " + to_string(kf.predict_point.x)+"  "+to_string(kf.predict_point.y), Point2f(15, 60), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        putText(image2show, "0 ", sort.Rect_points[0], FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2, 8, false);
        putText(image2show, "1 ", sort.Rect_points[1], FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2, 8, false);
        putText(image2show, "2 ", sort.Rect_points[2], FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2, 8, false);
        putText(image2show, "3 ", sort.Rect_points[3], FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2, 8, false);
        circle(image2show, targetArmor.center, 2, Scalar(0, 255, 0), 2, 8, 0);
        if (kf.cur_angle < 10 && abs(targetArmor.center.x - kf.predict_point.x) < 10 && abs(targetArmor.center.y - kf.predict_point.y) < 10)
        {
            circle(image2show, kf.predict_point, 2, Scalar(0, 0, 255), 2, 8, 0);
        }
        // cout << "target_center: " << targetArmor.center << endl;
        // cout << "predict_point: " << kf.predict_point << endl;
        cout << "/////////////////////////////////////////////////////////////" << endl;
    }
    imshow("info", image2show);
}

/**
 * @brief 计算装甲板坐标点与R标的夹角
 *
 * @param Armor targetArmor
 * @param R center_R
 */
void target::calAngle(RotatedRect Armor, RotatedRect R)
{
    target_angle = static_cast<float>(180 / 3.14 * atan2((-1 * (Armor.center.y - R.center.y)), (Armor.center.x - R.center.x)));
}

/**
 * @brief 设置传入点的世界坐标系
 * 
 * @param width 装甲板真实宽度
 * @param height 装甲板真实长度
 * @return vector<Point3f> 
 */
vector<Point3f> target::setObjectPoints(double width, double height)
{
    POINTS_3D.clear();
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    POINTS_3D.push_back(Point3f(-half_x, half_y, 0));  // tl top left
    POINTS_3D.push_back(Point3f(half_x, half_y, 0));   // tr top right
    POINTS_3D.push_back(Point3f(half_x, -half_y, 0));  // br below right
    POINTS_3D.push_back(Point3f(-half_x, -half_y, 0)); // bl below left

    return POINTS_3D;
}

/**
 * @brief 计算装甲板到相机的距离
 *
 * @param SMALL_ARMOR_POINTS_3D 世界坐标系的点
 * @param targetContour 图像坐标系的点
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

    target_h = abs(tVec_y);
    cout << "target_h :" << target_h << endl;

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

/**
 * @brief 计算装甲板到R标的距离
 * 
 * @param A 
 * @param B 
 */
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
