cmake_minimum_required(VERSION 3.5)

project(HNH CXX)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    main.cpp
    kalman/kalman.cpp
    kalman/kalman.hpp
    Flow/Flow.cpp
    Flow/Flow.hpp
    R/R.cpp
    R/R.hpp
    Target/target.cpp
    Target/target.hpp
)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})
