
/**
 * @file HospitalFactory.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef HOSPITAL_FACTORY_H_
#define HOSPITAL_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../Entity/Hospital.h"
#include "EntityFactory.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class HospitalFactory : public EntityFactory {
public:
    /**
    *
    * @brief creates a hospital based on the picson object
    *
    * @param[in] object json object containing hospital details
    * 
    * @return entity object or nullpointer 
    * 
    */
	IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController);
};      

#endif 
