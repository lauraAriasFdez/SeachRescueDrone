/**
 * @file related_pixel_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "related_pixel_filter.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RelatedPixelFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){
    //for every output image let´s start with a copy of the first original image passed
    for (int i =0; i<filtered.size();i++){
        // since original and filter are vectorors of pointers we need to dereference to make a copy
        *filtered[i] = *original[0];
    }
    
    // get the width and height of the image
    int width_limit = original[0]->GetWidth();
    int height_limit = original[0]->GetHeight();

    // for the (x,y) representing one pixel position of the original 
	for (int x=0;x<width_limit;x++){
		for (int y=0;y<height_limit;y++){
			std::vector<Color> pixelColors = ApplyAtPixel(original,x,y);

			// error testing
			if (pixelColors.size() < filtered.size()){
				std::cout << " Apply At Pixel should have returned more Colors " << std::endl;
				return; 
			}

			// set the pixel for each of the output images 
			for (int i =0; i<filtered.size();i++){
				//setting pixel to avg of all those values
				filtered[i]->SetPixel(x,y,pixelColors[i]);  
			}

		}// end of height of A image
	} // end of width of A image

}