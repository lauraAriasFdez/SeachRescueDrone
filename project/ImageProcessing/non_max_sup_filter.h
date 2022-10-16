/**
 * @file non_max_sup_filter.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef NON_MAX_SUP_FILTER_H_
#define NON_MAX_SUP_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "related_pixel_filter.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define PI 3.14159265

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief A Filter class that eliminates wide and fuzzy edges in an image. It only
* keeps the strongest pixel in the specified direction from the direction matrix.
 */
class NonMaxSupFilter:public RelatedPixelFilter{
    
public:
    /**
    * @brief Empty constructor for NonMaxSupFilter.
    */
    NonMaxSupFilter(){}

protected:
    /**
	* @brief  Applies the Non-Max Supression filter to a single pixel.
	*
	* @param[in] original A vector  of input images to apply the filter over.
    * @param[in] x An integer representing the width in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    * @param[in] y An integer representing the height in which the image color pixel is located, and
    * the pixel to which the filter should be applied.
    *
    * @return A unique pointer array containing a color for each filtered image the filter
    * should produce as an output, for this filter there should be only one color in the vector.
	*/
    std::vector<Color> ApplyAtPixel(const std::vector<Image*> original, int x, int y);
};
#endif