
/**
 * @file image_processor.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

using namespace std;

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "image_processor.h"
#include <iostream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ImageProcessor::ImageProcessor(){
    filters["greyscale"] = unique_ptr<Filter>(new GreyScaleFilter());
    filters["threshold"] = unique_ptr<Filter>(new ThresholdFilter(0.5));
    filters["threshold-low"] = unique_ptr<Filter>(new ThresholdFilter(0.25));
    filters["threshold-high"] = unique_ptr<Filter>(new ThresholdFilter(0.75));
    filters["mean_blur"] = unique_ptr<Filter>(new MeanBlurFilter());
    filters["gaussian"] = unique_ptr<Filter>(new GaussianFilter(5,2));
    filters["double_threshold_filter"] = unique_ptr<Filter>(new DoubleThresholdFilter(0.1, 0.2));
    filters["hysteresis_filter"] = unique_ptr<Filter>(new HysteresisFilter(25.0, 255.0));
    filters["canny-edge-detect"] = unique_ptr<Filter>(new Canny());
}

void ImageProcessor::ApplyFilter(const std::string& inputFile, const std::string& outputFile, const std::string& filterType){

    //Input Images
    std::vector<Image*> inputs;
    Image input(inputFile);
    inputs.push_back(&input);

    //Output Images
    std::vector<Image*> outputs;
    Image output;
    outputs.push_back(&output);

    //check if filter type exists 
    if (filters.count(filterType)<=0){
        std::cout<<"Image processor cannot implement this filter either because it does not exist or because it needs 2 inputs or outputs images"<<std::endl;
        return;
    }
	
    // Apply filter based on filter type
    filters[filterType]->Apply(inputs, outputs);

    //Save Image
    output.SaveAs(outputFile);
}
