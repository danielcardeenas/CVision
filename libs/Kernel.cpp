#include "Kernel.h"

using namespace std;

/// Ctors first
Kernel::Kernel(std::vector<std::vector<int> > v) {
    this->anchor (1,1);
    this->kernel = v;
}

Kernel::Kernel(std::vector<std::vector<int> > v, Coordinate anchor) {
    this->kernel = v;
    this->anchor = anchor;
}

/// Mods the kernel of an already decalred object. No a constructor.
void Kernel::operator <<=(std::vector<std::vector<int> > v) {
    this->kernel = v;
}

/// Access kernel vector elements.
///

/// [Simple way] Array-like acces.
/// Using a proxy class instead (defined in Kernel.h)
/// For index error handling (Segmentation faults)
/// Ex: [x][y]
/// std::vector<int>& Kernel::operator[](int i){
///     return this->kernel[i];
/// }

/// Array-like access
/// Ex: [x][y]
Kernel::Proxy Kernel::operator[](int index) {
    if(!(index >= kernel.size()))
        return Proxy(kernel[index]);
    else
        std::cerr << "Out of Range error in X axis: " << endl;
}

/// Ex: kernel[coo]
int Kernel::operator [](Coordinate coo) {
    return this->kernel[coo.x][coo.y];
}

/// Destructor
Kernel::~Kernel() {
    kernel.clear();
}