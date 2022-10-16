/**
 * @file double_threshold_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef DOUBLE_THRESHOLD_FILTER_H_
#define DOUBLE_THRESHOLD_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "simple_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that can be used to apply a Double Threshold Filter to an Image.
 */
class DoubleThresholdFilter : public SimpleFilter {
public:
	/**
		* @brief Constructor of a Double Threshold Filter with a specified low-threshold and high-threshold.
		*
		* @param[in] lowThresholdRatio A float value that represents the low-threshold value.
		* @param[in] highThresholdRatio A float value that represents the high-threshold value.
		* 
		* @return Returns an instance of a DoubleThresholdFilter with the specified low-threshold
		* and high-threshold values.
		*/
	DoubleThresholdFilter(float lowThresholdRatio, float highThresholdRatio);

	/**
		* @brief Get the value of the low-threshold for an instance of the DoubleThresholdFilter class.
		*
		* @return Returns an a float containing the value of the low-threshold set for this Double
		* Threshold filter.
		*/
	float GetLowThreshold();

	/**
		* @brief Get the value of the high-threshold for an instance of the DoubleThresholdFilter class.
		*
		* @return Returns an a float containing the value of the high-threshold set for this Double
		* Threshold filter.
		*/
	float GetHighThreshold();

protected:
/**
		* @brief Modify the pixel of an image to apply the effects of a Double Threshold filter on that image.
		*
	    * @param[in] image A constant pointer to an instance of the Image class.
		* @param[in] pixel A reference to an instance of the Color class that represents the pixel of an image
		* to apply the Double Threshold filter to.
		* 
		* @return Returns an instance of the Color class representing the new Color that the pixel in the
		* image will be changed to after applying the Double Threshold filter.
		*/
	Color ApplyAtPixel (const Image* image, const Color& pixel);

private:
	/**
		* @brief A private member variable to store the low-threshold value for the Double Threshold
		* when applied to an instance of the Image class.
		*/
	float lowThreshold;

	/**
		* @brief A private member variable to store the high-threshold value for the Double Threshold 
		* when applied to an instance of the Image class.
		*/
	float highThreshold;

	/**
		* @brief A private member variable to track whether both the low and high-threshold values store
		* the actual threshold value and not the threshold ratio.
		*/
	bool thresholdsSet;
};

#endif