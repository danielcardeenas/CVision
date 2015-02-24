#include <iostream>
#include <chrono>

#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "Filters.h"

using namespace cv;

int main(int argc, char** argv)
{
    
    Mat img, out_img;
    Mat dst, fast;
    string outputPath = "medianed.jpg";
    
    // Get image from shell
    img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    
    //Initialize output image (Full black)
    out_img = Mat::zeros(img.size(), img.type());
    dst = Mat::zeros(img.size(), img.type());

    if(!img.data)
    {
        std::cout << "Could not load the image" << std::endl;
        return -1;
    }
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    medianBlur(img, dst, 3);
    imwrite("medianblur.jpg", dst);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed opencv: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    
    // Start counting time
    begin = std::chrono::steady_clock::now();
    
    // Where magic happens
    MedianFilter(img, out_img);
    
    // Stop counting and print time elapsed
    end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed fast: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    
    // Write image in same directory
    std::cout << "Writing image... (" << "fast.jpg" << ")" << std::endl;
    
    imwrite("fast.jpg", out_img);
    
    // Start counting time
    begin = std::chrono::steady_clock::now();
    
    // Where magic happens
    MedianFilter(img, dst);
    
    // Stop counting and print time elapsed
    end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed normal: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    
    // Write image in same directory
    std::cout << "Writing image... (" << outputPath << ")" << std::endl;
    
    imwrite(outputPath, dst);
    
    img.release();
    out_img.release();
    
    return 0;
}