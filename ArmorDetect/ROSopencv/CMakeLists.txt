cmake_minimum_required(VERSION 3.5)

project(ROSopencv CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    Armor/ArmorDetect.cpp
    Armor/ArmorDetect.hpp
    Pose/AngleSolver.cpp
    Pose/AngleSolver.hpp
    Camera/Camera.cpp
    Camera/Camera.hpp
)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})
