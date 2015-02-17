#include <iostream>
#include <chrono>

#include "opencv2/opencv.hpp"
#include "Kernel.h"
#include "Filters.h"

using namespace std;
using namespace cv;
    
int main(int argc, char** argv)
{
     Mat img, out_img;
     
     //img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
     img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
     out_img = Mat::zeros(img.size(), img.type());

    // Sobel kernel
    Kernel gaus ({
        {1,2,1},
        {2,4,2},
        {1,2,1}
    });

    Kernel sob ({
            {-1,0,1},
            {-2,0,2},
            {-1,0,1}
    });

    //cvtColor(img,img,CV_RGB2GRAY);
    
    cout << img.channels() << endl;

    // Start counting time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    // Where magic happens
    Convolution(img, out_img, sob);
    
    // Stop counting and print time elapsed
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time elapsed fast: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Miliseconds" <<std::endl;
    
    // Write image in same directory
    std::cout << "Writing image... (" << "sobel.jpg" << ")" << std::endl;
    imwrite("sobel.jpg", out_img);
}