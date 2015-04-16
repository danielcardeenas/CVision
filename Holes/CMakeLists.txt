cmake_minimum_required(VERSION 2.8.4)
project(holes)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../libs)

set(SOURCE_FILES main.cpp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${holes_SOURCE_DIR})

set(LIB_FILES
    ../libs/Filters.cpp 
    ../libs/Filters.h 
    ../libs/Utils.cpp 
    ../libs/Utils.h
    ../libs/NewUtils.cpp
    ../libs/NewUtils.h
    ../libs/Neighborhood.cpp 
    ../libs/Neighborhood.h
    ../libs/Kernel.cpp 
    ../libs/Kernel.h
    ../libs/Coordinate.cpp 
    ../libs/Coordinate.h
    ../libs/Shape.cpp
    ../libs/Shape.h
    ../libs/Ellipse.cpp
    ../libs/Ellipse.h
    )
    
add_executable(holes ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(holes ${OpenCV_LIBS})