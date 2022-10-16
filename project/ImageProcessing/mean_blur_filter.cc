/**
 * @file mean_blur_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 /*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "mean_blur_filter.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::vector<Color> MeanBlurFilter::ApplyAtPixel(const std::vector<Image*> original, int x, int y){
    // for the meanblur filter we only need 1 single image
    Image* img = original[0];
    int width_limit = img->GetWidth();
    int height_limit = img->GetHeight();

    // counts the pixel numbers we are adding up, in the edge cases there will be less
    int numSurrounding =0;

    //Color array representing the addition of all surrounding pixels 
    std::unique_ptr<float[]> color = std::unique_ptr<float[]> (new float[img->GetComponentNum()]{0});
    int width_kernel = kernel_filter[0].GetWidth();
    int height_kernel = kernel_filter[0].GetHeight();

    //surrounding pixels index
    for (int w = x-(width_kernel/2);w<=x+(width_kernel/2);w++){
        for (int j = y-(height_kernel/2);j<=y+(height_kernel/2);j++){
            
            // looks at if pixel at that index exists or it is in the border, and thereby an edge case 
            if(w >=0 && j >=0 && w < width_limit && j < height_limit){
                // if it exits get the surrounding pixel and get all its components added to the color array 
                Color colorAddition = (*img->GetPixel(w,j) * kernel_filter[0].GetKernelComponent(w-x+(width_kernel/2), j - y+(height_kernel/2)));
                for (int component =0; component<img->GetComponentNum();component++){
                    color[component]+= (colorAddition.GetVal(component));
                }
                numSurrounding++;  
            } // end of if statement 
        }

    }

    //Create a color 
    Color pixelColor = Color(color,img->GetComponentNum());
    pixelColor = pixelColor * (1.0/numSurrounding);
    std::vector<Color> pixels;
    pixels.push_back(pixelColor);
    return pixels;
}