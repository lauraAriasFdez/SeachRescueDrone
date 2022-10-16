/**
 * @file Beeline.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Movement/Beeline.h"

Beeline::Beeline() {
}

void Beeline::Move(const Vector3& position, std::queue<Vector3>& q) {
  int x = position.GetX();
  int y = position.GetY();
  int z = position.GetZ();

  // Assumes that the queue q is empty
  // Push the position onto the queue as we only want to visit the point we need to Beeline to
  q.push(Vector3(x, y, z));
}