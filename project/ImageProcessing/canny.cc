/**
 * @file canny.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include "canny.h"
#include "greyscale_filter.h"
#include "gaussian_filter.h"
#include "sobel_filter.h"
#include "non_max_sup_filter.h"
#include "double_threshold_filter.h"
#include "hysteresis_filter.h"
#include <vector>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Canny::Apply(std::vector<Image*> original, std::vector<Image*> filtered)
{
    // Define filters to apply 
    GreyScaleFilter Gray = GreyScaleFilter();
    GaussianFilter Gauss = GaussianFilter(5, 2);
    SobelFilter Sobel =  SobelFilter();
    NonMaxSupFilter NMS = NonMaxSupFilter();
    DoubleThresholdFilter DT = DoubleThresholdFilter(0.1, 0.35);
    HysteresisFilter Hysteresis = HysteresisFilter(25.0, 255.0);

    // Apply grayscale
    Gray.Apply(original, filtered);

    // Appy Gauyssian Blur;
    Gauss.Apply(filtered, original);

    // Apply sobel (2 outputs)
    Image output2;
    filtered.push_back(&output2);
    Sobel.Apply(original, filtered);
    // now original contains the 2 outputs of sobel and filtered only the input

    // Apply non max supressonsupression
    NMS.Apply(filtered, original);

    // Appy double threshold
    DT.Apply(original, filtered);

    // Apply Hysteresis
    Hysteresis.Apply(filtered, original);
    
    // Since output is accessed by reference after canny filtration,
    // need to make sure the image being pointed to (the first image
    // originally in the filtered vector) actually contains the filtered
    // image, as it's currently the first element in the original vector
    Image& output = *filtered[0];
    Image& final_image = *original[0];
    output = final_image;
}