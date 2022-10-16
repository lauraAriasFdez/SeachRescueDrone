/**
 * @file Robot.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef ROBOT_H_
#define ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Entity.h"
#include <string>

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class Robot:public Entity {

public:

    /**
    *
    *@brief Robot Constructor
    * 
    */
    Robot(){}

    Robot(picojson::object& obj):Entity(obj){}
    /**
    *
    * @brief Fuction that will return the isRescue state of the Robot
    * 
    * @return true represeting if robot has been rescued and false otherwise
    */
    bool GetIsRescued() const;

    /**
    *
    * @brief Fuction that will change the isRescue state of the Robot
    * 
    * @param[in] val bool that is true  if robot has been rescued and false otherwise
    */
    void SetIsRescued(bool val);
    
protected:
    /**
    *
    * @brief boolean representing true if robot has been rescued by drone
    *        and false otherwise
    */
    bool isRescued = false;

};

#endif