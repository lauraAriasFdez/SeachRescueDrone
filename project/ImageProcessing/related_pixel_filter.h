/**
 * @file related_pixel_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef RELATED_PIXEL_FILTER_H_
#define RELATED_PIXEL_FILTER_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include "filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Abstract class that defines the virtual methods for all classes derived from RelatedPixelFilter.
 */

class RelatedPixelFilter:public Filter{

public:
    /**
    * @brief A method that goes through every pixel and applies the filter.
    *
    * @param original A vector of input images to apply the filter to.
    * @param filtered A vector of output images that stores images that have had the filter applied to them.
    */
    virtual void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

    /**
    * @brief Virtual destructor that is needed for polymorphism since derived classes constructors
    * need to be called.
    */
    virtual ~RelatedPixelFilter(){};

protected:
    /**
    * @brief Pure virtual method to apply the derived filter to one single pixel taking into
    * consideration surrounding pixels.
    *
    * @param[in] original A vector  of input images to apply the filter over.
    * @param[in] x An integer representing the x-position of the pixel the filter should be applied to.
    * @param[in] y An integer representing the y-position of the pixel the filter should be applied to.
    *
    * @return A unique pointer array containing a Color for each filtered image the filter
    * should produce as an output.
    */
    virtual std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y) = 0;
};

#endif