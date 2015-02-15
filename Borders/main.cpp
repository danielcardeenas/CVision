#include <iostream>
#include "Kernel.h"

using namespace std;
    
int main(int argc, char** argv)
{
    std::vector<std::vector<int> > v;
    
    //Kernel sob;
    
    /*
    so << {
        {1,0,1},
        {-2,0,2},
        {1,0,1}
    };
    
    
    Kernel sob ({
        {1,0,1},
        {-2,0,2},
        {1,0,1}
    });
    
    sob <<= {
        {1,0,1},
        {-2,0,2},
        {1,0,1}
    };
    */
    
    Kernel keg(
        {{1,0,1},
        {-2,0,2},
        {1,0,1}}, Coordinate(2,3)
        );
    
    cout << keg[1][1] << endl;
    int d = keg[0][1];
    cout << d << endl;
    
    return 0;
}