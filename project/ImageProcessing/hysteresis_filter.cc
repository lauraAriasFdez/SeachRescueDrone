/**
 * @file hysteresis_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "hysteresis_filter.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
HysteresisFilter::HysteresisFilter(float weakValue = 25.0, float strongValue = 255.0) {
	this->weak = weakValue;
	this->strong = strongValue;
}

// Apply the effects of the Hysteresis filter to a pixel located at (x, y) in the image
std::vector<Color> HysteresisFilter::ApplyAtPixel(const std::vector<Image*> original, int x, int y) {
	int imageWidth = original[0]->GetWidth();
	int imageHeight = original[0]->GetHeight();

	// Set the size of the neighboorhood of pixels to check around (x, y) for strong pixels
	int kernelWidth = 3;
	int kernelHeight = 3;

	bool hasStrongNeighbor = false; // Variable to track if the pixel at (x, y) has a strong neighbor
	std::vector<Color> pixel; // Vector of a single color that will be returned to Apply() to update the new image

	float newPixelValue = original[0]->GetPixel(x,y)->GetVal(0); // Get the current Red component of the original image

	// If (x, y) is a weak pixel -> check for strong neighbors
	if (original[0]->GetPixel(x,y)->GetVal(0) == this->weak) {
		
		for (int w = x - (kernelWidth/2); w <= x + (kernelWidth/2); w++){ // Check the neighborhood pixels of (x, y) for a single strong pixel
			for (int j = y - (kernelHeight/2); j <= y + (kernelHeight/2); j++){
				
				if ((w >=0 && j >=0 && w < imageWidth && j < imageHeight)) { // Check that bounds of pixel @ (w, j) are safe
					if ((original[0]->GetPixel(w,j)->GetVal(0) == this->strong)) {
						hasStrongNeighbor = true;
						break; // Break out from searching any additional neighbors if we have found a single strong neighboor
					}
				}
			}
		}

		// If (x, y) has a strong neighbor, make it strong, otherwise make it weak
		if (hasStrongNeighbor) {
			newPixelValue = 255.0;
		} else {
			newPixelValue = 0.0;
		}
	} 

	std::unique_ptr<float[]> newPixelColor = std::unique_ptr<float[]> (new float[4] {newPixelValue, newPixelValue, newPixelValue, 255}); // Alpha value should always be 255.0 as pixels should not be transparent
	Color pixelColor = Color(newPixelColor, 4);

	// Push the new pixelColor into the vector tracking the pixel color
	pixel.push_back(pixelColor);

	// Return the vector containing the new Color to Apply() so the pixel in the new image can be updated to the new color
	return pixel;
}