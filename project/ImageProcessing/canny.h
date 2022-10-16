/**
 * @file canny.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef CANNY_H_
#define CANNY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A filter that applies the greyscale, gaussian, sobel, non-max suppression, 
 * double threshold, and hysteresis filters to an Image.
 */
class Canny:public Filter{ 
public:
    /**
    * @brief method that applies all the filters required for canny edge detection
    *
    * @param original A vector  of input images to apply the filter over.
    * @param filtered  A vector of output images that displays the original images filtered.
    */
    void Apply(std::vector<Image*> original, std::vector<Image*> filtered);
};

#endif // CANNY_H_