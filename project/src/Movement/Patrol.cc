/**
 * @file Patrol.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Movement/Patrol.h"

Patrol::Patrol() {
}

void Patrol::Move(const Vector3& position, std::queue<Vector3>& q) {
  // Start the looping rectangle pattern from drone position 
  int x = position.GetX();
  int y = position.GetY();
  int z = position.GetZ();

  int xFactor = 15; // Determines how far we move in the x-direction on each pass
  int xMultiplier = 0; // Multiplier that will switch between 1 and -1 to calculate the next position's x component

  int zFactor = 10; // Determines how far we move in the z-direction on each pass
  int zMultiplier = 0; // Multiplier that will switch between 1 and -1 to calculate the next position's z component

  // Create 10 looping square revolutions
  for (int i = 1; i <= 20; i++) {
    
    // Determine if the x or z multiplier should be negative to correctly move the to next position
    if (i % 2 == 0) {
      xMultiplier = -1;
      zMultiplier = 1;
    } else {
      xMultiplier = 1;
      zMultiplier = -1;
    }

    // if the drone position is in the corners we do not want to go outside the map 
    // map size is 200 (-100 to 100) in the x direction and   120 units (-60 to 60) in the z direction 

    // if z is negative in the corner (close to -60) and we are updating in the negative direction do not update z
    bool z_not_update = (z<(-55)) &&  (zMultiplier==-1);
    // if z is positive in the corner (close to 60) and we are updating in the positive direction do not update z
    z_not_update = z_not_update || ( (z>(55)) &&  (zMultiplier==1) ) ;
    
    if (!z_not_update){
      z = z + (zFactor) * i * zMultiplier; // Update the z direction component
      q.push(Vector3(x, y, z));
    }
    
    // if x is negative in the corner (close to -100) and we are updating in the negative direction do not update x
    bool x_not_update = (x<(-95)) &&  (xMultiplier==-1);
    // if x is positive in the corner (close to 100) and we are updating in the positive direction do not update x
    x_not_update = x_not_update || ( (x>(95)) &&  (xMultiplier==1) ) ;

    if (!z_not_update){
      x = x + (xFactor) * i * xMultiplier; // Update the x direction component
      q.push(Vector3(x, y, z));
    }
  }
}