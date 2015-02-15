#ifndef __COORDINATE_H_INCLUDED__
#define __COORDINATE_H_INCLUDED__

class Coordinate {
    public:
        int x;
        int y;
        
        Coordinate(int x, int y);
        Coordinate();
        
        void operator ()(int x, int y);
};

#endif // __COORDINATE_H_INCLUDED__