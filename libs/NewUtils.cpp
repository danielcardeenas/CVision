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
        //outRow = outImg.ptr<uchar>(i);

        rowsValues.push_back(GetSum(currentRow, nCols) / 2);
    }

    ///
    /// Get cols sums
    std::vector<int> colsValues;
    cv::Mat currentCol;

    for (int j = 0; j < nCols; ++j)
    {
        currentCol = inImg.col(j);

        colsValues.push_back(GetSum(currentCol.data, nCols) / 2);
    }

    std::cout << "such wow" << std::endl;
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