#ifndef __PIXEL_H_INCLUDED__
#define __PIXEL_H_INCLUDED__

#include "opencv2/opencv.hpp"

class Pixel{
    public:
        Pixel();
    private:
        uchar r, g, b; // RGB pixels (Duh)
        uchar g // Grayscale pixel
}

/**
 * Not using this right now
 * 
template<typename T, int b>
class Pixel:public cv::Vec<T, b> {
    public:
        typedef T value_type;
        enum { channels = b};
};

typedef Pixel<uchar, 3> Pixel3b; // BGR
typedef Pixel<uchar, 4> Pixel4b; // BGRA

typedef Pixel<double, 3> Pixel3d; // BGR
typedef Pixel<double, 4> Pixel4d; // BGRA
*
*/
#endif // __PIXEL_H_INCLUDED__