/**
 * @file image.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

//include we implemented 
#include "image.h"
#include "color.h"

// Needed for reading images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Needed for writing images
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// 1 - CONSTRUCTORS
// Creates a "blank" image of a given width and height.
Image::Image(int w, int h){
    //basic private int variables
    width=w;
    height= h;
    componentNum = 4;
    size = width*height;

    //content is an array of Color objects, each color = 1 pixel 
    content =  std::unique_ptr<Color[]>(new Color[size]);
    
    //creates a float array with all 255 values for all components
    std::unique_ptr<float[]> default_color = std::unique_ptr<float[]> (new float[componentNum]);
    //memset (default_color,255,componentNum);
    for (int j = 0;j<componentNum;j++){
        default_color[j] = 255;
    }

    //initialize pixel/colors objects with all to be white pixels 
    for (int i=0;i<size;i++){
        content[i] = Color(default_color,componentNum);;
    }
}

// Load an image from the hard drive if a string (or character array) is passed into the constructor. 
Image::Image(const std::string& filename){

    // Load in an image using stb_image.h
    // Images may have less components, but we are forcing alpha with STBI_rgb_alpha
	unsigned char *loadedImage = stbi_load(filename.c_str(), &width, &height, &componentNum, STBI_rgb_alpha);

    //int variables 
    componentNum = 4; 
    size = width*height;

    //content is an array of Color objects, each color = 1 pixel 
    content = std::unique_ptr<Color[]>(new Color[size]);
    std::unique_ptr<float[]> color_pixel = std::unique_ptr<float[]> (new float[componentNum]);

    // Copy the image data into a local image buffer and free the image
    for (int i=0;i<size;i++){
        color_pixel[0] =  loadedImage[i*4];
        color_pixel[1] =  loadedImage[i*4 + 1];
        color_pixel[2] =  loadedImage[i*4+2];
        color_pixel[3] =  loadedImage[i*4+3];
        content[i] = Color(color_pixel,componentNum);
    }
    stbi_image_free(loadedImage); 
}

Image::Image(const unsigned char* data,int length){

    // Load in an image using stb_image.h
    unsigned char* loadedImage = stbi_load_from_memory(data, length, &width, &height, &componentNum, 4);
    
    //int variables 
    componentNum = 4; 
    size = width*height;

    //content is an array of Color objects, each color = 1 pixel 
    content = std::unique_ptr<Color[]>(new Color[size]);
    std::unique_ptr<float[]> color_pixel = std::unique_ptr<float[]> (new float[componentNum]);

    // Copy the image data into a local image buffer and free the image
    for (int i=0;i<size;i++){
        color_pixel[0] =  loadedImage[i*4];
        color_pixel[1] =  loadedImage[i*4 + 1];
        color_pixel[2] =  loadedImage[i*4+2];
        color_pixel[3] =  loadedImage[i*4+3];
        content[i] = Color(color_pixel,componentNum);
    }
    stbi_image_free(loadedImage); 
   
}
// 2- THE BIG 3

// Deeps copy an image into another object (Copy constructor)
Image::Image(const Image& image){
    *this = image; // Calls assigment operator through overloading 
}



void Image::operator=(const Image& image){
    this->width = image.width;
    this->size = image.size;
    this->height = image.height;
    this->componentNum = image.componentNum;
    this->content = std::unique_ptr<Color[]>(new Color[size]); 

    //copy content pixel by pixel so it is not shalow - DEEEP COPY
    for(int i=0; i<image.size;i++){
        //copy overload equal operator will take care of the deep copy of color object
        this->content[i] = image.content[i]; 
    }

}


// 3- GETTERS 
int Image::GetHeight()const{return height;}
int Image::GetWidth()const{return width;}
int Image::GetSize()const{return size;}
int Image::GetComponentNum()const{return componentNum;}
float Image::GetMaxFloatVal()const{
    float maxFloatColor = 0;
    ///for each pixel in each original picture
    for (int px =0;px<size;px++){
        //get the pixel color object
        Color pixel_img = this->content[px];
        float red = pixel_img.GetRed();
        float green = pixel_img.GetGreen();
        float blue = pixel_img.GetBlue();
        if (red > maxFloatColor)
            maxFloatColor = red;
        if (green > maxFloatColor)
            maxFloatColor = green;
        if (blue> maxFloatColor)
            maxFloatColor = blue;
    }   

    return maxFloatColor;
}
//method that returns a pixel value.
Color* Image::GetPixel(int x, int y)const{
    return &content[(y*width + x)];
}
Color* Image::GetPixel(int i)const{
    return &content[i];
}

// 4 - SETTERS
// method that sets a pixel value at a place on the image.
void Image::SetPixel(int x, int y,const Color& pixel){
    // get pixel of image you want to edit
    Color* pixel_img =GetPixel(x,y);
    // = overload operator of color will take care of deep copy 
    *pixel_img = pixel;
}

void Image::SetPixel(int i,const Color& pixel){
    Color* pixel_img =GetPixel(i);
    *pixel_img = pixel;
}


// 5- SAVE IMAGE TO FILE
//  A method that takes in a string (or character array) and saves the image.
void Image::SaveAs(const std::string& filename){

    //split color into unigned char
    unsigned char* data =  new unsigned char[size*componentNum];
    
    // for every color object we want to copt rgba into data to be written to
    for (int i=0;i<size*componentNum;i++){
        int pixel_idx = i/4;
        int component = (i%4);
        data[i]= static_cast<unsigned char> (content[pixel_idx].GetVal(component));
    }

    stbi_write_png(filename.c_str(), width, height, componentNum, data, width*4);
    delete [] data;
}
