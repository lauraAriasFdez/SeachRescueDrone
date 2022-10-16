/**
 * @file threshold_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef THRESHOLD_FILTER_H_
#define THRESHOLD_FILTER_H_

/*******************************************************************************
 * Includes
******************************************************************************/

#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A Threshold filter is a SimpleFilter that compares the luminance of a pixel and
 * compares that luminance to a threshold. If the luminance is larger than the threshold the
 * pixel is set to white, else it is set to black. 
 */
class ThresholdFilter:public SimpleFilter{

public:
    	
   /**
   * @brief Default constructor.
   */
    ThresholdFilter(){};

    /**
   * @brief Default constructor.
   * @param threshold The threshold for the filter.
   */
    ThresholdFilter(float threshold);

protected:
    /**
    * @brief Applies the filter to a single pixel.
    *
    * @param[in] image A constant pointer to an instance of the Image class.
    * @param[in] pixel A Color object representing the pixel to apply the Thereshold filter over.
    *
    * @return Color object representing the pixel that is having a filter applied filtered.
    */
     Color ApplyAtPixel (const Image* image,const Color& pixel);

private:
	/**
    * @brief A private member variable to track the threshold value for the ThresholdFilter.
    */
    float threshold;
};
#endif