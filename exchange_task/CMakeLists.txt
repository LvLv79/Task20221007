cmake_minimum_required(VERSION 3.5)

project(exchange CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    exchange.cpp
    exchange.hpp
    init.hpp
    init.cpp
    sort.cpp
    sort.hpp
    ArmorBox.cpp
    ArmorBox.hpp
)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS})
