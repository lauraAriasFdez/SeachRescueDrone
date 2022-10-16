/**
 * @file CameraResult.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "CameraResult.h"

/*******************************************************************************
 * Methods of CameraResult Class
 ******************************************************************************/

bool CameraResult::GetFoundRobot ()const{return this->found;}

void CameraResult::SetFoundRobot(bool f){found =f;}

Vector3 CameraResult::GetRobotPos ()const{return this->robot_pos;}

void CameraResult::SetFoundRobot(Vector3 pos){robot_pos =pos;}