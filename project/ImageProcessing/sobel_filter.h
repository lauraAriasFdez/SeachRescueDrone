/**
 * @file sobel_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "convolution_filter.h"
#include <math.h>       /* atanf, powf and pow*/
#include <iostream>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PI 3.14159265

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A filter that iterates two different kernels over an image to extract 
 * horizontal and vertical lines, then combine them using Euclidean distance.
 * The result is an intensify matrix represented by and image, as well as, a 
 * direction matrix, in degrees, of edges, also represented by an image.
 */
class SobelFilter:public ConvolutionFilter{
    
public:
   /**
   * @brief Constructor that call in parent constructor passing the 2 kernels 
   * needed for the filter.
   */
    SobelFilter():ConvolutionFilter(
        std::move(std::unique_ptr<float[]> (new float[18] {-1,0,1,-2,0,2,-1,0,1,1,2,1,0,0,0,-1,-2,-1})),
        3, 3, 2){}

protected:
    /**
    * @brief Applies the Sobel filter to one single pixel, taking into consideration 
    * the necessary surrounding pixels.
    *
    * @param original A vector of images needed to take into consideration to produce
    * the filtered pixel.
    * @param[in] x An integer representing the x-position of the pixel the filter should be applied to.
    * @param[in] y An integer representing the y-position of the pixel the filter should be applied to.
    *
    * @return A vector of Colors, each representing the new color value for a filtered
    * image's pixel located at (x,y).
    */
    std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y);
};
#endif
