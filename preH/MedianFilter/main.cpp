#include <iostream>
#include <chrono>

#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "Filters.h"

using namespace cv;

int main(int argc, char** argv)
{
    
    Mat img, out_img;
    string outputPath = "medianed.jpg";
    
    // Get image from shell
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    
    //Initialize output image (Full black)
    out_img = Mat::zeros(img.size(), img.type());

    if(!img.data)
    {
        std::cout << "Could not load the image" << std::endl;
        return -1;
    }
    
    // Start counting time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    // Where magic happens
    MedianFilter(img, out_img);
    
    // Stop counting and print time elapsed
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    
    // Write image in same directory
    std::cout << "Writing image... (" << outputPath << ")" << std::endl;
    imwrite(outputPath, out_img);
    
    img.release();
    out_img.release();
    
    return 0;
}