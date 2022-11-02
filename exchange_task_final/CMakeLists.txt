cmake_minimum_required(VERSION 3.5)

project(Exchange CXX)

add_subdirectory(detect)
add_subdirectory(solve)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} ArmorBox exchange init sort)