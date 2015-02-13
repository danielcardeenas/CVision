#ifndef __FILTERS_H_INCLUDED__
#define __FILTERS_H_INCLUDED__

#include "opencv2/opencv.hpp"

int Median(std::vector<int> vec); // Median value of a vector
void MedianFilter(cv::Mat& img, cv::Mat& out_img); // Easy-way calling method
void ComputeMedian(int& x, int& y, cv::Mat& img, cv::Mat& out_img); // Actual filter algorithm
void FastMedian(cv::Mat& img, cv::Mat& out_img);

void ComputeConvolution(cv::Mat& img, cv::Mat& out_img, std::vector<std::vector<cv::Vec3b>>& neighborhood);
void Convolution(cv::Mat& img, cv::Mat& out_img, std::vector<std::vector<cv::Vec3b>>& neighborhood, std::vector<std::vector<int>> kernel, Coordinate anchor);

#endif // __FILTERS_H_INCLUDED__