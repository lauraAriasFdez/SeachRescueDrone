/**
 * @file vector3_test.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "gtest/gtest.h"
#include "../src/vector3.h"

class VectorTest : public ::testing::Test {
public:
  void SetUp( ) { 
    defVector = Vector3();
    mixVector = Vector3(-1.2453, 2.34912, 0.2343);
    vec1 = Vector3(1, -2, 3);
    vec2 = Vector3(3, -4.5, 4);
  }

protected:
  Vector3 defVector; // Vector that is created with the default constructor
  Vector3 mixVector; // Vector that has a mix of positive and negative values
  Vector3 vec1; // Vector that can be used for general purpose testing
  Vector3 vec2; // Vector that can be used for general purpose testing
};

TEST_F(VectorTest, DefaultConstructorTest) {
  EXPECT_DOUBLE_EQ(defVector.GetX(), 0.0) << "X-Component of Vector Created by Default Constructor is Incorrect";
  EXPECT_DOUBLE_EQ(defVector.GetY(), 0.0) << "Y-Component of Vector Created by Default Constructor is Incorrect";
  EXPECT_DOUBLE_EQ(defVector.GetZ(), 0.0) << "Z-Component of Vector Created by Default Constructor is Incorrect";
}

TEST_F(VectorTest, ConstructorWithParameterValuesTest) {
  Vector3 customVector = Vector3(1.111, 2.222, -3.333);

  EXPECT_DOUBLE_EQ(customVector.GetX(), 1.111) << "X-Component of Vector Created by Constructor with Parameters is Incorrect";
  EXPECT_DOUBLE_EQ(customVector.GetY(), 2.222) << "Y-Component of Vector Created by Constructor with Parameters is Incorrect";
  EXPECT_DOUBLE_EQ(customVector.GetZ(), -3.333) << "Z-Component of Vector Created by Constructor with Parameters is Incorrect";
}

TEST_F(VectorTest, VectorAdditionOperatorOverloadTest) {
  Vector3 vec3 = vec1 + vec2;

  EXPECT_DOUBLE_EQ(vec3.GetX(), 4) << "X-Component of Vector Created As a Result of Adding 2 Vectors is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), -6.5) << "Y-Component of Vector Created As a Result of Adding 2 Vectors is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), 7) << "Z-Component of Vector Created As a Result of Adding 2 Vectors is Incorrect";
}

TEST_F(VectorTest, VectorSubtractionOperatorOverloadTest) {
  Vector3 vec3 = vec1 - vec2;

  EXPECT_DOUBLE_EQ(vec3.GetX(), -2) << "X-Component of Vector Created As a Result of Subtracting 2 Vectors is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), 2.5) << "Y-Component of Vector Created As a Result of Subtracting 2 Vectors is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), -1) << "Z-Component of Vector Created As a Result of Subtracting 2 Vectors is Incorrect";
}

TEST_F(VectorTest, VectorScalarZeroMultiplicationOperatorOverloadTest) {
  Vector3 vec3 = vec1 * 0;
  EXPECT_DOUBLE_EQ(vec3.GetX(), 0) << "X-Component of Vector Created As a Result of Multipling a Vector by 0 Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), 0) << "Y-Component of Vector Created As a Result of Multipling a Vector by 0 Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), 0) << "Z-Component of Vector Created As a Result of Multipling a Vector by 0 Is Incorrect";
}

TEST_F(VectorTest, VectorScalarNonZeroMultiplicationOperatorOverloadTest) {
  Vector3 vec3 = vec2 * -2;
  EXPECT_DOUBLE_EQ(vec3.GetX(), -6) << "X-Component of Vector Created As a Result of Multipling a Vector by a Negative Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), 9) << "Y-Component of Vector Created As a Result of Multipling a Vector by a Negative Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), -8) << "Z-Component of Vector Created As a Result of Multipling a Vector by a Negative Scalar Is Incorrect";

  Vector3 vec4 = vec2 * 3;
  EXPECT_DOUBLE_EQ(vec4.GetX(), 9) << "X-Component of Vector Created As a Result of Multipling a Vector by a Positive Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec4.GetY(), -13.5) << "Y-Component of Vector Created As a Result of Multipling a Vector by a Positive Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec4.GetZ(), 12) << "Z-Component of Vector Created As a Result of Multipling a Vector by a Positive Scalar Is Incorrect";
}

TEST_F(VectorTest, VectorScalarZeroDivisionOperatorOverloadTest) {
  Vector3 vec3 = vec1 / 0;
  EXPECT_DOUBLE_EQ(vec3.GetX(), vec1.GetX()) << "X-Component of Vector Created As a Result of Dividing a Vector by 0 Is Not Returing Unchanged Values";
  EXPECT_DOUBLE_EQ(vec3.GetY(), vec1.GetY()) << "Y-Component of Vector Created As a Result of Dividing a Vector by 0 Is Not Returing Unchanged Values";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), vec1.GetZ()) << "Z-Component of Vector Created As a Result of Dividing a Vector by 0 Is Not Returing Unchanged Values";
}

TEST_F(VectorTest, VectorScalarNonZeroDivisionOperatorOverloadTest) {
  Vector3 vec3 = vec2 / -2.1;
  EXPECT_DOUBLE_EQ(vec3.GetX(), 3/-2.1) << "X-Component of Vector Created As a Result of Divding a Vector by a Negative Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), -4.5/-2.1) << "Y-Component of Vector Created As a Result of Divding a Vector by a Negative Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), 4/-2.1) << "Z-Component of Vector Created As a Result of Divding a Vector by a Negative Scalar Is Incorrect";

  Vector3 vec4 = vec2 / 0.5;
  EXPECT_DOUBLE_EQ(vec4.GetX(), 3/0.5) << "X-Component of Vector Created As a Result of Divding a Vector by a Positive Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec4.GetY(), -4.5/0.5) << "Y-Component of Vector Created As a Result of Divding a Vector by a Positive Scalar Is Incorrect";
  EXPECT_DOUBLE_EQ(vec4.GetZ(), 4/0.5) << "Z-Component of Vector Created As a Result of Divding a Vector by a Positive Scalar Is Incorrect";
}

TEST_F(VectorTest, VectorSetComponentValuesTest) {
  Vector3 vec3 = Vector3(0,0,0);

  // Use setters to change component values of vector
  vec3.SetX(-1.3);
  vec3.SetY(1.25);
  vec3.SetZ(4.55);

  EXPECT_DOUBLE_EQ(vec3.GetX(), -1.3) << "X-Component of Vector After Calling SetX() Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), 1.25) << "Y-Component of Vector After Calling SetY() Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), 4.55) << "Z-Component of Vector After Calling SetZ() Is Incorrect";

  // Use setters to change component values of vector a second time
  vec3.SetX(4.59);
  vec3.SetY(-1.13);
  vec3.SetZ(12.14);

  EXPECT_DOUBLE_EQ(vec3.GetX(), 4.59) << "X-Component of Vector After Calling SetX() a Second Time Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetY(), -1.13) << "Y-Component of Vector After Calling SetY() a Second Time Is Incorrect";
  EXPECT_DOUBLE_EQ(vec3.GetZ(), 12.14) << "Z-Component of Vector After Calling SetZ() a Second Time Is Incorrect";}

TEST_F(VectorTest, VectorMagnitudeTest) {
  EXPECT_NEAR(vec2.Magnitude(), 6.726812024, 5.0e+4) << "Returned Value of Magnitude of Vector is Incorrect";

  Vector3 zeroVector = Vector3();
  EXPECT_DOUBLE_EQ(zeroVector.Magnitude(), 0) << "Returned Value of Magnitude of Zero Vector is Incorrect";
}

TEST_F(VectorTest, DistanceTestWithPositiveValues) {
  Vector3 vec4 = Vector3(1,2,3);
  Vector3 vec5 = Vector3(4,5,6);
  Vector3 vec6 = Vector3(1,0,1);

  EXPECT_DOUBLE_EQ(vec4.Distance(vec5), sqrtf(27)) << "Returned Value of Distance Between 2 Vectors with Positive Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec6.Distance(vec4), sqrtf(8)) << "Returned Value of Distance Between 2 Vectors with Positive Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec5.Distance(vec6), sqrtf(59)) << "Returned Value of Distance Between 2 Vectors with Positive Components is Incorrect";
}

TEST_F(VectorTest, DistanceTestWithNegativeValues) {
  Vector3 vec4 = Vector3(-1,-2,-3);
  Vector3 vec5 = Vector3(-4,-5,6);
  Vector3 vec6 = Vector3(-1,0,-1);

  EXPECT_DOUBLE_EQ(vec4.Distance(vec5), sqrtf(99)) << "Returned Value of Distance Between 2 Vectors with Negative Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec6.Distance(vec4), sqrtf(8)) << "Returned Value of Distance Between 2 Vectors with Negative Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec5.Distance(vec6), sqrtf(83)) << "Returned Value of Distance Between 2 Vectors with Negative Components is Incorrect";
}

TEST_F(VectorTest, DistanceTestWithZeroValues) {
  Vector3 vec4 = Vector3(0,0,0);
  Vector3 vec5 = Vector3(0,-5,6);
  Vector3 vec6 = Vector3(-1,0,-1);

  EXPECT_DOUBLE_EQ(vec4.Distance(vec4), 0) << "Returned Value of Distance Between 2 Vectors with Zero Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec6.Distance(vec4), sqrtf(2)) << "Returned Value of Distance Between 2 Vectors with Negative Components is Incorrect";
  EXPECT_DOUBLE_EQ(vec5.Distance(vec6), sqrtf(75)) << "Returned Value of Distance Between 2 Vectors with Negative Components is Incorrect";
}