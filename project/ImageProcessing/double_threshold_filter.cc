/**
 * @file double_threshold_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "double_threshold_filter.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
DoubleThresholdFilter::DoubleThresholdFilter(float lowThresholdRatio, float highThresholdRatio) {
	// Initialize the high and lowThreshold member variables to store the ratios passed into the constructor
	this->highThreshold = highThresholdRatio;
	this->lowThreshold = lowThresholdRatio;

	// Set to false as the lowThreshold and highThreshold only store their respective ratios and NOT their actual values
	this->thresholdsSet = false;
}

// Apply the effects of the Double Threshold filter to a pixel located at (x, y) in the image
Color DoubleThresholdFilter::ApplyAtPixel(const Image* image, const Color& pixel){
	// If the lowThreshold and highThresholds have not been set, set them before moving forward with applying the Double Threshold filter
	if (!thresholdsSet) {
		this->highThreshold = image->GetMaxFloatVal() * this->highThreshold; // 255.0 is a constant as the alpha values of each pixel will always be 255.0 (not transparent in any way)
		this->lowThreshold = this->highThreshold * this->lowThreshold;
		this->thresholdsSet = true;
	}

	float newPixelComponentValues = 0;

	// Determine if the pixel should be classified as strong, weak, or zero
	// All RGB components of the image are equivalent as the image is in grayscale
	if (pixel.GetRed() >= this->highThreshold) {
		newPixelComponentValues = 255.0;
	} else if ((pixel.GetRed() < this->highThreshold) && (pixel.GetRed() >= this->lowThreshold)) {
		newPixelComponentValues = 25.0;
	} else {
		newPixelComponentValues = 0.0;
	}

	// Create a new float[] to store the new pixel component value
	// Alpha component should always be 255 as we want each pixel to be equally visible and not transparent in any way
	std::unique_ptr<float[]> newPixelColor (new float[4] {newPixelComponentValues, newPixelComponentValues, newPixelComponentValues, 255.0});
    
	// Create a new instance of Color to store the new color values
	Color newPixel = Color(newPixelColor, 4);

	// Return the new Color to Apply(std::vector<Image*> original,std::vector<Image*> filtered) to update the pixel in the new image
	return newPixel;
}

float DoubleThresholdFilter::GetLowThreshold() {
	return lowThreshold;
}

float DoubleThresholdFilter::GetHighThreshold() {
	return highThreshold;
}