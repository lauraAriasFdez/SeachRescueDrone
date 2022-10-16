/**
 * @file filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef FILTER_H_
#define FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <vector>
#include "image.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Abstract class that defines the virtual methods for all filter classes.
 */
class Filter{

public:
    /**
    * @brief Pure virtual method for Filter.
    *
    * @param[in] original A vector of input images to apply the filter on.
    * @param[in] filtered  A vector of output images that contain the images with the filter applied.
    */
    void virtual Apply(std::vector<Image*> original, std::vector<Image*> filtered) = 0;


    /**
    * @brief Virtual destructor that is needed for polymorphism since derived classes constructors
    * need to be called.
    */
    virtual ~Filter(){};
};

#endif