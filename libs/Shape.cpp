#include "Shape.h"

Shape::Shape(){}

Shape::Shape(std::string name) {
    this->name = name;
}

void Shape::addCoordinate(Coordinate point) {
    this->body.push_back(point);
}
void Shape::setName(std::string name) {
    this->name = name;
}
void Shape::setCenterOfMass(Coordinate center) {
    this->centerOfMass = center;
}

void Shape::putValues(int sumX, int sumY, int q) {
    this->sumX += sumX;
    this->sumY += sumY;
    this->q = q;
}

// TODO: code the actual formula
void Shape::calculateCenter() {
    this->sumX /= this->q;
    this->sumY /= this->q;

    this->centerOfMass = Coordinate(sumX, sumY);
}

Coordinate Shape::getCenterofMass() {
    return this->centerOfMass;
}

std::vector<Coordinate> Shape::getBoundingBox() {

    std::vector<Coordinate> box;

    std::vector<int> allX;
    std::vector<int> allY;
    for(Coordinate &coo : this->body)
    {
        allX.push_back(coo.x);
        allY.push_back(coo.y);
    }

    // Find min elements (X, Y)
    std::vector<int>::iterator minX, minY, maxX, maxY;
    minX = std::min_element(std::begin(allX), std::end(allX));
    minY = std::min_element(std::begin(allY), std::end(allY));

    maxX = std::max_element(allX.begin(), allX.end());
    maxY = std::max_element(allY.begin(), allY.end());

    box.push_back(Coordinate(*minX, *minY));
    box.push_back(Coordinate(*minX, *maxY));
    box.push_back(Coordinate(*maxX, *maxY));
    box.push_back(Coordinate(*maxX, *minY));

    this->box = box;

    return box;
}

std::string Shape::getName() {
    return this->name;
}