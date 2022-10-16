#include <iostream>
#include <string>
#include "image_processor.h"

int main(int argc, const char* argv[]){
    // Get input file, and output file from command line
    // argc = # of arguments
    // argv = an array of arguments
    
    if (argc <= 3){
        std::cout << "We need 3 arguments to implement the Canny Edge Detector algorithm" << std::endl;
        std::cout << "(1) Input file of image to implement canny,(2) filter to implement (3) output file to save solution" << std::endl;
        return -1;
    }
	
    std::string inputFile(argv[1]);
    std::string filterType(argv[2]);
    std::string outputFile(argv[3]);

    // Create the image processor
    ImageProcessor processor = ImageProcessor();
    processor.ApplyFilter(inputFile,outputFile,filterType);

    return 0;
}