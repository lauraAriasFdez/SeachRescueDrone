/**
 * @file image.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 
#ifndef IMAGE_H_
#define IMAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "color.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief A class that holds content representing a PNG image.
 *
 */
class Image{
public:
//1. Constructor
    /**
    * @brief Default constructor accepting no parameters.
    */
    Image(){};

    /**
    * @brief Creates a "blank" image of a given width and height.
    *
    * @param[in] w An integer representing the width of the image to be created.
    * @param[in] h An integer representing the height of the image to be created.
    */
    Image(int w, int h);
    
    /**
    * @brief Load an image from the hard drive given the filename passed.
    * 
    * @param[in] filename A string representing the relative location of the image. 
    */
    Image(const std::string& filename);

    Image(const unsigned char* data,int length);

//2. The Big 3 for Dynamic Memory Allocation
    /**
    * @brief A copy constructor that allows to copy/duplicate any Image. 
    *
    * @param[in] image An Image object used to make a duplicate of.
    */
    Image(const Image& image);
        
    /**
    * @brief A destructor. 
    */
    ~Image(){};
        
    /**
    * @brief Deep copy an image passed in as parameter into another object.
    *
    * @param[in] image An Image object used to make a duplicate of.
    */
    void operator=(const Image& image);
        
//3. Methods
    /**
    * @brief A method that takes in a string (or character array) and saves the Image 
    * object into a PNG image.
    * @param[in] filename A string representing the name and location of the Image being
    * saved.
    */
    void SaveAs(const std::string& filename);
        
//4. Getters & Setters
    /**
    * @return The height of the image object.
    */
    int GetHeight() const;

    /**
    * @return The width of the image object.
    */
    int GetWidth() const;

    /**
    * @return The total number of pixels of the image object.
    */
    int GetSize() const;

    /**
    * @return The max r,g, or b that is found in the image.
    */
    float GetMaxFloatVal() const;

    /**
    * @return The number of components each pixel has.
    */
    int GetComponentNum() const; 
    
    /**
    * @param[in] x An integer representing the x-position of the pixel to return.
    * @param[in] y An integer representing the y-position of the pixel to return.
	* 
	* @return A Color object pointer, pointing to the Color at
    * the width and height passed in as parameters.
    */
    Color* GetPixel(int x, int y) const;


    /**
	* @param[in] i integer representing where the image color to retrive is situated
	*
    * @return  Color object pointer, pointing to the Color at
    * the given index in the image.
    */
    Color* GetPixel(int i) const; 

    /**
    * @brief Sets the Color pixel at the width and height passed as parameter
    * to a new Color object passed as parameter.
    *
    * @param[in] x An integer representing the x-position of the pixel to return.
    * @param[in] y An integer representing the y-position of the pixel to return.
    * @param[in] pixel A Color object to be used as new color of pixel at (x,y).
    */
    void SetPixel(int x, int y, const Color& pixel);

    /**
    * @brief Sets the Color pixel at the index passeed as parameter
    * to a new Color object also passed as a parameter.
    *
    * @param[in] i An integer representing where the image color to change is located.
    * @param[in] pixel A Color object to be used as new color of pixel at (x,y).
    */
    void SetPixel(int i, const Color& pixel);


private:
    /**
    * @brief Private member variables representing the width, height, size and the
    * number of Components of each pixel.
    */
    int width,height,size,componentNum;

    /**
    * @brief Private variable holding Image content. An image is represented as a
    * unique pointer array of Color objects.
    */
    std::unique_ptr<Color[]> content;
};

#endif