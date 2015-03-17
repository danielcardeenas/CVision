#include <iostream>
#include <stack>
#include <set>
#include <map>

#include "Utils.h"
#include "Coordinate.h"
#include "Shape.h"
#include "Filters.h"
#include "Kernel.h"

/// RAD = 0.017453293f (π / 180). Used to convert to radians
#define RAD 0.017453293f

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
    /**
    * Binarize image
    */
    cv::Mat joinImg = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat imgAbs = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradY = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat gradX = cv::Mat::zeros(inImg.size(), inImg.type());
    cv::Mat bin = cv::Mat::zeros(inImg.size(), inImg.type());

    // Supports n*n size
    /// As long it's odd sized and squared
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
    DeviationThreshold(joinImg, inImg);
    //LazyThreshold(joinImg, inImg);

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
    dfsMarker[1] = 145;
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

                    //cv::imshow("Demo", outImg);
                    //cv::waitKey(1);

                    /// Add neighbors to stack
                    /// They must be inside of bounds and must have not been spotted before
                    ///
                    // Below neighbor
                    if((point.y + 1 < MAXH) && inImg.at<uchar>(point.y + 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y + 1));

                    // Above neighbor
                    if((point.y - 1 > 0) && inImg.at<uchar>(point.y - 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y - 1));

                    // Left neighbor
                    if((point.x - 1 > 0) && inImg.at<uchar>(point.y, point.x - 1) != spotted)
                        stack.push(Coordinate(point.x - 1, point.y));

                    // Right neighbor
                    if((point.x + 1 < MAXW) && inImg.at<uchar>(point.y, point.x + 1) != spotted)
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
    std::vector<Shape> shapes;
    shapes = GetShapes(inImg);

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
                    if((point.y + 1 < MAXH) && inImg.at<uchar>(point.y + 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y + 1));

                    // Above neighbor
                    if((point.y - 1 > 0) && inImg.at<uchar>(point.y - 1, point.x) != spotted)
                        stack.push(Coordinate(point.x, point.y - 1));

                    // Left neighbor
                    if((point.x - 1 >= 0) && inImg.at<uchar>(point.y, point.x - 1) != spotted)
                        stack.push(Coordinate(point.x - 1, point.y));

                    // Right neighbor
                    if((point.x + 1 < MAXW) && inImg.at<uchar>(point.y, point.x + 1) != spotted)
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
        //std::cout << color << std::endl;
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

/// Get histogram from grayscale
std::map<uchar, int> CalcROIHistogram(std::vector<std::vector<uchar> > &I)
{
    int bins = 256; // number of bins
	std::map<uchar, int> hist;

	uchar val;

	// Calculate the histogram of the ROI
	for (int i = 0; i < I.size(); i++)
	{
		for (int j = 0; j < I[0].size(); j++)
		{
			val = I[i][j];
			hist[val] += 1;
		}
	}

	return hist;
}

void CustomDetectLines(cv::Mat &gradX, cv::Mat &gradY, cv::Mat &outImg)
{
    int nRows = gradX.rows;
    int nCols = gradX.cols;

    if (gradX.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    double theta, r;
    int x, y;

    uchar border = 255;
    cv::Vec3b marker;
    marker[0] = 0;
    marker[1] = 255;
    marker[2] = 0;

    cv::Vec3b markerBlue;
    markerBlue[0] = 0;
    markerBlue[1] = 255;
    markerBlue[2] = 255;

    int i,j;
    uchar* xRow;
    uchar* yRow;
    cv::Vec3b* colorRow;
    for( i = 0; i < nRows; ++i)
    {
        xRow = gradX.ptr<uchar>(i);
        yRow = gradY.ptr<uchar>(i);
        colorRow = outImg.ptr<cv::Vec3b>(i);
        for ( j = 0; j < nCols; ++j)
        {
            if(xRow[j] == border || yRow[j] == border)
            {
                x = xRow[j];
                y = yRow[j];

                theta = atan2(y, x);
                r = (x*cos(theta)) + (y * sin(theta));

                if (theta == 0)
                    colorRow[j] = marker;
                else if (theta > 0.7)
                    colorRow[j] = markerBlue;

                std::cout << theta << " - " << r << std::endl;

                cv::imshow("tim", outImg);
                cv::waitKey(1);
            }
        }
    }
}

///
/// Hough Line Transform
/// Sets the votes inside an accumulator
/// Calls the functions that draws the lines
void DetectLines(cv::Mat &inImg, cv::Mat &outImg, int threshold)
{
    int imgW = inImg.cols;
    int imgH = inImg.rows;

    ///
    /// Accumulator -> Memory block cause yolo
    /// Hough Space:
    ///     accuH = height of accumulator (from -rho -> 0 -> +rho)
    ///     accuW = width of accumulator (theta)
    unsigned int* accu;
    double hough_h = ((sqrt(2.0) * (double)(imgH > imgW?imgH: imgW)) / 2.0);
    int accuH = hough_h * 2.0; // -rho -> +rho
    int accuW = 180; // 0° -> 179°
    accu = (unsigned int*)calloc(accuH * accuW, sizeof(unsigned int));

    /// Center of the img
    /// Used to work with polar coordinates
    double center_x = imgW/2;
    double center_y = imgH/2;

    double rho;

    uchar *inRow;
    for(int y = 0; y < imgH; y++)
    {
        //inRow = inImg.ptr<uchar>(y);
        for(int x = 0; x < imgW; x++)
        {
            // If border tocuhed
            if( inImg.data[ (y*imgW) + x] > 250)
            {
                // Calculate rho from θ = 0° to θ = 179° and vote
                for(int t = 0; t < 180; t++)
                {
                    ///
                    /// Use polar coordinates
                    /// RAD = 0.017453293f (π / 180). Used to convert to radians
                    /// rho = x.cos(θ) + y.sin(θ)
                    rho = (((double)x - center_x) * cos((double)t * RAD)) + (((double)y - center_y) * sin((double)t * RAD));

                    // Add a vote
                    accu[ (int)((round(rho + hough_h) * 180.0)) + t]++;
                }
            }
        }
    }

    //auto threshold: imgW > imgH? imgW/4: imgH/4
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines = GetLines(threshold, accu, accuH, accuW, imgH, imgW);
    DrawLines(lines, outImg);
}

///
/// Returns a vector with pairs of coordinates:
/// [(x1, y1), (x2, y2)]
/// Only lines with an amount of votes above the threshold are selected
/// TODO: Make a Class for Line instead of returning this pairs inside a pair inside a vector
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> GetLines(int threshold, unsigned int * &accu, int accuH, int accuW, int imgH, int imgW)
{
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;
    if(accu == 0)
        return lines;

    for(int r = 0; r < accuH ; r++)
    {
        for(int t = 0; t < accuW; t++)
        {
            if((int)accu[(r*accuW) + t] >= threshold)
            {
                int max = accu[(r*accuW) + t];
                for(int ly= -4; ly <= 4; ly++)
                {
                    for(int lx = -4; lx <= 4; lx++)
                    {
                        if((ly + r >= 0 && ly + r < accuH) && (lx + t >= 0 && lx + t < accuW))
                        {
                            if((int)accu[((r+ly)*accuW) + (t+lx)] > max)
                            {
                                max = accu[( (r+ly)*accuW) + (t+lx)];
                                ly = lx = 5;
                            }
                        }
                    }
                }
                if(max > (int)accu[(r*accuW) + t])
                    continue;


                int x1, y1, x2, y2;
                x1 = y1 = x2 = y2 = 0;

                if(t >= 45 && t <= 135)
                {
                    //y = (r - x cos(t)) / sin(t)
                    x1 = 0;
                    y1 = ((double)(r-(accuH/2)) - ((x1 - (imgW/2) ) * cos(t * RAD))) / sin(t * RAD) + (imgH / 2);
                    x2 = imgW - 0;
                    y2 = ((double)(r-(accuH/2)) - ((x2 - (imgW/2) ) * cos(t * RAD))) / sin(t * RAD) + (imgH / 2);
                }
                else
                {
                    //x = (r - y sin(t)) / cos(t);
                    y1 = 0;
                    x1 = ((double)(r-(accuH/2)) - ((y1 - (imgH/2) ) * sin(t * RAD))) / cos(t * RAD) + (imgW / 2);
                    y2 = imgH - 0;
                    x2 = ((double)(r-(accuH/2)) - ((y2 - (imgH/2) ) * sin(t * RAD))) / cos(t * RAD) + (imgW / 2);
                }

                lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1,y1), std::pair<int, int>(x2,y2)));

            }
        }
    }

    std::cout << "lines: " << lines.size() << " " << threshold << std::endl;
    free(accu);
    return lines;
}

///
/// Draw lines in img
void DrawLines(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &lines, cv::Mat &outImg)
{
    int id = 0;
    double m = 0;
    double y = 0;
    cv::RNG rng(98342);
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >::iterator it;
    for(it = lines.begin(); it != lines.end(); it++)
    {
        // Draw line
        cv::line(outImg, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second),
                cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8);

        m = (it->second.second - it->first.second) / (it->second.first - it->first.first);
        std::cout << "Line " << id << ":\ny = " << "m" << "x + " << it->first.second << std::endl;
        id++;
    }
}

///
/// Hough Circles Transform
/// @param:
///     cv::Mat &inImg: input image
///      cv::Mat &outImg: output image
///      int threshold: [auto if not defined]
///      int minRadius: [20 if not defined],
///      int maxRadius: [250 if not defined],
///      int step : [4 if not defined]
void DetectCircles(cv::Mat &inImg, cv::Mat &outImg, int threshold, int minRadius, int maxRadius, int step)
{
    const int width = inImg.cols;
    const int height = inImg.rows;

    const int accuH = height;
    const int accuW = width;

    ///
    /// Accumulator for votes -> memory block
    /// Set to nullptr because another function will manage the accumulator (free and fill)
    /// And another function will read from it
    /// So I need it in the same scope
    unsigned int* _accu = nullptr;

    // [(x₀, y₀), radious]
    // Should make a class for this instead of this mess. Sorry
    std::vector< std::pair< std::pair<int, int>, int> > circles;

    if (step <= 0)
        step = 2;

    /// Iterate
    for (int r = minRadius; r < maxRadius; r = r + step)
    {

        HoughCircleTransform(inImg.data, width, height, r, _accu);

        if (threshold == 0)
            threshold = 0.95 * (2.0 * (double)r * M_PI);

        //Search the accumulator
        GetCircles(threshold, circles, r, _accu, accuH, accuW);

        //Draw the results
        int maxa = 0;

        for (int p = 0; p < (accuH * accuW); ++p)
        {
            if ((int) _accu[p] > maxa)
                maxa = _accu[p];
        }

        double contrast = 1.0;
        double coef = 255.0 / (double)maxa * contrast;

        // Visualize accumulator graphic
        /*
        cv::Mat accuGraph(accuH, accuW, CV_8UC3);
        for(int p = 0; p < (accuH * accuW); ++p)
        {
            unsigned char c = (double)accu[p] * coef < 255.0 ? (double)accu[p] * coef : 255.0;
            accuGraph.data[(p*3)+0] = 255;
            accuGraph.data[(p*3)+1] = 255-c;
            accuGraph.data[(p*3)+2] = 255-c;
        }
        */


        cv::imshow("out", inImg);
        //cv::imshow(CW_ACCUMULATOR, accuGraph);

        cv::waitKey(1);


    } //.For each radius in value

    // Sort
    std::sort(circles.begin(), circles.end(), SortCirclesDistance());

    int a, b, radius;
    a = b = radius = 0;

    std::vector< std::pair< std::pair<int, int>, int> > chosenCircles;
    std::vector< std::pair< std::pair<int, int>, int> >::iterator it;
    for(it = circles.begin(); it != circles.end(); ++it)
    {
        int d = sqrt( pow(abs(it->first.first - a), 2) + pow(abs(it->first.second - b), 2) );
        if( d > it->second + radius)
        {
            chosenCircles.push_back(*it);
            a = it->first.first;
            b = it->first.second;
            radius = it->second;
        }
    }

    // Draw
    std::cout << "Centers: " << std::endl;
    for(it = chosenCircles.begin(); it != chosenCircles.end(); ++it)
    {
        cv::Point center(it->first.first,
                         it->first.second);

        // Draw center
        cv::circle(outImg,
                center,
                3,
                cv::Scalar(0,255,0),
                -1,
                8,
                0);

        std::cout <<"(" << it->first.first << ", " << it->first.second << ")" << std::endl;

        // Draw radius
        /*
        cv::line(outImg,
                cv::Point(it->first.first, it->first.second),
                cv::Point(it->first.first + it->second, it->first.second),
                cv::Scalar(255, 255, 255),
                1,
                8);


        std::string text = "r: " + std::to_string(it->second);
        cv::putText(outImg,
                text,
                cv::Point(it->first.first + 6, it->first.second - 6),
                CV_FONT_HERSHEY_PLAIN,
                .6,
                cv::Scalar(0, 0, 0),
                1,
                8,
                false);
        */

        // Draw circle
        cv::circle(outImg,
                cv::Point(it->first.first, it->first.second),
                it->second,
                cv::Scalar(0, 176, 255),
                3,
                8);
    }

    // Dealloc memory
    free(_accu);

    std::cout << "Finished" << std::endl;
    cv::imshow("out", outImg);
    cv::waitKey(360000);
}

///
/// In charge of accumulating votes
void HoughCircleTransform(unsigned char* img_data, int width, int height, int r, unsigned int* &accu)
{
    int _r = r;

    int accuH = height;
    int accuW = width;

    if(accu)
        free(accu);

    accu = (unsigned int*)calloc(accuH * accuW, sizeof(unsigned int));

    int a, b = 0;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (img_data[(y * width) + x] > 250)
            {
                for (int t = 1; t <= 360; ++t)
                {
                    ///
                    /// a -> x₀ = x - R * cos(θ)
                    /// b -> y₀ = y - R * sin(θ)
                    a = ((double)x - ((double)_r * cos((double)t * RAD)));
                    b = ((double)y - ((double)_r * sin((double)t * RAD)));

                    // Just in case
                    if ((b >= 0 && b < accuH) && (a >= 0 && a < accuW))
                        accu[(b * accuW) + a]++;
                }
            }
        }
    }

    return;
}

///
/// Decides wether or not the votes in the accumulator are centers of circles
void GetCircles(int threshold, std::vector<std::pair<std::pair<int, int>, int>>& circles, int r, unsigned int* &accu, const int accuH, const int accuW)
{
    int _r = r;

    int found = 0;
    // Not needed.

    if (accu == 0)
        return;

    for (int b = 0;b < accuH; ++b)
    {
        for (int a = 0; a < accuW; ++a)
        {
            if ((int)accu[(b * accuW) + a] >= threshold)
            {
                //Is this point a local maxima (9x9)
                int max = accu[(b*accuW) + a];
                for (int ly = -4; ly <= 4; ++ly)
                {
                    for (int lx = -4; lx <= 4; ++lx)
                    {
                        if ((ly+b >= 0 && ly + b < accuH) && (lx + a >=0 && lx + a <accuW))
                        {
                            if ((int)accu[((b + ly) * accuW) + (a + lx)] > max)
                            {
                                max = accu[( (b+ly)*accuW) + (a+lx)];
                                ly = lx = 5;
                            }
                        }
                    }
                }
                if (max > (int)accu[(b*accuW) + a])
                    continue;

                circles.push_back(std::pair< std::pair<int, int>, int>(std::pair<int, int>(a,b), _r));
                found++;

            }
        }
    }
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
