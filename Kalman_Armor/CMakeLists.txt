cmake_minimum_required(VERSION 3.5)

project(Kalman_Armor)

add_subdirectory(Armor)
add_subdirectory(kalman)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} Armor kalman)