cmake_minimum_required(VERSION 3.5)

project(TEST)

add_subdirectory(common)   
add_subdirectory(modules)  

set(CMAKE_BUILD_TYPE Debug)

add_executable(TEST main.cpp)

target_link_libraries(TEST math A1 A2 M1 M2)
