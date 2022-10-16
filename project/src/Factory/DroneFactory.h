/**
 * @file DroneFactory.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Entity/Drone.h"
#include "../vector3.h"
#include "EntityFactory.h"
#include "../Decorator/BatteryDecorator.h"
#include "./camera_controller.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class DroneFactory : public EntityFactory {
public:

	/**
    *
    * @brief creates a Drone entity based on the picson object
    *
    * @param[in] object json object representing the entity that needs to be created
    * 
    * @return Drone entity object or nullpointer 
    * 
    */
	IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController);

};      

#endif 

