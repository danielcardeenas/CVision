cmake_minimum_required(VERSION 2.8.4)
project(objects)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../libs)

set(SOURCE_FILES main.cpp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${objects_SOURCE_DIR})

set(LIB_FILES
    ../libs/Filters.cpp 
    ../libs/Filters.h 
    ../libs/Utils.cpp 
    ../libs/Utils.h
    ../libs/Neighborhood.cpp 
    ../libs/Neighborhood.h
    ../libs/Kernel.cpp 
    ../libs/Kernel.h
    ../libs/Coordinate.cpp 
    ../libs/Coordinate.h
    ../libs/Shape.cpp
    ../libs/Shape.h
    )
    
add_executable(objects ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(objects ${OpenCV_LIBS})