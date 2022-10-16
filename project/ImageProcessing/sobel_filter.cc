/**
 * @file sobel_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "sobel_filter.h"

std::vector<Color> SobelFilter::ApplyAtPixel(const std::vector<Image*> original, int x, int y){

        // for the sobel filter we only need 1 single image as input and it will produce 2 output images
        Image* img = original[0];
        int width_limit = img->GetWidth();
        int height_limit = img->GetHeight();

        
        //float representing the addition of all surrounding pixels - kernel mult in x and y direction
        float Gx =0;
        float Gy = 0;

        // In the constructor we passed in a vecor of kernels to the parent constructor
        // let's get the width and height of one of those kernels to know which pixels we need
        // to loop through 
        int width_kernel = kernel_filter[0].GetWidth();
        int height_kernel = kernel_filter[0].GetHeight();

        //surrounding pixels index
        for (int w = x-(width_kernel/2);w<=x+(width_kernel/2);w++){
            for (int j = y-(height_kernel/2);j<=y+(height_kernel/2);j++){
                        
                // looks at if pixel at that index exists or it is in the border, and thereby an edge case 
                if(w >=0 && j >=0 && w < width_limit && j < height_limit){

                    // if it exits get the surrounding pixel and get all its components added to the color array 
                    Gx += ((img->GetPixel(w,j)->GetVal(0)) * kernel_filter[0].GetKernelComponent(w-x+(width_kernel/2), j - y+(height_kernel/2)));
                    Gy += ((img->GetPixel(w,j)->GetVal(0)) * kernel_filter[1].GetKernelComponent(w-x+(width_kernel/2), j - y+(height_kernel/2)));
                } // end of if statement 
            }
        } // end of surrounding pixel addition 

        // Find eucledian distance 
        float G = powf((pow(Gx,2) + pow(Gy,2)),.5);

        //normalize - so it does not go out of scope 
        if (G > 255)
            G = 255;
        
        if (G < 0)
            G = 0;
        //Create a color - for sobel #1  - angle
        std::unique_ptr<float[]> color = std::unique_ptr<float[]> (new float[4] {G,G,G,255});
        Color pixelColor = Color(color,4);
        
        //Create a color - for sobel #2
        float ata = atan2(Gy,Gx);
        ata = ata * 180.0/PI;
        if (ata < 0)
            ata+=180.0;
        float theta = ((ata)/180.0)*255.0;// theta will be between 0 and 255, if you want to get degrees do (+180/255)
        std::unique_ptr<float[]> angle = std::unique_ptr<float[]> (new float[4] {theta,theta,theta,255});
        Color direction = Color(angle,4);

        //Returned value - 1 color for each filtered image pixel 
        std::vector<Color> pixels;
        pixels.push_back(pixelColor);
        pixels.push_back(direction);
        
        return pixels;
    }