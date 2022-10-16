/**
 * @file image_processor.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef IMAGE_PROCESSOR_H_
#define IMAGE_PROCESSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <memory>
#include "image.h"
#include <vector>
#include <map>
#include "filter.h"
#include "canny.h"
#include "mean_blur_filter.h"
#include "threshold_filter.h"
#include "greyscale_filter.h"
#include "sobel_filter.h"
#include "non_max_sup_filter.h"
#include "gaussian_filter.h"
#include "double_threshold_filter.h"
#include "hysteresis_filter.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that applies any filter 
 */

class ImageProcessor {
public:

    /**
	* @brief Constructor that defines the map of filters.
	*
	*/
    ImageProcessor();

    /**
	*@brief Applies a filter to an Image and saves solution into another file.
	*
	*@param[in] inputFile A filename of the image to apply filter to.
	*@param[in] outputFile A filename of where the filtered image should be saved.
    *@param[in] filterType A filtertype that should be applied.
	* 
	*/
    void ApplyFilter(const std::string& inputFile, const std::string& outputFile, const std::string& filterType);

private:
    // Create available filters (unique_ptr handles dynamic memory)
    std::map<std::string, std::unique_ptr<Filter>> filters;
};

#endif