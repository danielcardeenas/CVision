#include <iostream>
#include "Utils.h"
#include "Coordinate.h"

std::vector<cv::Vec3b> neighbors;

/**
 * Gets all the direct neighbors of a pixel and sets them into
 * std::vector<Vec3b> field -> Global variable
 * [3][3] -> [9]
*/
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

/**
 * Fills a 2D vector<Vec3b> with the neighbors of the pixel in the Coordenate given
 * @param:
 *  Coordinate coo = Coordinate of the pixel in the image
 *  Mat img = The input image
 *  [OUTPUT] vector<vector<Vec3b>>& neighborhood = The neighboorhood to set
*/

void XYNeighbors(Coordinate coo, cv::Mat& img, std::vector<std::vector<cv::Vec3b>>& neighborhood)
{
    
     // int _x: X axis of neighbors requested
     // int _y: Y azis of neighbors requested
     int _x = neighborhood.size();
     int _y = neighborhood[0].size();
    
    // Iterating trough pixels
    for(int i = 0; i > _x; i++)
        for(int j = 0; j > _y; j++)
        {
            neighborhood[i][j] = img.ptr<cv::Vec3b>(coo.y+j)[coo.x+i];
        }
        
    return;
}