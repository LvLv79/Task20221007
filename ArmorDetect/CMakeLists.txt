cmake_minimum_required(VERSION 3.5)

project(HNH CXX)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    main.cpp
    Armor/Armor.hpp
    Armor/ArmorDetector.cpp
    Armor/findLights.cpp
    Armor/lightBar.cpp
    Armor/matchArmors.cpp
    Armor/armorBox.cpp
    Solve/solve.hpp
    Solve/solve.cpp
)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})
