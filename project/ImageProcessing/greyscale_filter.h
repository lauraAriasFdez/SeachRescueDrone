/**
 * @file greyscale_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef GREYSCALE_FILTER_H_
#define GREYSCALE_FILTER_H_

/*******************************************************************************
 * Includes
******************************************************************************/
#include "simple_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Greyscale filter is a SimpleFilter that sets RGB vales for each pixel in an image to be the
 * luminance of the pixel.
 */
class GreyScaleFilter:public SimpleFilter{
protected:
    /**
    * @brief Applies the filter to one single pixel.
    *
    * @param[in] image A constant pointer to an instance of the Image class.
    * @param[in] pixel Color object representing the pixel to apply the GrayScale filter.
    *
    * @return A Color object representing the pixel after the filter has been applied.
    */
    Color ApplyAtPixel (const Image* image,const Color& pixel);
};
#endif