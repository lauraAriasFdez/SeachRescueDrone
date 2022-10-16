/**
 * @file gaussian_filter.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gaussian_filter.h"
#include <math.h>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::unique_ptr<float[]> GaussianFilter::GaussianKernel(int size, float sigma)
{
    float normal = 1 / (2.0 * M_PI * powf(sigma, 2));
    std::unique_ptr<float[]> f(new float[size*size]);
    float s = 0.0;

    // calculate the values for the kernel
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int x = i - size / 2;
            int y = j - size / 2;
            float g = exp(-((powf(x, 2) + powf(y, 2)) / (2.0*powf(sigma, 2)))) * normal;
            f[i*size + j] = g;
            s += g;
        }
    }
    // scale all values so they sum to 1
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            f[i*size + j] = f[i*size + j] / s;
        }
    }
    return f;
}

std::vector<Color> GaussianFilter::ApplyAtPixel(const std::vector<Image*> original, int x, int y){
    // for the gaussian filter we only need 1 single image
    Image* img = original[0];
    int width_limit = img->GetWidth();
    int height_limit = img->GetHeight();
    
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
                Color colorAddition = (*(img->GetPixel(w,j)) * kernel_filter[0].GetKernelComponent(w-x+(width_kernel/2), j - y+(height_kernel/2)));
                for (int component =0; component<img->GetComponentNum();component++){
                    color[component]+= (colorAddition.GetVal(component));
                }
            } // end of if statement 
        }
    }

    // Confine color vals between 0 and 255
    for (int c = 0; c < img->GetComponentNum(); c++)
    {
        if (color[c] < 0.0) { color[c] = 0.0; }
        else if (color[c] > 255.0) { color[c] = 255.0; }
    }
    // Create a pixel using color and return it
    Color pixelColor = Color(color,img->GetComponentNum());
    pixelColor.SetAlpha(255);                
    std::vector<Color> pixels;
    pixels.push_back(pixelColor);
    return pixels;
}