/**
 * @file ObjectDetector.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef OBJECT_DETECTOR_H_
#define OBJECT_DETECTOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <memory>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
using namespace std;
using namespace cv; // Using namespace statements are being used here due to the pervasiveness of OpenCV library Usage

/**
 * @brief A class used to detect the orange Robot within a given image.
 */
class ObjectDetector {
public:

  /**
  * @brief A constructor for an instance of the ObjectDetector class.
  *
  */
  ObjectDetector();

  /**
  * @brief Checks to see if the orange robot is found in the image.
  *
  * @param[in] im An img (in OpenCV Matrix representation) that will be used to look for the robot.
  * 
  * @return bool True if robot found, otherwise False is returned.
  */
  bool Found(cv::Mat im);

  /**
  * @brief Transfers the (x, y) pixel number of where the robot is found.
  *
  * @param[in] robot_x reference to an integer containing the x component of the pixel in the image where the robot can be found
  * @param[in] robot_y reference to an integer containing the y component of the pixel in the image where the robot can be found
  */
  void GetRobotPos(int& robot_x, int& robot_y);

private:
  /**
    * @brief An integer representing the x-position of where the object can be found in the scene.
    */
  int x_pos;

  /**
    * @brief An integer representing the y-position of where the object can be found in the scene.
    */
  int y_pos;
};

#endif