/**
 * @file color.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 

#ifndef COLOR_H_
#define COLOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <memory>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that represents a pixel. Each component of the color is 
 * represented by a value between 0 and 255.
 */
class Color{

public:
// 1 - CONSTRUCTORS & DESTRUCTORD 
    /**
    * @brief Default constructor accepting no parameters.
    */
    Color(){};
    /**
    * @brief Constructor that accepts color component values.
    *
    * @param[in] pixel A unique pointer float array containing all the 
    * color coponents, such as rgba values of the pixel.
    * @param[in] numOfComponents The number of components the Color 
    * object has, which is the length of the pixel unique pointer
    * float array.
    */
    Color (std::unique_ptr<float[]>& pixel, int numOfComponents);
    
    /**
    * @brief A copy constructor that allows to copy/duplicate any Color. 
    * 
    *  @param[in] color The Color object to make a deep copy from.
    */
    Color (const Color& color);

    /**
    * @brief A destructor. 
    */
    ~Color(){};

// 2- OVERLOAD OPERATORS 
    /**
    * @brief Performs a deep copy of the color object passed in.
    *
    * @param[in] color The Color object to copy from.
    */
    void operator=(const Color& color);

    /**
    * @brief Performs the component-wise sum of two colors.
    * Components that exceed 255 are NOT truncated to 255.
    *
    * @param[in] color A color object to use as addition parameter.
    *
    * @return An instance of the Color class with color components calculated by adding the two specified Color objects together.
    */
    Color operator+(const Color& color)const;

    /**
    * @brief Performs the component-wise multiplication of two colors.
    * Components that exceed 255 are NOT truncated to 255.
    *
    * @param[in] color A Color object to use as multiplication parameter.
    *
    * @return The Color object calculated by multiplying each corresponding
    * commponets of the 2 colors.
    */
    Color operator*(const Color& color)const;

// 3- SCALAR COLOR OVERLOAD OPERATORS
    /**
    * @brief Performs the component-wise multiplication of
    * a color and a float, it multiplies each component of the
    * color by the float passed as parameter.
    * Components that exceed 255 are NOT truncated to 255.
    *
    * @param[in] factor A float to scale each color component by.
    *
    * @return The Color object calculated by multiplying each
    * component of the color by the factor.
    */
    Color operator*(float factor)const;


    /**
    * @brief Performs the component-wise division of
    * a color and a float, it divides each component of the
    * color by the float passed as parameter.
    *
    * @param[in] factor A float to divide each color component by.
    *
    * @return A Color object calculated by dividing each
    * component of the color by the factor.
    */
    Color operator/(float factor)const;

//4- GETTERS & SETTERS
    /**
    * @return The number of components that color object holds.
    */
    int GetComp()const{return numOfComponents;};

    /**
    * @return The red value component of the color. 
    */
    float GetRed()const{return pixel[0];};

    /**
    * @return The green value component of the color.
    */
    float GetGreen()const{return pixel[1];};

    /**
    * @return The blue value component of the color.
    */
    float GetBlue()const{return pixel[2];};

    /**
    * @return The alpha value component of the color.
    */
    float GetAlpha()const{return pixel[3];};

    /**
    * @brief Sets the alpha component to the new float
    * value passed in as the val parameter.
    */
    void SetAlpha(float val){pixel[3] = val;};

    /**
    * @return The value component of the color that is represented
    * by the indexed passed in as the component parameter.
    *
    *@param[in] Returns the value of the color component of the index that was specified to be retrieved.
    */
    float GetVal(int component)const{return pixel[component];};
    
    /**
    * @brief Calculates the brightness of the color according to a weighted 
    * sum of the RGB components of the color.
    *
    * @return A float representing the brightness of the color.
    */
    float GetLuminance() const{
        return pixel[0]*0.2126 + pixel[1]*0.7152 + pixel[2]*0.0722;
    }

private:
    /**
    * @brief A float unique pointer array representing the values of the color components.
    */
    std::unique_ptr<float[]> pixel;
    
    /**
	* @brief A private member variable to track the number of Components
    * in the color object.
	*/
    int numOfComponents;
};

#endif