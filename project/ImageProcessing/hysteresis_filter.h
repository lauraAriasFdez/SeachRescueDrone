/**
 * @file hysteresis_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef HYSTERESIS_FILTER_H_
#define HYSTERESIS_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "related_pixel_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that can be used to apply a Hysteresis Filter to an instance of the Image class.
 */
class HysteresisFilter : public RelatedPixelFilter {
public:
	/**
		* @brief Constructor of a HysteresisFilter with a specified weak and strong value to classify pixels with.
		*
		* @param[in] weakValue A float value that represents the weak threshold values to classify pixels.
		* @param[in] strongValue A float value that represents the high threshold values to classify pixels.
		* 
		* @return An instance of a HysteresisFilter with a specified weak and strong value to classify pixels with.
		*/
	HysteresisFilter(float weakValue, float strongValue);

protected:
	/**
		* @brief Modify an image by applying the effects of a Hysteresis filter to the pixel located
		* at (x, y) in an instance of the Image class.
		*
		* @param[in] original A vector of pointers to instances of the Image class to be able to access the
		* pixels of the original image.
		* @param[in] x An integer representing the x-coordinate of the pixel in the image.
		* @param[in] y An integer representing the y-coordinate of the pixel in the image.
		* 
		* @return A vector of instances of the Color class with each Color object in the vector 
		*representing a new Color for a different pixel in the image.
		*/
	std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y);

private:
	/**
		* @brief A private member variable to store the weak value that will help create a threshold to classify
		* pixels as weak or strong.
		*/
	float weak;

	/**
		* @brief A private member variable to store the strong value that will help create a threshold to classify
		* pixels as weak or strong.
		*/
	float strong;
};

#endif