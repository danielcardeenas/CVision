#ifndef __COORDINATE_H_INCLUDED__
#define __COORDINATE_H_INCLUDED__

class Coordinate {
    public:
        int x;
        int y;
        Coordinate(int x, int y);
        Coordinate();
        
        void operator ()(int x, int y);
        void operator =(Coordinate c);
};

inline bool operator ==(const Coordinate &left, const Coordinate &right) {
    return (left.x == right.x &&
            left.y == right.y);
}

inline bool operator < (const Coordinate &left, const Coordinate &right) {
    return left.x < right.x;
}

#endif // __COORDINATE_H_INCLUDED__