/**
 * @file non_max_sup_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

 /*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "non_max_sup_filter.h"
 #include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::vector<Color> NonMaxSupFilter::ApplyAtPixel(const std::vector<Image*> original, int x, int y){

    // for the non max supression filter we have 2 images
    Image* img = original[0];
    Image* angles_img = original[1];
    // angle of pixel - any color represents the angle
    Color* px = (angles_img->GetPixel(x,y));
    float pixel_angle = (px->GetVal(0)/255.0 * 180.0);
    //Color of pixel to be compared  - since it is grey scale rgb all the same thus we just get the first component      
    float pixel_color = (img->GetPixel(x,y))->GetVal(0);
    float pixel_comp1 = 255;
    float pixel_comp2= 255;

    // looks at if pixel at that index exists or it is in the border, and thereby an edge case 
    int width_limit = img->GetWidth();
    int height_limit = img->GetHeight();
    // angle 0
    if ((0 <= pixel_angle && pixel_angle < 22.5) || (157.5 <= pixel_angle && pixel_angle <= 180)){
        if ((y+1) < height_limit)
            pixel_comp1 = img->GetPixel(x, y+1)->GetVal(0);
        if ((y-1) >=0)
            pixel_comp2 = img->GetPixel(x, y-1)->GetVal(0);
    }
    //angle 45
    else if (22.5 <= pixel_angle && pixel_angle <67.5){
        if ((x+1) < width_limit && (y-1) >=0)
            pixel_comp1 = img->GetPixel(x+1, y-1)->GetVal(0);
        if ((y+1) < height_limit && (x-1) >=0)
            pixel_comp2 = img->GetPixel(x-1, y+1)->GetVal(0);
    }
    //angle 90
    else if (67.5 <= pixel_angle && pixel_angle <112.5){
        if ((x+1) < width_limit)
            pixel_comp1 = img->GetPixel(x+1, y)->GetVal(0);
        if((x-1) >=0)                
            pixel_comp2 = img->GetPixel(x-1, y)->GetVal(0);
    }
    //angle 135
    else{
        if ((y-1) >=0 && (x-1)>=0)
            pixel_comp1 = img->GetPixel(x-1, y-1)->GetVal(0);
        if ((x+1) < width_limit && (y+1) >height_limit)
            pixel_comp2 = img->GetPixel(x+1, y+1)->GetVal(0);
    }

    // compare the 3 pixels 
    Color return_pixel;
    if ((pixel_color >= pixel_comp1)&&(pixel_color>=pixel_comp2)){
            return_pixel = *(img->GetPixel(x,y));
    }else{
        std::unique_ptr<float[]> black_pixel(new float[4] {0,0,0,255});
            return_pixel = Color(black_pixel,4); // black
    }
    return_pixel.SetAlpha(255);

    //Create a color 
    std::vector<Color> pixels;
    pixels.push_back(return_pixel);
    return pixels;
}