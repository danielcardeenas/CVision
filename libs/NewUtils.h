//
// Created by leind on 16/04/15.
//

#ifndef ELLIPSES_NEWUTILS_H
#define ELLIPSES_NEWUTILS_H

#include <opencv2/core/core.hpp>
#include <stack>
#include "Coordinate.h"
#include "Shape.h"
#include "Utils.h"

void DetectHoles(cv::Mat inImg, cv::Mat outImg);
template <class T> int GetSum(T &v, int size);
void DoubleThreshold(cv::Mat& inImg, cv::Mat& outImg);
std::vector<Shape> DFSHist(cv::Mat& inImg, std::vector<int>& colsValues, std::vector<int>& rowsValues);

#endif //ELLIPSES_NEWUTILS_H
