#ifndef __KERNEL_H_INCLUDED__
#define __KERNEL_H_INCLUDED__

#include <iostream>
#include <vector>
#include <algorithm>

#include "Coordinate.h"

class Kernel {
    private:
        // Vars
        Coordinate anchor;
        std::vector<std::vector<int> > kernel { {-1,0,1},
                                                {-2,0,2},
                                                {-1,0,1} };
                                                
        // Functions        
        bool IsValidAnchor (Coordinate a);
        int KernelSummation();
        
    public:
        // Vars
        bool isNormalized = false;
        int normal = 0;
    
        // Ctors
        Kernel();
        Kernel(std::vector<std::vector<int> > v);
        Kernel(std::vector<std::vector<int> > v, Coordinate anchor);
        
        // Operators Overloads
        void operator <<=(std::vector<std::vector<int> > v);
        int operator [](Coordinate coo);
        
        class Proxy {
            public:
                Proxy(std::vector<int> _vector) : _vector(_vector) { }
                
                int& operator[](int index) {
                    if(!(index >= _vector.size() || index < 0))
                        return _vector[index];
                    else
                        std::cerr << "Out of Range error in Y axis: " << std::endl;
                }
                
            private:
                std::vector<int> _vector;
        };
        Proxy operator[](int index);
        
        // Functions
        int size();
        
        // Bills the destroyer
        ~Kernel();

};

#endif // __KERNEL_H_INCLUDED__