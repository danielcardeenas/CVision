#include <iostream>
#include <chrono>
#include <numeric>

#include "opencv2/opencv.hpp"
#include "Kernel.h"
#include "Filters.h"
#include "Utils.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat colorImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
     
    Mat joinImg = Mat::zeros(img.size(), img.type());
    Mat imgAbs = Mat::zeros(img.size(), img.type());
    Mat gradY = Mat::zeros(img.size(), img.type());
    Mat gradX = Mat::zeros(img.size(), img.type());
    Mat final = Mat::zeros(img.size(), img.type());

    /// Supports n*n size
    /// As long it's odd sized and squared (same size for the 2 dimensions)
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
    
    /// Filters.cpp for more info
    Convolution(img, gradX, sobx);
    Convolution(img, gradY, soby);
    
    /// Filters.cpp for more info
    EuclidianJoin(gradX, gradY, joinImg);
    // AbsJoin(gradX, gradY, joinImg);
    
    /// Filters.cpp  for more info
    DeviationThreshold(joinImg, final);
    // LazyThreshold(out_img, final);
    // MeanThreshold(out_img, finalmean);

    //imshow("bin", final);
    //waitKey(-1);

    FloodFill(final, colorImg);

    imwrite("final.jpg", colorImg);
    //waitKey(-1);
}