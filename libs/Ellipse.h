//
// Created by leind on 26/03/15.
//

#ifndef _ELIPSES_ELLIPSE_H_
#define _ELIPSES_ELLIPSE_H_

#include "Coordinate.h"

class Ellipse {
public:
    int a;
    int b;
    double alpha;
    Coordinate center;
    int votes;

    Ellipse();
    Ellipse(Coordinate center, int majorAxis, int minorAxis, double alpha, int votes);
};

struct less_than_key
{
    inline bool operator() (const Ellipse& a, const Ellipse& b)
    {
        return (a.votes < b.votes);
    }
};


#endif //_ELIPSES_ELLIPSE_H_
