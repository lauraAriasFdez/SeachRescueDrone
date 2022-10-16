/**
 * @file gaussian_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef GAUSSIAN_FILTER_H_
#define GAUSSIAN_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "convolution_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief A ConvolutionFilter that computes a gaussian kernel given a kernel
* size and sigma.
*/
class GaussianFilter:public ConvolutionFilter{
    /**
   * @brief A method that calculates a gaussian kernel given a kernel size and
   * sigma.
   *
   * @param[in] size An integer specifying the size of the kernel. Must be odd.
   * @param[in] sigma A float representing the sigma used to generate the kernel.
   *
   * @return float A unique pointer array containing the values for the gaussian
   * kernel from left to right, top to bottom, scaled so that the values add up
   * to 1.
   */
    std::unique_ptr<float[]> GaussianKernel(int size, float sigma);

public:
   /**
   * @brief Constructor that is called in parent constructor passing the 1 kernels
   * needed for the filter, calls the GaussianKernel method to generate the kernel.
   *
   */
    GaussianFilter(int size, float sigma):ConvolutionFilter(GaussianKernel(size, sigma), size, size, 1){}

protected:
    /**
    * @brief method that applies the mean blur filter to a single pixel.
    *
    * @param[in] original A vector of input images to apply the filter over.
    * @param[in] x An integer representing the width in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    * @param[in] y An integer representing the height in which the image color pixel is located, and
    * the pixel to which the filter should be applied.   
    *
    * @return A unique pointer array containing a Color for each filtered image the filter
    * should produce as an output, for the mean blur filter the vector should only contain one 
    * color object.
    */
    std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y);
};
#endif
