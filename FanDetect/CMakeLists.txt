cmake_minimum_required(VERSION 3.5)

project(fanDetect CXX)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME}
    general.hpp
    param_define.hpp
    fanDetect.cpp
    Dilate.cpp
    run.cpp
    Init.cpp
    armor.cpp
    main.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})
