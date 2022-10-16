/**
 * @file convolution_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "convolution_filter.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ConvolutionFilter::ConvolutionFilter(std::unique_ptr<float[]> matrix, int width, int height, int kernel_num){
    
    for (int i =0; i<kernel_num;i++){
        kernel_filter.push_back(Kernel(&matrix[width*height*i],width,height));
    }
    this->kernel_num = kernel_num;
}

