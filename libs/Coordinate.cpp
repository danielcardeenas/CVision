#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    this->x = x;
    this->y = y;
}
Coordinate::Coordinate() {
    // Init variables
    return;
}

void Coordinate::operator ()(int x, int y) {
    this->x = x;
    this->y = y;
}

void Coordinate::operator =(Coordinate p) {
    this->x = p.x;
    this->y = p.y;
}