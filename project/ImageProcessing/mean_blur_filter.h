/**
 * @file mean_blur_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef MEANBLUR_FILTER_H_
#define MEANBLUR_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "convolution_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief A ConvolutionFilter that computes the mean of all the surrounding pixels
* and replaces the central pixel by the avg value.
*
*/
class MeanBlurFilter:public ConvolutionFilter{
    
public:
   /**
   * @brief Constructor that call in parent constructor passing the kernels 
   * needed for the filter.
   *
   */
    MeanBlurFilter():ConvolutionFilter(std::move(std::unique_ptr<float[]> (new float[9] {1,1,1,1,1,1,1,1,1})), 3, 3, 1){}

protected:
    /**
    * @brief A method that applies the mean blur filter to a single pixel.
    *
    * @param[in] original A vector  of input images to apply the filter over.
    * @param[in] x An integer representing the width in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    * @param[in] y An integer representing the height in which the image color pixel is located, and
    * the pixel to which the filter should be applied.  
    *
    * @return A unique pointer array containing a Color for each filtered image the filter
    * should produce as an output, for the mean blur filter the vector should only contain one 
    * Color object.
    */
    std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y);
};
#endif
