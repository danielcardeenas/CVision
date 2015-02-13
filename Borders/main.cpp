#include <iostream>

using namespace std;

int kernel[3][3] =
    {
        {1,0,1},
        {-2,0,2},
        {1,0,1}
    };
    
void foo (std :: initializer_list <int> inputs) {
    for (auto i : inputs) {
        cout << i << " " << endl;
    }
}
    
int main(int argc, char** argv)
{
    foo({
        {1,0,1},
        {-2,0,2},
        {1,0,1}
    });
}