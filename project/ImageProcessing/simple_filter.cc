/**
 * @file simple_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "simple_filter.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void SimpleFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){

    // for each image 
    Image* img = original[0];
    // since original and filter are vectorors of pointers we need to dereference to make a copy
    *filtered[0] = *img;
    //for each pixel in each original picture
    for (int px =0;px< img->GetSize();px++){
        //get the pixel color object
        Color* pixel_img =img->GetPixel(px);

        //create new color - specific to each simple filter
        Color newColor = ApplyAtPixel (original[0],*pixel_img);

        //set pixel to new color
        filtered[0]->SetPixel(px,newColor);
    }
}