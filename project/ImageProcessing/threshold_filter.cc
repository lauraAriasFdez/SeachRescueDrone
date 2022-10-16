 /**
 * @file threshold_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 
/*******************************************************************************
* Includes
******************************************************************************/
#include "threshold_filter.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
Color ThresholdFilter::ApplyAtPixel (const Image* image,const Color& pixel){

    // if the luminance of that pixel is above the threashold set it ot black, 
    if (pixel.GetLuminance() < threshold){
        std::unique_ptr<float[]> black_pixel(new float[4] {0,0,0,255});
        Color black = Color(black_pixel,4);
        return black;
    }
    // if the pixel is below thereshold set the pixel to white
    else{
        std::unique_ptr<float[]> white_pixel(new float[4] {255,255,255,255});
        Color white = Color(white_pixel,4);
        return white;
    }

}

ThresholdFilter::ThresholdFilter(float threshold){
    this->threshold = threshold*255; 
}
    

