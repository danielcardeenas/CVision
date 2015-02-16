#include <iostream>

#include "Utils.h"
#include "Filters.h"
#include "Neighborhood.h"
#include "Pixel.h"

std::vector<cv::Vec3b> field;
std::vector<int> pix(9);
std::vector<int>::iterator it;

/**
 * Two times faster than my normal median filter
 * Still not as fast the opencv implementation.
 * Only works with a 3x3 neighborhood
 * @param 
 *  [INPUT]  Mat: input image
 *  [OUTPUT] Mat: image to output (Cannot be the same as input)
*/
void MedianFilter(cv::Mat& img, cv::Mat& out_img)
{
    uchar r, g, b;
    int x = 0;
    Neighborhood directNeigh;

    cv::Vec3b* pixel_r1;
    cv::Vec3b* pixel_r2;
    cv::Vec3b* pixel_r3;
    
    for (int i = 1; i < img.rows -1; ++i)
    {
        pixel_r1 = img.ptr<cv::Vec3b>(i-1); // point to first pixel in row
        pixel_r2 = img.ptr<cv::Vec3b>(i); // point to first pixel in row
        pixel_r3 = img.ptr<cv::Vec3b>(i+1); // point to first pixel in row
        for (int j = 1; j < img.cols -1; ++j)
        {
            // (0,0)
            r = pixel_r1[j-1][2];
            g = pixel_r1[j-1][1];
            b = pixel_r1[j-1][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (0,1)
            r = pixel_r1[j][2];
            g = pixel_r1[j][1];
            b = pixel_r1[j][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (0,2)
            r = pixel_r1[j+1][2];
            g = pixel_r1[j+1][1];
            b = pixel_r1[j+1][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (1,0)
            r = pixel_r2[j-1][2];
            g = pixel_r2[j-1][1];
            b = pixel_r2[j-1][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (1,1)
            r = pixel_r2[j][2];
            g = pixel_r2[j][1];
            b = pixel_r2[j][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (1,2)
            r = pixel_r2[j+1][2];
            g = pixel_r2[j+1][1];
            b = pixel_r2[j+1][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (2,0)
            r = pixel_r3[j-1][2];
            g = pixel_r3[j-1][1];
            b = pixel_r3[j-1][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (2,1)
            r = pixel_r3[j][2];
            g = pixel_r3[j][1];
            b = pixel_r3[j][0];
            directNeigh.push(r, g, b, x);
            x++;
            
            // (2,2)
            r = pixel_r3[j+1][2];
            g = pixel_r3[j+1][1];
            b = pixel_r3[j+1][0];
            directNeigh.push(r, g, b, x);
            x = 0;
            
            
            // Get median from the neighborhood
            pix.resize(9);
            for(int z = 0; z < 9; z++)
                pix.at(z) = directNeigh.sum(z);
            
            // Find the median value in the vector and set it to an iterator
            it = find(pix.begin(), pix.end(), Median(pix));
            auto index = std::distance(pix.begin(), it);
            out_img.at<cv::Vec3b>(i, j) = directNeigh.pixel(index);
            
            pix.clear();
            field.clear();
            
        }
    }
}

/**
 * Convolution algorithm
 * Giving a 2D int vector (kernel), applies convolution to an img
 * @param:
 *  [INPUT]  Mat: input image
 *  [OUTPUT] Mat: output image
 *  [INPUT]  Kernel: kernel object (Read libs/Kernel.h for info)
 *  [OPTIONAL] int bias: Can be used if you want to make the resulting image brighter
*/
void Convolution(cv::Mat& img, cv::Mat& out_img, Kernel& kernel, int bias)
{
    uchar r, g, b;
    
    cv::Vec3b pixel;
    std::vector<cv::Vec3b*> rows(kernel.size());

    // Will let know the kernel where it should take the value
    int _nRow;

    /// Σ (Summation)
    /// Each element a color: [0]:B, [1]:G, [2]:R
    std::vector<int> summation {0,0,0};
    
    int z = kernel.size() / 2; // Center of the rows
    int _z; // Row position (can be negative values)
    int logicRow = 0; // Logical position in vector for row from _z

    int w = kernel[0].size() / 2; // Center of the columns
    int _w = 0; // Column position (can be negative values)
    int logicColumn = 0; // Logical position in vector for row from _z

    /// This loop does not touch borders nor corners
    for (int i = z; i < img.rows-z; ++i)
    {
        /// Assign rows in a vector dynamically
        /// from a n*n kernel (odd sized)
        for(_z = z * -1, logicRow = 0; _z <= z; ++_z)
        {
            /// Sets first the rows from above the center
            /// Then sets the center row in the center of the vector
            /// Sets at last the rows below the center
            rows[logicRow] = img.ptr<cv::Vec3b>(i + _z); // Points to _z row
            logicRow++;
        }

        for (int j = z; j < img.cols-z; ++j)
        {
            _nRow = 0;
            std::fill(summation.begin(), summation.end(), 0); // Set summations in zero
            for(cv::Vec3b* row : rows)
            {
                for(_w = w * -1, logicColumn = 0; _w <= w; ++_w)
                {
                    /// Sets first the left side columns in the row
                    /// Then sets the center side columns in the row
                    // Sets at last the right side columns in the row
                    r = row[j + _w][2]; // R
                    g = row[j + _w][1]; // G
                    b = row[j + _w][0]; // B
                    
                    // Pixel object handles the quantity of channels
                    //pixel = row

                    summation[2] += r * kernel[_nRow][logicColumn];
                    summation[1] += g * kernel[_nRow][logicColumn];
                    summation[0] += b * kernel[_nRow][logicColumn];
                    logicColumn++;
                }

                _nRow++;
            }
            
            if(kernel.isNormalized)
            {
                summation[2] /= kernel.normal;
                summation[1] /= kernel.normal;
                summation[0] /= kernel.normal;
            }

            // Truncate to get better results
            pixel[2] = std::min(std::abs(summation[2]) + bias, 255); // R
            pixel[1] = std::min(std::abs(summation[1]) + bias, 255); // G
            pixel[0] = std::min(std::abs(summation[0]) + bias, 255); // B

            // Draw pixel in the kernel anchor position
            out_img.at<cv::Vec3b>(kernel.anchor.x + i - 1, kernel.anchor.y + j - 1) = pixel;
        }
    }
}