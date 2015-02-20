#include <iostream>
#include <chrono>
#include <numeric>

#include "opencv2/opencv.hpp"
#include "Utils.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat colorImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    //imshow("bin", final);
    //waitKey(-1);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // Utils.cpp ->
    DetectShapes(img, colorImg);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;

    imwrite("final.jpg", colorImg);
    //waitKey(-1);
}
