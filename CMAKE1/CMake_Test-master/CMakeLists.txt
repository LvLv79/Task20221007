# 在此处进行 CMake 设置（最小版本号，项目名）
cmake_minimum_required(VERSION 3.5)

project(TEST CXX)

find_package(OpenCV REQUIRED)
####### 以下禁止修改 #######
add_subdirectory(common)   #
add_subdirectory(modules)  #
####### 以上禁止修改 #######
set(CMAKE_BUILD_TYPE Debug)
# 在此处生成可执行程序
add_executable(TEST main.cpp)
# 在此处链接库
target_link_libraries(TEST math A1 A2 M1 M2)