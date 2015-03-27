//
// Created by leind on 26/03/15.
//

#include "Ellipse.h"

Ellipse::Ellipse() {}


Ellipse::Ellipse(Coordinate center, int majorAxis, int minorAxis, double alpha, int votes) {
    this->center = center;
    this->a = majorAxis;
    this->b = minorAxis;
    this->alpha = alpha;
    this->votes = votes;
}
