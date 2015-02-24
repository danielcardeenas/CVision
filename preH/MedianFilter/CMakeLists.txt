cmake_minimum_required(VERSION 2.8.4)
project(median)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${median_SOURCE_DIR})

include_directories(../../libs)

set(SOURCE_FILES main.cpp)

set(LIB_FILES
    ../../libs/Filters.cpp 
    ../../libs/Filters.h 
    ../../libs/Utils.cpp 
    ../../libs/Utils.h
    ../../libs/Neighborhood.cpp 
    ../../libs/Neighborhood.h
    ../../libs/Kernel.cpp 
    ../../libs/Kernel.h
    ../../libs/Coordinate.cpp 
    ../../libs/Coordinate.h
    ../../libs/Shape.cpp
    ../../libs/Shape.h
    )

add_executable(median ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(median ${OpenCV_LIBS})