#include "Neighborhood.h"

void Neighborhood::push(uchar r, uchar g, uchar b, int x) {
    this->oned_neighborhood[x][2] = r;
    this->oned_neighborhood[x][1] = g;
    this->oned_neighborhood[x][0] = b;
}

void Neighborhood::push(uchar gray, int x) {
    this->oned_neighborhood[x] = gray;
}

int Neighborhood::sum(int index) {
    return (
        this->oned_neighborhood[index][0] +
        this->oned_neighborhood[index][1] +
        this->oned_neighborhood[index][2]
        );
}

cv::Vec3b Neighborhood::pixel(int index) {
    return this->oned_neighborhood[index];
}

Neighborhood::Neighborhood() {
    // Initialize the variables
    return;
}