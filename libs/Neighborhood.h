#ifndef __NEIGHBORHOOD_H_INCLUDED__
#define __NEIGHBORHOOD_H_INCLUDED__

#include "opencv2/opencv.hpp"

class Neighborhood {
    private:
        std::vector<std::vector<cv::Vec3b>> neighborhood;
    public:
        cv::Vec3b oned_neighborhood[9];
        void push(uchar r, uchar g, uchar b, int x);
        int sum(int index);
        cv::Vec3b pixel(int index);
        Neighborhood();
};

#endif // __NEIGHBORHOOD_H_INCLUDED__