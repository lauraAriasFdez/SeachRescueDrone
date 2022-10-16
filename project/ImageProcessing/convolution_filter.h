/**
 * @file convolution_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef CONVOLUTION_FILTER_H_
#define CONVOLUTION_FILTER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "related_pixel_filter.h"
#include "kernel.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief ConvolutionFilter is an abstract Filter class with a convolution kernel.
*  In order to compute the value of each pixel, surrounding pixels are multiplied
* by kernel values and then their values are added together.
*/
class ConvolutionFilter:public RelatedPixelFilter{
public:
    /**
    * @brief Empty convolution filter constructor
    */
    ConvolutionFilter(){};

	/**
    * @brief Constructor of a Convolution Filter with a specified kernels. It is
    * assumed that all kernels in the filter have the same dimensions
    *
    * @param[in] matrix A float unique pointer array containing all the values of 
    * each of the kernels.
    * @param[in] width An integer value that represents the width of a kernel.
    * @param[in] height An integer value that represents the height of a kernel.
    * @param[in] kernel_num An integer value that represents the number of a kernels that
    * this convolution filter holds.
    */
    ConvolutionFilter(std::unique_ptr<float[]> matrix, int width, int height, int kernel_num);

    /**
    * @brief Virtual destructor that is needed for polymorphism since derived classes constructors
    * need to be called.
    */
    virtual ~ConvolutionFilter(){};

protected:
    /**
    * @brief Pure virtual method to apply the derived filter to one single pixel taking into
    * consideration surrounding pixels.
    *
    * @param[in] original A vector of input images to apply the filter over.
    * @param[in] x An integer representing the width in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    * @param[in] x An integer representing the height in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    *
    * @return A unique pointer array containing a color for each filtered image the filter
    * should produce as an output
    */
    virtual std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y) = 0;

protected:
    std::vector<Kernel> kernel_filter; 
    int kernel_num;
};
#endif