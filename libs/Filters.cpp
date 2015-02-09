#include <iostream>
#include <assert.h>

#include "Utils.h"
#include "Filters.h"

std::vector<cv::Vec3b> field;
std::vector<int> pix(9);
std::vector<int>::iterator it;

int i;

std::vector<int> blue(9);
std::vector<int> green(9);
std::vector<int> red(9);

int medBlue;
int medGreen;
int medRed;

int _x, _y;

/**
 * Median value of a std::vector<int>
 * @note: Gets the vector as copy, so the sorting does not affcet the original vector
 * @param std::vector<int>
 * @return int median
*/
int Median(std::vector<int> vec)
{
    int median;
    size_t size = vec.size();

    // Sort
    sort(vec.begin(), vec.end());

    if (size  % 2 == 0)
        median = (vec[size / 2 - 1] + vec[size / 2]) / 2;
    else
        median = vec[size / 2];

    //vector<int>().swap(vec);
    return median;
}

/**
 * Computes the median of a pixel coordinate (x, y) from Mat::img 
 * and sets it to Mat::out_img on the same coordinate
 * @param: int x, int y, Mat::img, Mat::out_img
*/
void ComputeMedian(int& x, int& y, cv::Mat& img, cv::Mat& out_img)
{
    // Gets the direct neighbors of a pixel into a vector
    DirectNeighbors(x, y, img, field);

    // If the pixel is an edge or a corner (direct neighbors are less than 9)
    // Get median of each channel and create new pixel
    if(field.size() < 9)
    {
        blue.resize(field.size());
        green.resize(field.size());
        red.resize(field.size());

        for(i = 0; i < field.size(); ++i)
        {
            blue.at(i) = field.at(i)[0]; //B
            green.at(i) = field.at(i)[1]; //G
            red.at(i) = field.at(i)[2]; //R
        }

        //Median
        medBlue = Median(blue);
        medGreen = Median(green);
        medRed = Median(red);

        cv::Vec3b color;
        color[0] = medBlue;
        color[1] = medGreen;
        color[2] = medRed;

        out_img.at<cv::Vec3b>(y, x) = color;
        field.clear();
    }
    else{
        // Since this will always be 9
        // Just set the index of the median values R+G+B of the vector
        // This way is much faster than creating a new pixel
        pix.resize(field.size());
        for(i = 0; i < field.size(); i++)
        {
            pix.at(i) = (
                     field.at(i)[0]
                    + field.at(i)[1]
                    + field.at(i)[2]
            );
        }
        
        // Find the median value in the vector and set it to an iterator
        it = find(pix.begin(), pix.end(), Median(pix));
        auto index = std::distance(pix.begin(), it);
        out_img.at<cv::Vec3b>(y, x) = field.at(index);
        
        pix.clear();
        field.clear();
    }
}

/**
 * Easy-way calling for the actual filter algorithm
 * Sets median filter to Mat::img. Outputs Mat::out_img
 * @note: Gets the images as reference
 * @param Mat::img input image, Mat::out_img output image
*/
void MedianFilter(cv::Mat& img, cv::Mat& out_img)
{
    // Init output just in case 
    if(!out_img.data)
        out_img = cv::Mat::zeros(img.size(), img.type());
        
    // Iterating trough pixels
    for(int y = 0; y < img.rows - 0; y++)
        for(int x = 0; x < img.cols - 0; x++)
        {
            ComputeMedian(x, y, img, out_img);
        }
}

/**
 * Easy-way calling for the actual convolution algorithm
 * Giving a 2D int array, applies convolution to img
 * @param:
 *  Mat input image
 *  [OUTPUT] Mat output image
 *  vector<vector<int>> kernel
 *  [OUTPUT] <vector<Vec3b> neighborhood = Where the pixel's neighbors are set. Must be initialized in the desired size
 *  Coordinate anchor of the kernel
*/
void Convolution(cv::Mat& img, cv::Mat& out_img, std::vector<std::vector<cv::Vec3b>>& neighborhood, std::vector<std::vector<int>> kernel, Coordinate anchor)
{
    assert(kernel.size() < anchor.x || kernel[0].size() < anchor.y);
    
    // Iterating trough pixels
    for(int y = 0; y < img.rows; y++)
        for(int x = 0; x < img.cols; x++)
        {
            // Get neighboorhood
            XYNeighbors(Coordinate(x, y), img, neighborhood);
        }
        
    ComputeConvolution(img, out_img, neighborhood);
}

// BGR
void ComputeConvolution(cv::Mat& img, cv::Mat& out_img, std::vector<std::vector<cv::Vec3b>>& neighborhood)
{
    _x = neighborhood.size();
    _y = neighborhood[0].size();
    
    return;
}