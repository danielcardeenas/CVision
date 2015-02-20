#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"
#include "Coordinate.h"

class Shape {
    private:
        std::vector<Coordinate> body;
        std::string name;
        Coordinate centerOfMass;
        cv::Vec3b color;
        std::vector<Coordinate> box;
        int sumX = 0;
        int sumY = 0;
        int q = 0;
    public:
        Shape();
        Shape(std::string name);
        void addCoordinate(Coordinate point);
        void setName(std::string name);
        void setCenterOfMass(Coordinate center);
        void putValues(int sumX, int sumY, int q);
        void calculateCenter();
        Coordinate getCenterofMass();
        std::vector<Coordinate> getBoundingBox();
        std::string getName();
        std::string getID();

};
#endif // __SHAPE_H_INCLUDED__