#include "Kernel.h"

using namespace std;

/// Ctors first
Kernel::Kernel() {
    this->anchor (1, 1);
}

Kernel::Kernel(std::vector<std::vector<int> > v) {
    /// If kernel is not odd sized, set the default
    if(v.size() % 2 == 0 || v[0].size() % 2 == 0)
        std::cout << "Kernel must be odd sized\nSetting default Sobel Y(3x3)" << endl;
    else
        this->kernel = v;
    
    /// Veryfy anchor is not out of the range of the kernel
    if (kernel.size() > 1 && kernel[0].size() > 1)
        this->anchor (1, 1);
    else
        this->anchor (0, 0);
        
    /// If the sum of the elements is 0
    /// Do not normalize, since is a magnitude kernel
    int normal = KernelSummation();
    
    if (normal == 0)
        this->isNormalized = false;
    else{
        this->normal = normal;
        this->isNormalized = true;
    }
}

Kernel::Kernel(std::vector<std::vector<int> > v, Coordinate anchor) {
    this->kernel = v;
    
    if(IsValidAnchor(anchor))
        this->anchor = anchor;
    else{
        std::cout << "Anchor outside kernel range.\nSetting anchor default" << endl;
        if (kernel.size() > 1 && kernel[0].size() > 1)
            this->anchor (1, 1);
        else
            this->anchor (0, 0);
    }
    
    /// If the sum of the elements is 0
    /// Do not normalize, since is a magnitude kernel
    int normal = KernelSummation();
    
    if (normal == 0)
        this->isNormalized = false;
    else{
        this->normal = normal;
        this->isNormalized = true;
    }
}

/// Mods the kernel of an already decalred object. No a constructor.
void Kernel::operator <<=(std::vector<std::vector<int> > v) {
    /// If kernel is not odd sized, set the default
    if(v.size() % 2 == 0 || v[0].size() % 2 == 0)
        std::cout << "Kernel must be odd sized\nSetting default Sobel Y(3x3)" << endl;
    else
        this->kernel = v;
    
    /// Veryfy anchor is not out of the range of the kernel
    if (kernel.size() > 1 && kernel[0].size() > 1)
        this->anchor (1, 1);
    else
        this->anchor (0, 0);
    
    /// If the sum of the elements is 0
    /// Do not normalize, since is a magnitude kernel
    int normal = KernelSummation();
    
    if (normal == 0)
        this->isNormalized = false;
    else{
        this->normal = normal;
        this->isNormalized = true;
    }
}

/// Access kernel vector elements.

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
    if(!(index >= kernel.size() || index < 0))
        return Proxy(kernel[index]);
    else
        std::cerr << "Out of Range error in X axis: " << endl;
}

/// Access an element of the kernel givena Coordinate (Class)
/// Ex: kernel[coo]
int Kernel::operator [](Coordinate coo) {
    return this->kernel[coo.x][coo.y];
}

bool Kernel::IsValidAnchor (Coordinate a) {
    if (a.x < 0 || a.y < 0)
        return false;
    else if (a.x >= this->kernel.size() || a.y >= this->kernel[0].size())
        return false;
    else 
        return true;
}

int Kernel::size() {
    return this->kernel.size();
}

int Kernel::KernelSummation() {
    int temp = 0;
    for(int i=0; i < this->kernel.size(); i++)
        for(int j=0; j < this->kernel[0].size(); j++)
            temp += kernel[i][j];
            
    return temp;
}

/// Destructor
Kernel::~Kernel() {
    kernel.clear();
}