#include "Pixel.h"

/// Ctors
Pixel::Pixel(){}

Pixel& Pixel::operator=(Vec3b* row) // move assignment
{
    r = row[j + _w][2]; // R
    g = row[j + _w][1]; // G
    b = row[j + _w][0]; // B
    
    assert(this != &other); // self-assignment check not required
    delete[] mArray;        // delete this storage
    mArray = other.mArray;  // move
    other.mArray = nullptr; // leave moved-from in valid state
    return *this;
}