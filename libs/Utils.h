#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "Coordinate.h"

int Median(std::vector<int> vec); // Median value of a vector
void DirectNeighbors(int x, int y, cv::Mat& img, std::vector<cv::Vec3b>& field); // For optimization pass the vector as parameter and sets the neighbors to it.
void XYNeighbors(Coordinate coo, cv::Mat& img, std::vector<std::vector<cv::Vec3b>>& neighborhood);

#endif // __UTILS_H_INCLUDED__