/**
 * @file simple_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef SIMPLE_FILTER_H_
#define SIMPLE_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An abstract class that represents a filter that applies a change on an
 * individual pixel exclusively based on that pixel.
 *
 */
class SimpleFilter:public Filter{
public:

    /**
    * @brief A method that goes through every pixel and applies a simple filter over each pixel.
    *
    * @param[in] original A vector of input images to apply the filter to.
    * @param[in] filtered  A vector of output images that have all had a filered applied to its pixels.
    */
    void Apply(std::vector<Image*> original, std::vector<Image*> filtered);

    /**
    * @brief Virtual destructor that is needed for polymorphism since derived classes constructors
    * need to be called.
    */
    virtual ~SimpleFilter(){};

protected: 
    /**
    * @brief Pure virtual method to apply the derived filter to one single pixel.
    *
    * @param[in] image A constant pointer to an instance of the Image class.
    * @param[in] pixel A Color object representing the pixel to apply the filter over.
    *
    * @return A Color object representing the pixel being filtered.
    */
    virtual Color ApplyAtPixel (const Image* image, const Color& pixel) = 0;
};

#endif