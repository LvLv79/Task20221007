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
        putText(image2show, "", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false); // title NOT FOUND 大标题 “没找到装甲板”
    }
    else
    {
        center_R = Rcontours[0];
        targetArmor = Fcontours[0];

        Cam_Init();
        setImagePoints(targetArmor);
        setObjectPoints(armor_width, armor_height);
        calDistance(POINTS_3D, POINTS_2D);
        calAngle(targetArmor, center_R);
        Point2f A_vertices[4];
        Point2f R_vertices[4]; //定义矩形的4个顶点
        targetArmor.points(A_vertices);
        center_R.points(R_vertices); //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
        {
            line(image2show, A_vertices[i], A_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
            line(image2show, R_vertices[i], R_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }
        putText(image2show, to_string(target_angle), center_R.center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        circle(image2show, targetArmor.center, 2, Scalar(0, 255, 0), 2, 8, 0);
        putText(image2show, to_string(distance), targetArmor.center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
        
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
        Mat _rvec, tVec;
        solvePnP(SMALL_ARMOR_POINTS_3D, targetContour, cameraMatrix, distCoeffs, _rvec, tVec, false, SOLVEPNP_ITERATIVE);
        double x_pos = tVec.at<double>(0, 0);
        double y_pos = tVec.at<double>(1, 0);
        double z_pos = tVec.at<double>(2, 0);
        distance = sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
    }

    void target::Cam_Init()
    {
        cameraMatrix.at<double>(0, 0) = 1.1527e+03;
        cameraMatrix.at<double>(0, 1) = 0;
        cameraMatrix.at<double>(0, 2) = 618.6327;
        cameraMatrix.at<double>(1, 1) = 1.1527e+03;
        cameraMatrix.at<double>(1, 2) = 361.1508;

        distCoeffs.at<double>(0, 0) = 0.0741;
        distCoeffs.at<double>(1, 0) = -0.0685;
        distCoeffs.at<double>(2, 0) = 0;
        distCoeffs.at<double>(3, 0) = 0;
        distCoeffs.at<double>(4, 0) = 0;

        return;
    }
    // putText(armorDisplay, to_string(int(armor.center.x)), armor.center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
    // putText(armorDisplay, "ARMOR NOT FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false);//title NOT FOUND 大标题 “没找到装甲板”
