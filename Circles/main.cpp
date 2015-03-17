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
    int threshold = 0;

    //imshow("bin", final);
    //waitKey(-1);

    cv::Mat joinImg = cv::Mat::zeros(inImg.size(), inImg.type());
    //cv::Mat imgAbs = cv::Mat::zeros(inImg.size(), inImg.type());
    //cv::Mat gradY = cv::Mat::zeros(inImg.size(), inImg.type());
    //cv::Mat gradX = cv::Mat::zeros(inImg.size(), inImg.type());
    //cv::Mat bin = cv::Mat::zeros(inImg.size(), inImg.type());

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

    ///
    /// If a second parameter is given.
    /// Assume its the threshold value
    /// Note: atoi() will treat any invalid parameter as 0
    if (argc >= 3)
        threshold = atoi(argv[2]);

    ///
    /// Uncomment this lines if you want to use my functions for pre-processing
    /// Convolution function is slow
    //Convolution(inImg, gradX, sobx);
    //Convolution(inImg, gradY, soby);
    //EuclidianJoin(gradX, gradY, joinImg);

    ///
    /// Comment this if you're going to use the functions from above.
    /// Canny is way more fast than two sobel convolutions.
    /// TODO: Implement Canny detection.
    cv::blur(inImg, joinImg, cv::Size(5,5));
    cv::Canny(joinImg, joinImg, 100, 150, 3);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    ///
    /// @param:
    ///     cv::Mat &inImg: input image
    ///      cv::Mat &outImg: output image
    ///      int threshold: [auto if not defined]
    ///      int minRadius: [20 if not defined],
    ///      int maxRadius: [200 if not defined],
    ///      int step : [4 if not defined]
    DetectCircles(joinImg, colorImg, threshold);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    imwrite("detectedCircles.jpg", colorImg);
}
