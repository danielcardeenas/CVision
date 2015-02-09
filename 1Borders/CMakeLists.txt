cmake_minimum_required(VERSION 2.8.4)
project(Borders)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../libs)

set(SOURCE_FILES main.cpp)

set(LIB_FILES
    ../libs/Filters.cpp 
    ../libs/Filters.h 
    ../libs/Utils.cpp 
    ../libs/Utils.h
    ../libs/Coordinate.cpp 
    ../libs/Coordinate.h
    )
    
add_executable(Borders ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(Borders ${OpenCV_LIBS})