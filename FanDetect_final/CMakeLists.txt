cmake_minimum_required(VERSION 3.5)

project(fanDetect CXX)

find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    R.cpp
    R.hpp
    main.cpp
    Flow.cpp
    Flow.hpp
    target.cpp
    target.hpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})