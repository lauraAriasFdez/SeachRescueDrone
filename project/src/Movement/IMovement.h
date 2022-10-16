/**
 * @file IMovement.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef IMOVEMENT_H_
#define IMOVEMENT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <queue>
#include "../vector3.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief An Interface for any Movement Strategy.
 */
class IMovement {

public:
  /**
  * @brief A method that adds locations to the queue of Vector3 locations to be visited.
  *
  * @param[in] position A constant reference to a Vector3 of any location in space.
  * @param[in] q  A reference to a queue of Vector3 objects that represent the locations to be visited in space.
  */
  virtual void Move(const Vector3& position, std::queue<Vector3>& q) = 0;
};

#endif