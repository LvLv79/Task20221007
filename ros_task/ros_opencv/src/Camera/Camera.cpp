#include "Camera.hpp"

cv::VideoCapture inputVideo("/home/lvlv/Task_ROS/HNH_ros_test/HNH_test/src/ros_opencv/src/1.avi");
void Cam::Cam_Init()
{
    
    return;
}

bool Cam::getImage()
{
    if (!inputVideo.isOpened())
    {
        std::cout << "Could not open the input video: " << std::endl;
        return false;
    }
    else
    {
        inputVideo.read(InitImg);
        return true;
    }
}
void Cam::imgAdjust()
{
    cv::Mat map1, map2;
    cv::Size imageSize;
    imageSize = InitImg.size();
    initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(),
                            getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
                            imageSize, CV_16SC2, map1, map2);
    // check if at end
    remap(InitImg, AdjustedImg, map1, map2, cv::INTER_LINEAR);
    return;
}
