/**
 * @file greyscale_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "greyscale_filter.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
Color GreyScaleFilter::ApplyAtPixel (const Image* image, const Color& pixel){
    // get the luminance to represent rgb values and the same a for rgba value
    float L = pixel.GetLuminance();
    float alpha = pixel.GetAlpha();
                
    //create new color to be the rgb each to be the luminance 
    std::unique_ptr<float[]> gray_pixel(new float[4] {L,L,L,alpha});
    Color newColor = Color(gray_pixel,4);

    return newColor;
}