cmake_minimum_required(VERSION 3.5)

project(Kalman_Fan CXX)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(detect)
add_subdirectory(solve)


add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC  Flow R Target)