/**
 * @file color.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 
/*******************************************************************************
* Includes
******************************************************************************/
#include "color.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
//1- CONSTRUCTORS 
Color::Color (std::unique_ptr<float[]>& pixel, int numOfComponents){

    this->numOfComponents = numOfComponents;

    //create pixel float array
    this->pixel = std::unique_ptr<float[]>(new float[numOfComponents]);
    for(int i=0; i<numOfComponents;i++){
        this->pixel[i] = pixel[i];
    }

}

Color::Color(const Color& color){
    *this = color; // Calls assignment operator through overloading 
}

// Copy Constructor 
void Color::operator=(const Color& color){

    this->numOfComponents = color.numOfComponents;
    this->pixel = std::unique_ptr<float[]>(new float[numOfComponents]);

    // copy pixel value by pixel value - deep copy 
    for(int i=0; i<color.numOfComponents;i++){
        this->pixel[i] = color.pixel[i];
    }

}


//2- OPERATION BETWEEN COLORS

Color Color::operator+(const Color& color)const{

    // edge case - should not occur, but just in case error occurs 
    if (color.numOfComponents != this->numOfComponents){
        std::cout<<"ADD: The number of components do not match thereby defaulting to just 1 copy o the 1st color"<<std::endl;
        return Color(*this);
    }
    // will store the addition of every component of the pixels
    std::unique_ptr<float[]> addition_colors = std::unique_ptr<float[]>(new float[color.numOfComponents]);
    for(int i=0; i<color.numOfComponents;i++){
        addition_colors[i]= this->pixel[i] + color.pixel[i];
    }
    // new color created by adding the 2 colors
    Color rt = Color(addition_colors,this->numOfComponents);
    return rt;
}

Color Color::operator*(const Color& color)const{

    // edge case - should not occur, but just in case error occurs 
    if (color.numOfComponents != this->numOfComponents){
        std::cout<<"ADD: The number of components do not match thereby defaulting to just 1 copy o the 1st color"<<std::endl;
        return Color(*this);
    }

    // will store the multiplocation of every component of the pixels
    std::unique_ptr<float[]> mul_colors = std::unique_ptr<float[]>(new float[color.numOfComponents]);
    for(int i=0; i<color.numOfComponents;i++){
        mul_colors[i]= this->pixel[i] * color.pixel[i];
    }

    // new color created by multiplying 2 colors
    Color rt = Color(mul_colors,this->numOfComponents);
    return rt;
}

//3- SCALAR OPERATION METHODS
Color Color::operator*(float factor)const{
    // will hold the multiplication of each component by the factor 
    std::unique_ptr<float[]> mul_colors = std::unique_ptr<float[]>(new float[numOfComponents]);
    for(int i=0; i<numOfComponents;i++){
        mul_colors[i]= this->pixel[i] * factor;
    }

    // New color created 
    Color rt = Color(mul_colors,this->numOfComponents);
    return rt;
}

Color Color::operator/(float factor)const{
    // will hold the division of each component by the factor 
    std::unique_ptr<float[]> div_colors = std::unique_ptr<float[]>(new float[numOfComponents]);
    for(int i=0; i<numOfComponents;i++){
        div_colors[i]= this->pixel[i] / factor;
    }

    // New color created in the division of a color by a factor 
    Color rt = Color(div_colors,this->numOfComponents);
    return rt;
}

