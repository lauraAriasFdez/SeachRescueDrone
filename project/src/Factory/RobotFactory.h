/**
 * @file RobotFactory.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "EntityFactory.h"
#include "../Entity/Robot.h"
#include "../Entity/Entity.h"
#include "../vector3.h"
/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class RobotFactory : public EntityFactory {
public:

	/**
    *
    * @brief creates a Robot entity based on the picson object
    *
    * @param[in] object json object representing the entity that needs to be created
    * 
    * @return Robot entity object or nullpointer 
    * 
    */
    IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController);	
	
}; 

#endif 