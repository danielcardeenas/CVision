#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "Coordinate.h"
#include "Shape.h"

int Median(std::vector<int> vec); // Median value of a vector
void DirectNeighbors(int x, int y, cv::Mat& img, std::vector<cv::Vec3b>& field); // For optimization pass the vector as parameter and sets the neighbors to it.
void SpecialReplacePixels(cv::Mat &inImg, cv::Mat &binImg, cv::Vec3b &marker);

int GetStandardDeviaton(cv::Mat inImg);
template <class T> double StandardDeviation(std::vector<T> &v);

int GetMean(cv::Mat inImg);
template <class T> double Mean(std::vector<T> &v);

void FloodFill(cv::Mat& inImg, cv::Mat& outImg);
void DetectShapes(cv::Mat& inImg, cv::Mat& outImg);
std::vector<Shape> GetShapes(cv::Mat& inImg);
void DrawShapes(cv::Mat& inImg, std::vector<Shape> shapes);

template <typename T> bool FindItem(std::vector<T> &mySet, Coordinate item);

uchar MedianFromROI(std::vector<std::vector<uchar> > &I);
std::map<uchar, int> CalcROIHistogram(std::vector<std::vector<uchar> > &I);

void CustomDetectLines(cv::Mat &gradX, cv::Mat &gradY, cv::Mat &outImg);
void DetectLines(cv::Mat &inImg, cv::Mat &outImg);
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> GetLines(int threshold, unsigned int * &accu, int accu_h, int accu_w, int imgH, int imgW);
void DrawLines(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &lines, cv::Mat &outImg);
#endif // __UTILS_H_INCLUDED__