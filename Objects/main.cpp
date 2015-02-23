#include <iostream>
#include <chrono>
#include <numeric>

#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "Filters.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat colorImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat inImg = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    //imshow("bin", final);
    //waitKey(-1);

    cv::Mat joinImg = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat imgAbs = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradY = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradX = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat bin = cv::Mat::zeros(inImg.size(), inImg.type());

    // Supports n*n size
    /// As long it's odd sized and squared
    /// Kernel.cpp for more info
    Kernel soby ({
            {1,2,1},
            {0,0,0},
            {-1,-2,-1}
    });

    Kernel sobx ({
            {-1,0,1},
            {-2,0,2},
            {-1,0,1}
    });

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    /// Filters.cpp for more info
    Convolution(inImg, gradX, sobx);
    Convolution(inImg, gradY, soby);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;

    /// Filters.cpp for more info
    //EuclidianJoin(gradX, gradY, joinImg);
    // AbsJoin(gradX, gradY, joinImg);

    /// Filters.cpp for more info
    //DeviationThreshold(joinImg, final);
    LazyThreshold(joinImg, bin);
    // MeanThreshold(joinImg, final);


    // Utils.cpp ->
    DetectShapes(bin, colorImg);

    imwrite("final.jpg", colorImg);
    //waitKey(-1);
}
