#include <iostream>
#include <stack>
#include <set>

#include "Utils.h"
#include "Coordinate.h"
#include "Shape.h"
#include "Filters.h"
#include "Kernel.h"

std::vector<cv::Vec3b> neighbors;

/// Gets the standard deviation value of an image
int GetStandardDeviaton(cv::Mat inImg)
{
    if (inImg.channels() != 1) { std::cerr << "Cannot apply threshold to non one-channeled image" << std::endl; return -1; }
    
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    if (inImg.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* inRow;
    std::vector<int> v;
    for( i = 0; i < nRows; ++i)
    {
        inRow = inImg.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            // Get all the values
            v.push_back(inRow[j]);
        }
    }
    
    return static_cast<int>(StandardDeviation(v));
    
}


/// Standard deviation algorithm
template <class T>
double StandardDeviation(std::vector<T> &v)
{
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);

    return stdev;
}

/// Gets the mean value of an image
int GetMean(cv::Mat inImg)
{
    if (inImg.channels() != 1) { std::cerr << "Cannot apply threshold to non one-channeled image" << std::endl; return -1; }
    
    int nRows = inImg.rows;
    int nCols = inImg.cols;

    if (inImg.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* inRow;
    std::vector<int> v;
    for( i = 0; i < nRows; ++i)
    {
        inRow = inImg.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            // Get all the values
            v.push_back(inRow[j]);
        }
    }
    
    return static_cast<int>(Mean(v));
    
}

/// Standard deviation algorithm
template <class T>
double Mean(std::vector<T> &v)
{
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    return mean;
}

///
/// Median value of a std::vector<int>
/// @note: Gets the vector as copy, so the sorting does not affcet the original vector
/// @param std::vector<int>
/// @return int median
/// 
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

///
/// Replace all pixels of a specific color ina binarized image
/// Then "copys" the replaced pixels of the binarized image in input image (inImg) 
/// in order to get a colored view of the borders in the original image
/// This method assumes both images are the same
void SpecialReplacePixels(cv::Mat &inImg, cv::Mat &binImg, cv::Vec3b &marker)
{
    
    // Using fast pixel access to set the borders int he original image
    cv::Vec3b* row;
    uchar* rowBin;
    for (int i = 0; i < binImg.rows; ++i)
    {
        row = inImg.ptr<cv::Vec3b>(i);
        rowBin = binImg.ptr<uchar>(i);
        for (int j = 0; j < binImg.cols; ++j)
        {
            if(rowBin[j] == 255)
                row[j] = marker;
        }
    }
}

///
/// Flood fill every object detected on the image by DFS
void FloodFill(cv::Mat& inImg, cv::Mat& outImg)
{
    int MAXH = inImg.rows;
    int MAXW = inImg.cols;

    uchar border = 255;
    uchar spotted = 255;
    uchar current;

    Coordinate point;

    // Current for position
    cv::Vec3b marker;
    marker[2] = 0;
    marker[1] = 0;
    marker[0] = 255;

    // Current dfs position
    cv::Vec3b dfsMarker;
    dfsMarker[2] = 255;
    dfsMarker[1] = 0;
    dfsMarker[0] = 0;

    /// Create window
    //char* window_name = "Demo";
    int c;
    //cv::namedWindow( "Demo", CV_WINDOW_AUTOSIZE );

    std::stack<Coordinate> stack;
    std::vector<Coordinate> visited;

    // Things detected, including background
    int things = 0;

    for (int i = 0; i < MAXH - 1; i++)
    {
        for (int j = 0; j < MAXW - 1; j++)
        {
            //outImg.at<cv::Vec3b>(i, j) = marker;
            stack.push(Coordinate(j, i));

            current = inImg.at<uchar>(i, j);

            if(current != spotted && current != border)
                things ++;

            while(!stack.empty())
            {
                point = stack.top();
                stack.pop();
                if(inImg.at<uchar>(point.y, point.x) != spotted && inImg.at<uchar>(point.y, point.x) != border)
                {
                    // If not already spotted before
                    // Spot it and show it
                    inImg.at<uchar>(point.y, point.x) = spotted;
                    //outImg.at<cv::Vec3b>(point.y, point.x) = dfsMarker;

                    cv::imshow("Demo", inImg);
                    cv::waitKey(1);

                    /// Add neighbors to stack
                    /// They must be inside of bounds and must have not been spotted before
                    ///
                    // Below neighbor
                    if((point.y + 1 < MAXH - 1) && inImg.at<uchar>(point.y + 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y + 1));

                    // Above neighbor
                    if((point.y - 1 > 0) && inImg.at<uchar>(point.y - 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y - 1));

                    // Left neighbor
                    if((point.x - 1 > 0) && inImg.at<uchar>(point.y, point.x - 1) != spotted)
                        stack.push(Coordinate(point.x - 1, point.y));

                    // Right neighbor
                    if((point.x + 1 < MAXW - 1) && inImg.at<uchar>(point.y, point.x + 1) != spotted)
                        stack.push(Coordinate(point.x + 1, point.y));
                }
            }
        }
    }

    std::cout << things << std::endl;
}

/// Easy-way calling method
/// Assumes the image has not been binarized so it will do all the proccess
void DetectShapes(cv::Mat& inImg, cv::Mat& outImg)
{
    cv::Mat joinImg = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat imgAbs = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradY = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradX = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat bin = cv::Mat::zeros(inImg.size(), inImg.type());

    std::vector<Shape> shapes;

    // Supports n*n size
    /// As long it's odd sized and squared (same size for the 2 dimensions)
    /// Kernel.cpp for more info
    Kernel soby ({
            {1,2,1},
            {0,0,0},
            {-1,-2,-1}
    });

    Kernel sobx ({
            {-1,0,1},
            {-2,0,2},
            {-1,0,1}
    });

    /// Filters.cpp for more info
    Convolution(inImg, gradX, sobx);
    Convolution(inImg, gradY, soby);

    /// Filters.cpp for more info
    EuclidianJoin(gradX, gradY, joinImg);
    // AbsJoin(gradX, gradY, joinImg);

    /// Filters.cpp for more info
    //DeviationThreshold(joinImg, final);
    LazyThreshold(joinImg, bin);
    // MeanThreshold(joinImg, final);

    shapes = GetShapes(bin);

    DrawShapes(outImg, shapes);
}

///
/// Flood fill every object detected on the image by DFS
std::vector<Shape> GetShapes(cv::Mat& inImg)
{
    int MAXH = inImg.rows;
    int MAXW = inImg.cols;

    uchar border = 255;
    uchar spotted = 128;
    uchar current;

    Coordinate point;

    /// Create window
    //char* window_name = "Demo";
    //cv::namedWindow( "Demo", CV_WINDOW_AUTOSIZE );

    std::stack<Coordinate> stack;
    std::vector<Shape> shapes;
    int num = 0, sumX = 0, sumY = 0; // Used to get the center of mass on the go
    int _ob = -1;

    // Things detected, including background
    int things = 0;

    for (int i = 0; i < MAXH - 1; i++)
    {
        for (int j = 0; j < MAXW - 1; j++)
        {
            stack.push(Coordinate(j, i));
            current = inImg.at<uchar>(i, j);

            if(current != spotted && current != border)
            {
                //New object detected
                _ob++;
                shapes.push_back(Shape(std::to_string(_ob)));
            }

            while(!stack.empty())
            {
                point = stack.top();
                stack.pop();
                if(inImg.at<uchar>(point.y, point.x) != spotted && inImg.at<uchar>(point.y, point.x) != border)
                {
                    // If not already spotted before
                    // Spot it
                    inImg.at<uchar>(point.y, point.x) = spotted;
                    shapes[_ob].addCoordinate(Coordinate(point.x, point.y));

                    num++;
                    shapes[_ob].putValues(point.x, point.y, num);

                    // Show real time
                    //cv::imshow("Demo", inImg);
                    //cv::waitKey(1);

                    /// Add neighbors to stack
                    /// They must be inside of bounds and must have not been spotted before
                    // Below neighbor
                    if((point.y + 1 < MAXH - 1) && inImg.at<uchar>(point.y + 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y + 1));

                    // Above neighbor
                    if((point.y - 1 > 0) && inImg.at<uchar>(point.y - 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y - 1));

                    // Left neighbor
                    if((point.x - 1 > 0) && inImg.at<uchar>(point.y, point.x - 1) != spotted)
                        stack.push(Coordinate(point.x - 1, point.y));

                    // Right neighbor
                    if((point.x + 1 < MAXW - 1) && inImg.at<uchar>(point.y, point.x + 1) != spotted)
                        stack.push(Coordinate(point.x + 1, point.y));
                }
            }
        }
    }

    return shapes;
}


/// Gets a three channeled image (for now) and draw shapes properties in it
void DrawShapes(cv::Mat& inImg, std::vector<Shape> shapes)
{
    cv::RNG rng(9864);

    std::vector<Coordinate> box;
    for(Shape &shape : shapes)
    {
        // Get bounding box
        box = shape.getBoundingBox();

        // Draw rectangle
        int thickness = 2;
        cv::Scalar color = cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
        std::cout << color << std::endl;
        cv::Point pt1 (box[1].x, box[1].y);
        cv::Point pt2 (box[3].x, box[3].y);
        cv::rectangle(inImg,
                pt1,
                pt2,
                color,
                thickness
        );

        cv::putText(inImg,
                shape.getName(),
                pt1,
                CV_FONT_HERSHEY_PLAIN,
                2.0,
                color,
                2,
                8,
                false);

    }
}

template <typename T>
bool FindItem(std::vector<T>& mySet, Coordinate item)
{
    bool found = (std::find(mySet.begin(), mySet.end(), item) != mySet.end());
    return found;
}

/// 
/// Gets all the direct neighbors of a pixel and sets them into
/// std::vector<Vec3b> field -> Global variable
/// TODO: Optimize this, since the pixel access it's very slow
/// 
void DirectNeighbors(int x, int y, cv::Mat& img, std::vector<cv::Vec3b>& field)
{
    //cout << "x: " << x << endl;
    if(x == 0 && y == 0)
    {
        //Left-upper corner. Only 4 pixels needed
        //vector<cv::Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(2) = img.ptr<cv::Vec3b>(y+1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y+1)[x+1];
        
        return;
    }

    if(x == img.cols -1 && y == 0)
    {
        //Right-upper corner. Only 4 pixels needed
        //vector<cv::Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x-1];
        field.at(2) = img.ptr<cv::Vec3b>(y+1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y+1)[x-1];

        return;
    }

    if(x == 0 && y == img.rows - 1)
    {
        //Left-lower corner. Only 4 pixels needed
        //vector<cv::Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(2) = img.ptr<cv::Vec3b>(y-1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y-1)[x+1];

        return;
    }

    if(x == img.cols - 1 && y == img.rows - 1)
    {
        //Right-lower corner. Only 4 pixels needed
        //vector<cv::Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(2) = img.ptr<cv::Vec3b>(y-1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y-1)[x+1];

        return;
    }

    /* Check edges after */

    if(x > 0 && y == 0)
    {
        //Upper edge. Only 6 pixels needed
        //vector<cv::Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x-1];
        field.at(2) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(3) = img.ptr<cv::Vec3b>(y+1)[x-1];
        field.at(4) = img.ptr<cv::Vec3b>(y+1)[x];
        field.at(5) = img.ptr<cv::Vec3b>(y+1)[x+1];
        return;
    }

    if(x == 0 && y > 0)
    {
        //Left edge. Only 6 pixels needed
        //vector<cv::Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y-1)[x];
        field.at(2) = img.ptr<cv::Vec3b>(y+1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y-1)[x+1];
        field.at(4) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(5) = img.ptr<cv::Vec3b>(y+1)[x+1];
        return;
    }

    if(x == img.cols - 1 && y > 0)
    {
        //Right edge. Only 6 pixels needed
        //vector<cv::Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y-1)[x];
        field.at(2) = img.ptr<cv::Vec3b>(y+1)[x];
        field.at(3) = img.ptr<cv::Vec3b>(y-1)[x-1];
        field.at(4) = img.ptr<cv::Vec3b>(y)[x-1];
        field.at(5) = img.ptr<cv::Vec3b>(y+1)[x-1];
        return;
    }

    if(x > 0 && y == img.rows - 1)
    {
        //Bottom edge. Only 6 pixels needed
        //vector<cv::Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<cv::Vec3b>(y)[x];
        field.at(1) = img.ptr<cv::Vec3b>(y)[x-1];
        field.at(2) = img.ptr<cv::Vec3b>(y)[x+1];
        field.at(3) = img.ptr<cv::Vec3b>(y-1)[x-1];
        field.at(4) = img.ptr<cv::Vec3b>(y-1)[x];
        field.at(5) = img.ptr<cv::Vec3b>(y-1)[x+1];
        return;
    }

    /* No edges around the pixel. Return 9 pixels */
    //vector<cv::Vec3b> field(9);
    field.resize(9);
    field.at(0) = img.ptr<cv::Vec3b>(y-1)[x-1];
    field.at(1) = img.ptr<cv::Vec3b>(y-1)[x];
    field.at(2) = img.ptr<cv::Vec3b>(y-1)[x+1];
    field.at(3) = img.ptr<cv::Vec3b>(y)[x-1];
    field.at(4) = img.ptr<cv::Vec3b>(y)[x];
    field.at(5) = img.ptr<cv::Vec3b>(y)[x+1];
    field.at(6) = img.ptr<cv::Vec3b>(y+1)[x-1];
    field.at(7) = img.ptr<cv::Vec3b>(y+1)[x];
    field.at(8) = img.ptr<cv::Vec3b>(y+1)[y+1];

    return;
}