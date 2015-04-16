//
// Created by leind on 16/04/15.
//

#ifndef ELLIPSES_NEWUTILS_H
#define ELLIPSES_NEWUTILS_H

#include <opencv2/core/core.hpp>

void DetectHoles(cv::Mat inImg, cv::Mat outImg);
template <class T> int GetSum(T &v, int size);

#endif //ELLIPSES_NEWUTILS_H
