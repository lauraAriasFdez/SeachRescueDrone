/**
 * @file Beeline.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef BEELINE_H_
#define BEELINE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Movement/IMovement.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class that enables a Beeline movement strategy.
 */
class Beeline : public IMovement {

public:
  /**
  * @brief A constructor for an instance of the Beeline class.
  */
  Beeline();

  /**
  * @brief A method that adds locations to the queue of Vector3 locations to be visited.
  *
  * @param[in] position A constant reference to a Vector3 of any location in space.
  * @param[in] q  A reference to a queue of Vector3 objects that represent the locations to be visited in space.
  */
  void Move(const Vector3& position, std::queue<Vector3>& q);
};

#endif