/**
 * @file Patrol.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef PATROL_H_
#define PATROL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Movement/IMovement.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class that enables a Patrol movement strategy.
 */
class Patrol : public IMovement {

public:
  /**
  * @brief A constructor for an instance of the Patrol class.
  */
  Patrol();

  /**
  * @brief A method that adds locations to the queue of Vector3 locations to be visited.
  *
  * @param[in] position A constant reference to a Vector3 of any location in space.
  * @param[in] q  A reference to a queue of Vector3 objects that represent the locations to be visited in space.
  */
  void Move(const Vector3& position, std::queue<Vector3>& q);
};

#endif