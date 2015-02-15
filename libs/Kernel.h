#ifndef __KERNEL_H_INCLUDED__
#define __KERNEL_H_INCLUDED__

#include <iostream>
#include <vector>

#include "Coordinate.h"

class Kernel {
    private:
        Coordinate anchor;
        std::vector<std::vector<int> > kernel { {1,0,1},
                                                {-2,0,2},
                                                {1,0,1} };
    public:
        // Ctors
        Kernel(std::vector<std::vector<int> > v);
        Kernel(std::vector<std::vector<int> > v, Coordinate anchor);
        
        // Operators Overloads
        void operator <<=(std::vector<std::vector<int> > v);
        int operator [](Coordinate coo);
        
        class Proxy {
            public:
                Proxy(std::vector<int> _vector) : _vector(_vector) { }
        
                int operator[](int index) {
                    if(!(index >= _vector.size()))
                        return _vector[index];
                    else
                        std::cerr << "Out of Range error in Y axis: " << std::endl;
                }
            private:
                std::vector<int> _vector;
        };
        Proxy operator[](int index);
        
        // Bills the destroyer
        ~Kernel();

};

#endif // __KERNEL_H_INCLUDED__