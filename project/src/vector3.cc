/**
 * @file vector3.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "vector3.h"

// Base Constructor
Vector3::Vector3() {
  x = 0;
  y = 0;
  z = 0;
}

Vector3::Vector3(const double xVal, const double yVal, const double zVal) {
  x = xVal;
  y = yVal;
  z = zVal;
}

// Operator Overloads
Vector3 Vector3::operator+ (const Vector3& vec) {
  return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator- (const Vector3& vec) {
  return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator* (const double val) {
  return Vector3(x*val, y*val, z*val);
}

Vector3 Vector3::operator/ (const double val) {
  if (val == 0.0) { // If the user tries to divide by 0, just return a vector with unchanged x, y, and z components
    return Vector3(x, y, z);
  }
  return Vector3(x/val, y/val, z/val);
}

// Method to return the magnitude of a vector
double Vector3::Magnitude() const {
  return (sqrtf(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
}

// Method to return the magnitude of a vector
double Vector3::Distance(const Vector3& point2) const {
  return (sqrtf(std::pow((point2.GetX() - x), 2) + std::pow((point2.GetY() - y), 2) + std::pow((point2.GetZ() - z), 2)));
}

// Method that will print vectors to the command line in a consistent format to check each component value
void Vector3::Print() {
  std::cout << "[" << x << ", " << y << ", " << z<< "]" << std::endl;
}

// Getters
double Vector3::GetX() const {
  return x;
}

double Vector3::GetY() const {
  return y;
}

double Vector3::GetZ() const {
  return z;
}

// Setters
void Vector3::SetX(const double val) {
  x = val;
}

void Vector3::SetY(const double val) {
  y = val;
}

void Vector3::SetZ(const double val) {
  z = val;
}
