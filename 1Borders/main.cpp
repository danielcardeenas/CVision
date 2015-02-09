/* ---------------------------------------------------------------------------
** References: 
**  Convolution: http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/filter_2d/filter_2d.html
**  Sobel function: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=sobel#sobel
**  Thresholding: http://docs.opencv.org/doc/tutorials/imgproc/threshold/threshold.html
** -------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Filters.h"

using namespace cv;
using namespace std;

/** @function main */
int main( int argc, char** argv )
{

    Mat img, img_med, img_gray;
    Mat grad;

    int c;
    
    img = imread(argv[1]);

    if(!img.data ) { return -1; }
    
    // Apply median filter to remove noise
    MedianFilter(img, img_med);

    // Convert it to gray
    cvtColor(img_med, img_gray, CV_RGB2GRAY);

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    // Gradient X
    Sobel(img_gray, grad_x, -1, 1, 0, 3, BORDER_DEFAULT );
    convertScaleAbs(grad_x, abs_grad_x);

    // Gradient Y
    Sobel(img_gray, grad_y, -1, 0, 1, 3, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    // Sum gradients
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    // Binarize the image
    Mat copy;
    cv::threshold(grad, copy, 0, 255, CV_THRESH_OTSU | CV_THRESH_BINARY);

    // Convert it to a color image again
    cvtColor(copy, copy, CV_GRAY2BGR);

    // Change border color (White -> Green)
    Mat3b output = copy;
    for (Mat3b::iterator it = output.begin(); it != output.end(); it++) {
        if (*it == Vec3b(255, 255, 255)) {
            *it = Vec3b(0, 255, 0);
        }
    }
    
    
    // Set a border marker
    cv::Vec3b marker;
    marker[0] = 0;
    marker[1] = 0;
    marker[2] = 255;
    
    // Using fast pixel access to set the borders int he original image
    for (int i = 0; i < output.rows; ++i)
    {
        cv::Vec3b* pixel = output.ptr<cv::Vec3b>(i);
        for (int j = 0; j < output.cols; ++j)
        {
            if(pixel[j][2] == 0 && pixel[j][1] == 255 && pixel[j][0] == 0)
                img.at<cv::Vec3b>(i,j) = marker;
        }
    }
    cout << "Writing image... (bordered.jpg)" << endl;
    imwrite("threshold.jpg", output);
    imwrite("bordered.jpg", img);

    return 0;
}
