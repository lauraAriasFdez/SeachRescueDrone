/**
 * @file vector3.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <math.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that can be used to represent a 3D Vector.
 */
class Vector3 {
public:
  /**
    * @brief The default constructor of a 3D Vector.
    *
    * @return Returns an instance of Vector3 object whose vector components are all 0.
    */
  Vector3();

  /**
    * @brief Constructor of a Double Threshold Filter with a specified x, y, and z component values.
    *
    * @param[in] x A double value that represents the value of the x-component of the 3D Vector.
    * @param[in] y A double value that represents the value of the y-component of the 3D Vector.
    * @param[in] z A double value that represents the value of the z-component of the 3D Vector.
    * 
    * @return Returns an instance of Vector3 object with the specific x, y, and z components.
    */
  Vector3(const double x, const double y, const double z);

  /**
    * @brief Operator overload for the addition of two Vector3 objects.
    *
    * @param[in] vec A constant reference to the Vector3 that should be added to the current Vector3 object.
    * 
    * @return Returns an instance of Vector3 object whose x, y, and z components are equal to the sum of the two input vectors.
    */
  Vector3 operator+ (const Vector3& vec);

  /**
    * @brief Operator overload for the subtraction of two Vector3 objects.
    *
    * @param[in] vec A constant reference to the Vector3 that should be subtracted from the current Vector3 object.
    * 
    * @return Returns an instance of Vector3 object whose x, y, and z components are equal to the difference of the two input vectors.
    */
  Vector3 operator- (const Vector3& vec);

  /**
    * @brief Operator overload for the multiplication of a scalar across an instance of a Vector3 object.
    *
    * @param[in] val A constant scalar double that will be multipled across each of the x, y, and z components of the Vector3.
    * 
    * @return Returns an instance of Vector3 object whose x, y, and z components are equal to their original values multiplied by the value of val.
    */
  Vector3 operator* (const double val);

  /**
    * @brief Operator overload for the division of a scalar across an instance of a Vector3 object.
    *
    * @param[in] val A constant scalar double that will be divided across each of the x, y, and z components of the Vector3.
    * 
    * @return Returns an instance of Vector3 object whose x, y, and z components are equal to their original values multiplied by the value of val. Note: Trying to divide by zero will return a new instance of a Vector3 object with the same x, y, and z components.
    */
  Vector3 operator/ (const double val);

  /**
    * @brief A method that returns the magnitude of a Vector3 object.
    *
    * @return Returns the double value of the magnitude of the vector.
    */
  double Magnitude() const;

  /**
    * @brief A method that returns the distance between the current instance of Vector3 and point2.
    *
    * @return Returns the distance between the current instance of Vector3 and point2.
    */
  double Distance(const Vector3& point2) const;

  /**
    * @brief A method that prints the the Vector3 object to the command line in the form of [x, y, z].
    */
  void Print();

  /**
    * @brief A method that returns the x-component of a Vector3 object.
    *
    * @return Returns the double value of the x-component of the current Vector3 object.
    */
  double GetX() const;

  /**
    * @brief A method that returns the y-component of a Vector3 object.
    *
    * @return Returns the double value of the y-component of the current Vector3 object.
    */
  double GetY() const;

  /**
    * @brief A method that returns the z-component of a Vector3 object.
    *
    * @return Returns the double value of the z-component of the current Vector3 object.
    */
  double GetZ() const;

  /**
    * @brief A method that can set the x-component of an instance of the Vector3 class.
    *
    * @param[in] val A constant double that holds the new value that the x-component of the vector should be set to.
    */
  void SetX(const double val);

  /**
  * @brief A method that can set the y-component of an instance of the Vector3 class.
  *
  * @param[in] val A constant double that holds the new value that the y-component of the vector should be set to.
  */
  void SetY(const double val);

  /**
  * @brief A method that can set the z-component of an instance of the Vector3 class.
  *
  * @param[in] val A constant double that holds the new value that the z-component of the vector should be set to.
  */
  void SetZ(const double val);

private:
  double x, y, z;
};

#endif //VECTOR_H_