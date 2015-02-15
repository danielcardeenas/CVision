#ifndef __FILTERS_H_INCLUDED__
#define __FILTERS_H_INCLUDED__

#include "opencv2/opencv.hpp"
#include "Coordinate.h"
#include "Kernel.h"

void MedianFilter(cv::Mat& img, cv::Mat& out_img); // Easy-way calling method
void ComputeMedian(int& x, int& y, cv::Mat& img, cv::Mat& out_img); // Actual filter algorithm
void FastMedian(cv::Mat& img, cv::Mat& out_img); // Faster median algoritm

void Convolution(cv::Mat& img, cv::Mat& out_img, Kernel& kernel);

#endif // __FILTERS_H_INCLUDED__