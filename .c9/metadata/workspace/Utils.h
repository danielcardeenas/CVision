{"filter":false,"title":"Utils.h","tooltip":"/Utils.h","undoManager":{"mark":0,"position":0,"stack":[[{"group":"doc","deltas":[{"start":{"row":0,"column":0},"end":{"row":11,"column":30},"action":"remove","lines":["#ifndef __UTILS_H_INCLUDED__","#define __UTILS_H_INCLUDED__","","#include \"opencv2/opencv.hpp\"","","void ComputeMedian(int& x, int& y, cv::Mat& img, cv::Mat& out_img);","void DirectNeighbors(int x, int y, cv::Mat& img);","std::vector<cv::Vec3b> GetDirectNeighbors(int x, int y, cv::Mat& img);","int Median(std::vector<int> vec);","void MedianFilter(cv::Mat& img, cv::Mat& out_img);","","#endif // __UTILS_H_INCLUDED__"]},{"start":{"row":0,"column":0},"end":{"row":11,"column":30},"action":"insert","lines":["#ifndef __UTILS_H_INCLUDED__","#define __UTILS_H_INCLUDED__","","#include \"opencv2/opencv.hpp\"","","void ComputeMedian(int& x, int& y, cv::Mat& img, cv::Mat& out_img);","void DirectNeighbors(int x, int y, cv::Mat& img);","std::vector<cv::Vec3b> GetDirectNeighbors(int x, int y, cv::Mat& img);","int Median(std::vector<int> vec);","void MedianFilter(cv::Mat& img, cv::Mat& out_img);","","#endif // __UTILS_H_INCLUDED__"]}]}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":11,"column":30},"end":{"row":11,"column":30},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1423430141653,"hash":"d88dc254fcd9de20008be81bbc83d0215277e1ed"}