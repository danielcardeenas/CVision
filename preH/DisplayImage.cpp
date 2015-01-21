#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
        cout <<" Usage: ./DisplayImage <image_to_mod>" << endl;
        return -1;
    }

    Mat image,fin_img;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    /// BRG ->
    //channel[0] -> Blue
    //channel[1] -> Green
    //channel[2] -> Red
    Mat channel[3];
    Mat blue, red;
    imshow( "Original Image", image );

    // The actual splitting.
    split(image, channel);

    // Set channels
    blue = channel[0];
    red = channel[2];

    //channel[0]=Mat::zeros(image.rows, image.cols, CV_8UC1);//Set blue channel to 0

    // Replace red with blue
    channel[0] = red;
    channel[2] = blue;

    //Merging channels
    merge(channel,3,image);
    imshow("R->B", image);
    imwrite("mod.jpg",image);

    //waitKey(0);//Wait for a keystroke in the window

    while(waitKey(1) != 27);
    return 0;
}
