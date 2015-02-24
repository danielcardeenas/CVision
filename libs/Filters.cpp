#include <iostream>
#include <math.h> 
#include <map>

#include "Utils.h"
#include "Filters.h"
#include "Neighborhood.h"

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

void MedianFilterGray(cv::Mat& img, cv::Mat& out_img)
{
    if (img.channels() != 1) { std::cerr << "Image not supported" << std:: endl; return; }
    
    int nRows = img.rows;
    int nCols = img.cols;
    
    // 3x3 vector. Neighbordhood area
    std::vector<std::vector<uchar>> area(3, std::vector<uchar>(3));

    if (img.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* upRow;
    uchar* centerRow;
    uchar* belowRow;
    for( i = 1; i < nRows - 1; ++i)
    {
        upRow = img.ptr<uchar>(i-1);
        centerRow = img.ptr<uchar>(i);
        belowRow = img.ptr<uchar>(i+1);
        for ( j = 1; j < nCols - 1; ++j)
        {
            /// Get neighbordhood
            
            // Above row
            area[0][0] = upRow[j - 1];
            area[0][1] = upRow[j];
            area[0][2] = upRow[j + 1];
            
            // Middle row
            area[1][0] = centerRow[j - 1];
            area[1][1] = centerRow[j];
            area[1][2] = centerRow[j + 1];
            
            // Below row
            area[2][0] = belowRow[j - 1];
            area[2][1] = belowRow[j];
            area[2][2] = belowRow[j + 1];
            
            centerRow[j] = MedianFromROI(area);
        }
    }
}

/**
 * Convolution "Interface". Decides what fucniton to call giving a colored image or grayscaled
 * Giving a 2D int vector (kernel), applies convolution to an img
 * @param:
 *  [INPUT]  Mat: input image
 *  [OUTPUT] Mat: output image
 *  [INPUT]  Kernel: kernel object (Read libs/Kernel.h for info)
 *  [OPTIONAL] int bias: Can be used if you want to make the resulting image brighter
*/
void Convolution(cv::Mat& img, cv::Mat& out_img, Kernel& kernel, int bias)
{
    if(img.channels() == 3)
        ConvolutionRGB(img, out_img, kernel, bias);
    else if (img.channels() == 1)
        ConvolutionGrayscale(img, out_img, kernel, bias);
    else
        std::cerr << "Image not supported" << std::endl;
}

///
/// Convolution algorithm for 3 channel image
void ConvolutionRGB(cv::Mat& img, cv::Mat& out_img, Kernel& kernel, int bias)
{
    uchar r, g, b;
    std::vector<cv::Vec3b*> rows(kernel.size());

    // Will let know the kernel where it should take the value
    int _nRow;

    /// Σ (Summation)
    /// Each element a color: [0]:B, [1]:G, [2]:R
    std::vector<int> summation {0,0,0};

    cv::Vec3b pixel;

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

///
/// Convolution algorithm for 1 channeled image
void ConvolutionGrayscale(cv::Mat& img, cv::Mat& out_img, Kernel& kernel, int bias)
{
    uchar gray;
    std::vector<uchar*> rows(kernel.size());

    // Will let know the kernel where it should take the value
    int _nRow;

    /// Σ (Summation)
    /// Each element a color: [0]:B, [1]:G, [2]:R
    int summation = 0;

    uchar pixel;

    int z = kernel.size() / 2; // Center of the rows
    int _z; // Row position (can be negative values)
    int logicRow = 0; // Logical position in vector for row from _z

    int w = kernel[0].size() / 2; // Center of the columns
    int _w = 0; // Column position (can be negative values)
    int logicColumn = 0; // Logical position in vector for row from _z

    /// This loop does not touch borders nor corners
    for (int i = z; i < img.rows-z; ++i)
    {
        /// Generate rows needed giving a kernel size
        /// Assign rows in a vector dynamically
        /// from a n*n kernel (odd sized)
        for(_z = z * -1, logicRow = 0; _z <= z; ++_z)
        {
            /// Sets first the rows from above the center
            /// Then sets the center row in the center of the vector
            /// Sets at last the rows below the center
            rows[logicRow] = img.ptr<uchar>(i + _z); // Points to _z row
            
            logicRow++;
        }

        for (int j = z; j < img.cols-z; ++j)
        {
            _nRow = 0;
            summation = 0; // Set summations in zero
            for(uchar* row : rows)
            {
                for(_w = w * -1, logicColumn = 0; _w <= w; ++_w)
                {
                    /// Sets first the left side columns in the row
                    /// Then sets the center side columns in the row
                    // Sets at last the right side columns in the row
                    gray = row[j + _w];

                    summation += gray * kernel[_nRow][logicColumn];
                    logicColumn++;
                }

                _nRow++;
            }

            if(kernel.isNormalized)
            {
                summation /= kernel.normal;
            }

            // Truncate to get better results
            pixel = std::min(std::abs(summation) + bias, 255); // R

            // Draw pixel in the kernel anchor position
            out_img.ptr<uchar>(kernel.anchor.x + i - 1)[kernel.anchor.y + j - 1] = pixel;
        }
    }
}

/// Joins 2 images by calculating their pixels euclidian distance
/// G² = Gx² + Gy²
void EuclidianJoin(cv::Mat &gradX, cv::Mat &gradY, cv::Mat &out_img)
{
    if (gradX.channels() != 1 || gradY.channels() != 1) { std::cerr << "Image not supported yet" << std:: endl; return; }
    
    int nRows = gradX.rows;
    int nCols = gradY.cols;

    if (gradX.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* gradXRow;
    uchar* gradYRow;
    uchar* outRow;
    for( i = 0; i < nRows; ++i)
    {
        gradXRow = gradX.ptr<uchar>(i);
        gradYRow = gradY.ptr<uchar>(i);
        outRow = out_img.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            /// Calculate and truncate
            /// G² = Gx² + Gy²
            outRow[j] = std::min((int)std::sqrt(std::pow(gradXRow[j], 2) + std::pow(gradYRow[j], 2)), 255);
        }
    }
}

/// Joins 2 images by calculating their pixels absolutes
/// G = |Gx| + |Gy|
void AbsJoin(cv::Mat &gradX, cv::Mat &gradY, cv::Mat &out_img)
{
    if (gradX.channels() != 1 || gradY.channels() != 1) { std::cerr << "Image not supported yet" << std:: endl; return; }
    
    int nRows = gradX.rows;
    int nCols = gradY.cols;

    if (gradX.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* gradXRow;
    uchar* gradYRow;
    uchar* outRow;
    for( i = 0; i < nRows; ++i)
    {
        gradXRow = gradX.ptr<uchar>(i);
        gradYRow = gradY.ptr<uchar>(i);
        outRow = out_img.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            /// Calculate and truncate
            /// G = |Gx| + |Gy|
            outRow[j] = std::min((int)std::abs(gradXRow[j]) + (int)std::abs(gradYRow[j]), 255);
        }
    }
}

/// Binarize the image making 128 = (255/2) of the pixels the cut
void LazyThreshold(cv::Mat &inImg, cv::Mat &outImg)
{
    if (inImg.channels() != 1) { std::cerr << "Cannot apply threshold to non one-channeled image" << std:: endl; return; }
    
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    if (inImg.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* inRow;
    uchar* outRow;
    for( i = 0; i < nRows; ++i)
    {
        inRow = inImg.ptr<uchar>(i);
        outRow = outImg.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            if(inRow[j] < 128)
                outRow[j] = 0;
            else
                outRow[j] = 255;
        }
    }
}

/// Binarize the image making the standard deviation of the pixels the cut
void DeviationThreshold(cv::Mat &inImg, cv::Mat &outImg)
{
    if (inImg.channels() != 1) { std::cerr << "Cannot apply threshold to non one-channeled image" << std:: endl; return; }
    
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    if (inImg.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    /// Utils.cpp for more info
    int cut = GetStandardDeviaton(inImg);
    
    int i,j;
    uchar* inRow;
    uchar* outRow;
    for( i = 0; i < nRows; ++i)
    {
        inRow = inImg.ptr<uchar>(i);
        outRow = outImg.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            if(inRow[j] < cut)
                outRow[j] = 0;
            else
                outRow[j] = 255;
        }
    }
}

/// Binarize the image making the mean of the pixels the cut
void MeanThreshold(cv::Mat &inImg, cv::Mat &outImg)
{
    if (inImg.channels() != 1) { std::cerr << "Cannot apply threshold to non one-channeled image" << std:: endl; return; }
    
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    if (inImg.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    /// Utils.cpp for more info
    int cut = GetMean(inImg);
    
    int i,j;
    uchar* inRow;
    uchar* outRow;
    for( i = 0; i < nRows; ++i)
    {
        inRow = inImg.ptr<uchar>(i);
        outRow = outImg.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            if(inRow[j] < cut)
                outRow[j] = 0;
            else
                outRow[j] = 255;
        }
    }
}