/**
 * @file ObjectDetector_test.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include <opencv2/core.hpp>
#include "gtest/gtest.h"
#include "../src/ObjectDetector/ObjectDetector.h"

class ObjectDetectorTest : public ::testing::Test {
public:
  void SetUp( ) { 
    objdet = ObjectDetector();
    imRobot = imread("tests/images/robot.jpg");
    imRobotless = imread("tests/images/robotless.jpg");
    imBait = imread("tests/images/bait.jpg");
  }

protected:
  ObjectDetector objdet;
  Mat imRobot; //image containing a robot
  Mat imRobotless; //image without a robot
  Mat imBait; //image containing football field
  //this field has coloration that can be mistaken for robot
};

// COMPONENT TESTS
TEST_F(ObjectDetectorTest, NotFoundTest) {
  EXPECT_EQ(objdet.Found(imRobotless), false) << "Robot detected in an image that clearly did not contain a robot";
}

TEST_F(ObjectDetectorTest, FoundTest) {
  EXPECT_EQ(objdet.Found(imRobot), true) << "Robot not detected in an image clearly containing a robot";
}

TEST_F(ObjectDetectorTest, BaitTest) {
  EXPECT_EQ(objdet.Found(imBait), false) << "Robot not detected in an image that did not contain a robot";
}
