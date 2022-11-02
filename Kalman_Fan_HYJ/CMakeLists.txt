cmake_minimum_required(VERSION 3.5)

project(Kalman_Fan 
        LANGUAGE CXX)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

add_subdirectory(detect)
add_subdirectory(solve)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC  Flow R Sort Compensate kalman Target)


target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC  ${OpenCV_LIBS})