//
// Created by leind on 16/04/15.
//

#include <iostream>
#include "NewUtils.h"

void DetectHoles(cv::Mat inImg, cv::Mat outImg)
{
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    ///
    /// Get rows sums
    uchar* currentRow;
    std::vector<int> rowsValues;

    for (int i = 0; i < nRows; ++i)
    {
        currentRow = inImg.ptr<uchar>(i);
        rowsValues.push_back(GetSum(currentRow, nRows));
    }

    ///
    /// Get cols sums
    std::vector<int> colsValues;
    cv::Mat currentCol;
    uchar* charCol;
    
    for (int y = 0; y < nCols; ++y)
    {
       currentCol = inImg.col(y);
       charCol = currentCol.ptr<uchar>(y);
       colsValues.push_back(GetSum(charCol, nCols));
    }
    
    //std::cout << colsValues.size() << std::endl;
    
    //DFS only the whites in both vectors (cols and rows).
    DFSHist (inImg, colsValues, rowsValues);
}

void DFSHist(cv::Mat& inImg, std::vector<int>& colsValues, std::vector<int>& rowsValues)
{
    int MAXH = inImg.rows;
    int MAXW = inImg.cols;

    uchar probHole = 255;
    uchar spotted = 128;
    uchar current;

    Coordinate point;

    std::stack<Coordinate> stack;
    std::vector<Shape> holes;
    int num = 0, sumX = 0, sumY = 0; // Used to get the center of mass on the go
    int _ob = -1;

    // Things detected
    int things = 0;

    for (int i = 0; i < MAXH - 1; i++)
    {
        for (int j = 0; j < MAXW - 1; j++)
        {
            // Make sure to only go trough the holes detected in the histogram
            if (rowsValues[i] > 128 && colsValues[j] > 128)
            {
                stack.push(Coordinate(j, i));
                current = inImg.at<uchar>(i, j);
    
                if(current != spotted)
                {
                    //New object detected
                    _ob++;
                    holes.push_back(Shape(std::to_string(_ob)));
                }
    
                while(!stack.empty())
                {
                    point = stack.top();
                    stack.pop();
                    if(inImg.at<uchar>(point.y, point.x) != spotted)
                    {
                        // If not already spotted before
                        // Spot it
                        inImg.at<uchar>(point.y, point.x) = spotted;
                        holes[_ob].addCoordinate(Coordinate(point.x, point.y));
    
                        num++;
                        holes[_ob].putValues(point.x, point.y, num);
    
                        // Show real time
                        //cv::imshow("Demo", inImg);
                        //cv::waitKey(1);
    
                        /// Add neighbors to stack
                        /// They must be inside of bounds and must have not been spotted before
                        // Below neighbor
                        if((point.y + 1 < MAXH) && inImg.at<uchar>(point.y + 1, point.x) == probHole)
                            stack.push(Coordinate(point.x, point.y + 1));
    
                        // Above neighbor
                        if((point.y - 1 > 0) && inImg.at<uchar>(point.y - 1, point.x) == probHole)
                            stack.push(Coordinate(point.x, point.y - 1));
    
                        // Left neighbor
                        if((point.x - 1 >= 0) && inImg.at<uchar>(point.y, point.x - 1) == probHole)
                            stack.push(Coordinate(point.x - 1, point.y));
    
                        // Right neighbor
                        if((point.x + 1 < MAXW) && inImg.at<uchar>(point.y, point.x + 1) == probHole)
                            stack.push(Coordinate(point.x + 1, point.y));
                    }
                }
            }
        }
    }
    
    std::cout << holes.size() << std::endl;
}

/// Get sum of column / row
template <class T>
int GetSum(T &v, int size)
{
    int sum = 0, a;

    for (a = 0; a < size; ++a)
        sum += v[a];

    return sum;
}

void DoubleThreshold(cv::Mat& inImg, cv::Mat& outImg)
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
        
        for (j = 0; j < nCols; ++j)
        {
            // Get freq min ->0 - 128 max -> 128 -255
            if (inRow[j] > 100 && inRow[j] < 200)
                outRow[j] = 0;
            else
                outRow[j] = 255;
        }
    }
}