#include <iostream>
#include <chrono>
#include <numeric>

#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "NewUtils.h"
#include "Filters.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat colorImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat inImg = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat prepImg = cv::Mat::zeros(inImg.size(), inImg.type());
    Mat binImg = cv::Mat::zeros(inImg.size(), inImg.type());

    imwrite("gray.jpg", inImg);

    ///
    /// Create output filename
    std::string filename(argv[1]);
    std::string extension = ".jpg";

    // find the last dot '.'
    size_t pos = filename.find_last_of(".");

    // make sure the poisition is valid
    if (pos != string::npos)
        extension = filename.substr(pos+1);
    else
        std::cout << "Coud not find . in the string\n";

    std::string outputFileName = "detectedHoles." + extension;

    /// Canny is way more fast than two sobel convolutions.
    /// TODO: Implement Canny detection.
    cv::blur(inImg, prepImg, cv::Size(5,5));
    //cv::Canny(prepImg, prepImg, 100, 150, 3);
    DoubleThreshold(prepImg, binImg);
    //imshow("cannied", binImg);
    //waitKey(99999);
    
    imwrite("thresh.jpg", binImg);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    ///
    /// @param:
    ///     cv::Mat &inImg: input image
    ///      cv::Mat &outImg: output image
    ///      int threshold: [auto if not defined]
    ///      int minRadius: [20 if not defined],
    ///      int maxRadius: [200 if not defined],
    ///      int step : [4 if not defined]
    DetectHoles(binImg, colorImg);

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    imwrite(outputFileName, colorImg);
}
