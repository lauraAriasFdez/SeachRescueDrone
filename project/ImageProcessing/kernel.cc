/**
 * @file kernel.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 
/*******************************************************************************
* Includes
******************************************************************************/
#include "kernel.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
Kernel::Kernel(float* matrix, int width, int height){
    // make a deep copy of the kernel values matrix
    this->matrix = std::unique_ptr<float[]>(new float[width*height]);
    for(int i=0; i<(width*height);i++){
        this->matrix[i] = matrix[i];
    }
    this->width = width;
    this->height = height;
}
// Copy Constructor 
void Kernel::operator=(const Kernel& kernel){
    this->width = kernel.width;
    this->height = kernel.height;

    int size = kernel.width*kernel.height;

    this->matrix = std::unique_ptr<float[]>(new float[size]);

    // copy value by value -deep copy 
    for(int i=0; i<size;i++){
        this->matrix[i] = kernel.matrix[i];
    }
}

Kernel::Kernel(const Kernel& kernel){
    *this = kernel; // Calls assigment operator through overloading 
}

float Kernel::GetKernelComponent(int x, int y) const{
    // checks that we can actually index kernel 
    if (width>x && height >y){
        return matrix[(x*width) + y];
    }
    // if we cannot index it we return 0.0 as the value
    return 0.0;
}