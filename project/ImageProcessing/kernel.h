/**
 * @file kernel.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef KERNEL_H_
#define KERNEL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <memory>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class that represents the convolution kernel for a ConvolutionFilter
 */
class Kernel{

public:
    /**
    * @brief Constructor of a kernel with a specified value of kernel matrix,
    * its width and height.
    *
    * @param[in] matrix A float pointer to a 1D matrix containing the values of the kernel.
    * @param[in] width An integer representing the width of the kernel matrix.
    * @param[in] height An integer representing the height of the kernel matrix.
    */
    Kernel(float* matrix, int width, int height);

    /**
    * @brief Copy constructor to perform deep copies of kernels.
    *
    */
    Kernel(const Kernel& kernel);

    /**
    * @brief Equality overload operator to perform deep copes.
    * 
    * @param[in] kernel Another Kernel to copy data from.
    */
    void operator=(const Kernel& kernel);

    /**
    * @brief Get the width of the kernel matrix for an instance of the kernel class.
    *
    * @return An integer containing the with of the kernel.
    */
    int GetWidth()const{return width;};

    /**
    * @brief Get the height of the kernel matrix for an instance of the kernel class.
    *
    * @return An integer containing the height of the kernel.
    */
    int GetHeight()const{return width;};

    /**
    * @brief Get the matrix kernel value at of the kernel at a specific with and height.
    *
    * @param[in] x An integer representing the x-position of the kernel value to return.
    * @param[in] y An integer representing the y-position of the kernel value to return.
    *
    * @return Returns the float value of the kernel at (x,y).
    */
    float GetKernelComponent (int x, int y) const;

private:

    /**
    * @brief A float unique pointer array representing the values of the kernel.
    */
    std::unique_ptr<float[]> matrix;

    /**
    * @brief Private member variables representing the width and height of kernel matrix (integers).
    */
    int width, height;
};

#endif