#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "Coordinate.h"
#include "Shape.h"
#include "Ellipse.h"

// Cause pair of pairs lokos ugly
typedef std::vector< std::pair< std::pair<int, int>, int>> circleStruct; // [(x₀, y₀), radius]
typedef std::vector< std::pair< std::pair<int, int>, std::pair<int, int>>> lineStruct; // [(x₁, y₁), (x₂, y₂)]

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

/* ==========================================================================
     Lines detection
     --------------------------------------------------------------------------
*/
void CustomDetectLines(cv::Mat &gradX, cv::Mat &gradY, cv::Mat &outImg);
void DetectLines(cv::Mat &inImg, cv::Mat &outImg, int threshold = 100);
lineStruct GetLines(int threshold, unsigned int * &accu, int accu_h, int accu_w, int imgH, int imgW);
void DrawLines(lineStruct &lines, cv::Mat &outImg);

/* ==========================================================================
     Circles detection
     --------------------------------------------------------------------------
*/
void DetectCircles(cv::Mat &inImg, cv::Mat &outImg, int threshold = 0, int minRadius = 20, int maxRadius = 250, int step = 4);
void HoughCircleTransform(unsigned char* img_data, int width, int height, int r, unsigned int* &accumulator);
void GetCircles(int threshold, circleStruct& circles, int r, unsigned int* &accumulator, const int accuH, const int accuW);
void DrawCircles(cv::Mat& outImg, circleStruct& circles);

/* ==========================================================================
     Ellipses detection
     --------------------------------------------------------------------------
*/
void DetectEllipses(cv::Mat &inImg, cv::Mat &outImg, int threshold = 0, int minMajorAxis = 120);
int findMaximum(unsigned int* &a, int n);

/* ==========================================================================
     Test
     --------------------------------------------------------------------------
*/
std::vector<Shape> DetectDamages(cv::Mat& inImg, cv::Mat& outImg);

#endif // __UTILS_H_INCLUDED__