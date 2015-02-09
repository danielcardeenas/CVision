#include <iostream>
#include <stdio.h>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if( argc != 2)
    {
        cout <<" Usage: ./channels <image_to_mod>" << endl;
        return -1;
    }

    Mat image, fin_img;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    // Check for invalid input
    if(!image.data)
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    /** 
     * BRG:
     *  channel[0] -> Blue
     *  channel[1] -> Green
     *  channel[2] -> Red
    */
    Mat channel[3];
    Mat blue, red;

    // Split channels
    split(image, channel);

    // Set channels needed
    blue = channel[0];
    red = channel[2];

    // Replace red with blue
    channel[0] = red;
    channel[2] = blue;

    //Merging channels
    merge(channel,3,image);
    
    // Uncomment this if you want to see the image ina  window
    //imshow("R->B", image);
    
    // Write image on same directory
    imwrite("mod.jpg",image);

    //Wait for a keystroke in the window. Uncomment this too if you want to see the image in a window
    //waitKey(-1);
    
    return 0;
}