#include <iostream>
#include <chrono>
#include <numeric>

#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "NewUtils.h"
#include "Filters.h"
#include "Shape.h"

#define MARGIN 10

using namespace std;
using namespace cv;

// Sorry for the global variables
std::vector<Coordinate> box;
int significativeDetections = 0;
int notRealDetections = 0;
int imgWidth;
int imgHeight;

std::vector<Shape> damages;

inline void processInfo()
{
    int smallerPart;
    if (imgWidth > imgHeight) { smallerPart = imgHeight; }
    else { smallerPart = imgWidth; }
    
    for(Shape &damage : damages)
    {
        // Get bounding box
        box = damage.getBoundingBox();
        
        // Get bounding box dimensions
        int x = box[3].x - box[0].x;
        int y = box[1].y - box[0].y;
        
        // Check if clean first
        if (x >= imgWidth - MARGIN || y >= imgHeight - MARGIN) { notRealDetections++; continue; }
        
        // Check if significative damage
        if (x > smallerPart/MARGIN || y > smallerPart/MARGIN)
        {
            std::cout << "Damage" << damage.getName() 
                        << " Dimensions: " << x << "x" << y << " - Significative damage" << std::endl;
                        
            significativeDetections ++;
        }
        else
        {
            std::cout << "Damage" << damage.getName() 
                        << " Dimensions: " << x << "x" << y << " - Non significative damage" << std::endl;
        }
    }
}

inline double evaluate()
{
    if (significativeDetections == 0)
    {
        std::cout << "All good" << std::endl;
    }
    
    if (significativeDetections >= 1)
    {
        std::cout << "Not good" << std::endl;
        double evaulation = (significativeDetections * 100) / (damages.size() - notRealDetections);
        
        std::cout << "Evaluation: " << evaulation << " (The bigger the worst)" << std::endl;
    }
}

int main(int argc, char** argv)
{
    //==============================================================================
    /** Preprocessing, you don't need to read this
     *  Applies a medianBlur kinda strong to make sure the noise is not there
     *  Creates output file name, etc... Really, you don't need to see this
    */
    Mat colorImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat inImg = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat prepImg = cv::Mat::zeros(inImg.size(), inImg.type());
    Mat binImg = cv::Mat::zeros(inImg.size(), inImg.type());
    imgWidth = inImg.cols;
    imgHeight = inImg.rows;
    std::cout << "Size: " << imgWidth << "x" << imgHeight << std::endl;
    std::string filename(argv[1]);
    std::string extension = ".jpg";
    size_t pos = filename.find_last_of(".");
    if (pos != string::npos)
        extension = filename.substr(pos+1);
    else
        std::cout << "Coud not find . in the string\n";

    std::string outputFileName = "output." + extension;
    cv::medianBlur(inImg, prepImg, 29);
    LazyThreshold(prepImg, binImg);
    
    //==============================================================================
    /** This is what you want to read
     *  DetectDamages -> Utils.cpp
    */
    damages = DetectDamages(binImg, colorImg);
    std::cout << "Damages detected: " << damages.size() << std::endl;
    processInfo();
    double evaulation = evaluate();
    
    // Was going to write the reult on the image but no time
    cv::Scalar color;
    std:string text;
    if (significativeDetections == 0)
    {
        text = "All good";
        color = cv::Scalar(0, 255, 0);
        cv::putText(colorImg,
            text,
            cv::Point (imgWidth/2, imgHeight/2),
            CV_FONT_HERSHEY_PLAIN,
            4.0,
            color,
            2,
            8,
            false);
    }
    else if (significativeDetections >= 1)
    {
        text = "Not cool";
        color = cv::Scalar(0, 0, 255);
        cv::putText(colorImg,
            text,
            cv::Point (imgWidth/2, imgHeight/2),
            CV_FONT_HERSHEY_PLAIN,
            4.0,
            color,
            4,
            8,
            false);
    }
    
    //==============================================================================
    imwrite(outputFileName, colorImg);
}
