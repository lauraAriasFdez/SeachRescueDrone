/**
* @file EntityFactory.h
*
* @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
*/
#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Entity/IEntity.h"
#include <memory>
#include "picojson.h"
#include "./camera_controller.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class EntityFactory {
public:

	/**
    *
    * @brief virtual destructor since composite Factory 
	* 		needs to be called and that is a subclass
    *
    */
	virtual ~EntityFactory() = default;

	/**
    *
    * @brief creates an entity based on the picson object
    *
    * @param[in] object json object representing the entity that needs to be created
    * 
    * @return  entity object or nullpointer 
    * 
    */
	virtual IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController) =0;
}; 

#endif 