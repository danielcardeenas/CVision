#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ComputeMedian(int& x, int& y);
void PixelNeighbors(int x, int y);
int Median(vector<int>& vec);

int corner = 0;
Mat out_img, img;
vector<Vec3b> field;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Usage .median <image_to_mod>" << endl;
        return -1;
    }

    //img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    //out_img = img.clone();
    //for(int y = 0; y < img.rows; y++)
    //for(int x = 0; x < img.cols; x++)
    //out_img.at<uchar>(y,x) = 0.0;
    out_img = Mat::zeros(img.size(), img.type());

    if(!img.data)
    {
        cout << "Could not load the image" << endl;
    }



    cout << "Cols: " << img.cols << endl;
    cout << "Rows: " << img.rows << endl;
    // Start getting pixels
    for(int y=0; y<img.rows; y++)
        for(int x=0; x<img.cols; x++)
        {
            ComputeMedian(x, y);
        }

    cout << "Cornerns: " << corner << endl;

    imshow("Original", img);
    imshow("Median", out_img);
    //imwrite("entei.jpg", out_img);

    while(waitKey(1) != 27);
    return 0;
}

void ComputeMedian(int& x, int& y)
{
    // Check borders
    PixelNeighbors(x, y);

    // Set sortable values to vector
    //vector<BGR> pixValues(field.size());
    vector<int> blue (field.size());
    vector<int> green (field.size());
    vector<int> red (field.size());

    for(int i = 0; i < field.size(); ++i)
    {
        blue.at(i) = field.at(i)[0]; //B
        green.at(i) = field.at(i)[1]; //G
        red.at(i) = field.at(i)[2]; //R
    }

    //Median
    int medBlue = Median(blue);
    int medGreen = Median(green);
    int medRed = Median(red);

    Vec3b color;
    color[0] = medBlue;
    color[1] = medGreen;
    color[2] = medRed;

    out_img.at<Vec3b>(Point(x,y)) = color;

    vector<Vec3b>().swap(field);
}

void PixelNeighbors(int x, int y)
{
    //cout << "x: " << x << endl;
    if(x == 0 && y == 0)
    {
        //Left-upper corner. Only 4 pixels needed
        //vector<Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x+1];
        field.at(2) = img.ptr<Vec3b>(y+1)[x];
        field.at(3) = img.ptr<Vec3b>(y+1)[x+1];

        cout << "L-U" << endl;
        corner += 1;
        return;
    }

    if(x == img.cols -1 && y == 0)
    {
        //Right-upper corner. Only 4 pixels needed
        //vector<Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x-1];
        field.at(2) = img.ptr<Vec3b>(y+1)[x];
        field.at(3) = img.ptr<Vec3b>(y+1)[x-1];

        cout << "R-U" << endl;
        corner += 1;
        return;
    }

    if(x == 0 && y == img.rows - 1)
    {
        //Left-lower corner. Only 4 pixels needed
        //vector<Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x+1];
        field.at(2) = img.ptr<Vec3b>(y-1)[x];
        field.at(3) = img.ptr<Vec3b>(y-1)[x+1];

        cout << "L-L" << endl;
        corner += 1;
        return;
    }

    if(x == img.cols - 1 && y == img.rows - 1)
    {
        //Right-lower corner. Only 4 pixels needed
        //vector<Vec3b> field(4);
        field.resize(4);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x+1];
        field.at(2) = img.ptr<Vec3b>(y-1)[x];
        field.at(3) = img.ptr<Vec3b>(y-1)[x+1];

        cout << "R-L" << endl;
        corner += 1;
        return;
    }

    /* Check edges after */

    if(x > 0 && y == 0)
    {
        //Upper edge. Only 6 pixels needed
        //vector<Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x-1];
        field.at(2) = img.ptr<Vec3b>(y)[x+1];
        field.at(3) = img.ptr<Vec3b>(y+1)[x-1];
        field.at(4) = img.ptr<Vec3b>(y+1)[x];
        field.at(5) = img.ptr<Vec3b>(y+1)[x+1];
        return;
    }

    if(x == 0 && y > 0)
    {
        //Left edge. Only 6 pixels needed
        //vector<Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y-1)[x];
        field.at(2) = img.ptr<Vec3b>(y+1)[x];
        field.at(3) = img.ptr<Vec3b>(y-1)[x+1];
        field.at(4) = img.ptr<Vec3b>(y)[x+1];
        field.at(5) = img.ptr<Vec3b>(y+1)[x+1];
        return;
    }

    if(x == img.cols - 1 && y > 0)
    {
        //Right edge. Only 6 pixels needed
        //vector<Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y-1)[x];
        field.at(2) = img.ptr<Vec3b>(y+1)[x];
        field.at(3) = img.ptr<Vec3b>(y-1)[x-1];
        field.at(4) = img.ptr<Vec3b>(y)[x-1];
        field.at(5) = img.ptr<Vec3b>(y+1)[x-1];
        return;
    }

    if(x > 0 && y == img.rows - 1)
    {
        //Bottom edge. Only 6 pixels needed
        //vector<Vec3b> field(6);
        field.resize(6);
        field.at(0) = img.ptr<Vec3b>(y)[x];
        field.at(1) = img.ptr<Vec3b>(y)[x-1];
        field.at(2) = img.ptr<Vec3b>(y)[x+1];
        field.at(3) = img.ptr<Vec3b>(y-1)[x-1];
        field.at(4) = img.ptr<Vec3b>(y+1)[x];
        field.at(5) = img.ptr<Vec3b>(y-1)[x+1];
        return;
    }

    /* No edges around the pixel. Return 9 pixels */
    //vector<Vec3b> field(9);
    field.resize(9);
    field.at(0) = img.ptr<Vec3b>(y-1)[x-1];
    field.at(1) = img.ptr<Vec3b>(y-1)[x];
    field.at(2) = img.ptr<Vec3b>(y-1)[x+1];
    field.at(3) = img.ptr<Vec3b>(y)[x-1];
    field.at(4) = img.ptr<Vec3b>(y)[x];
    field.at(5) = img.ptr<Vec3b>(y)[x+1];
    field.at(6) = img.ptr<Vec3b>(y+1)[x-1];
    field.at(7) = img.ptr<Vec3b>(y+1)[x];
    field.at(8) = img.ptr<Vec3b>(y+1)[x+1];

    return;

}

int Median(vector<int>& vec)
{
    int median;
    size_t size = vec.size();

    // Sort
    sort(vec.begin(), vec.end());

    if (size  % 2 == 0)
        median = (vec[size / 2 - 1] + vec[size / 2]) / 2;
    else
        median = vec[size / 2];

    return median;
}
