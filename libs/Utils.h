#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "Coordinate.h"

int Median(std::vector<int> vec); // Median value of a vector
void DirectNeighbors(int x, int y, cv::Mat& img, std::vector<cv::Vec3b>& field); // For optimization pass the vector as parameter and sets the neighbors to it.
void SpecialReplacePixels(cv::Mat &inImg, cv::Mat &binImg, cv::Vec3b &marker);

int GetStandardDeviaton(cv::Mat inImg);
template <class T> double StandardDeviation(std::vector<T> &v);

int GetMean(cv::Mat inImg);
template <class T> double Mean(std::vector<T> &v);

void FloodFill(cv::Mat& inImg, cv::Mat& outImg);

template <typename T> bool FindItem(std::vector<T> &mySet, T &item);
#endif // __UTILS_H_INCLUDED__