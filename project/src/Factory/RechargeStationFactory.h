/**
 * @file RechargeStationFactory.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef RECHARGE_STATION_FACTORY_H_
#define RECHARGE_STATION_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "EntityFactory.h"
#include "../Entity/RechargeStation.h"
#include "../Entity/Entity.h"
#include "../vector3.h"
/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class RechargeStationFactory : public EntityFactory {
public:

	/**
    *
    * @brief creates a recharge station entity based on the picson object
    *
    * @param[in] object json object containing recharge station obj details
    * 
    * @return entity object or nullpointer 
    * 
    */
    IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController);
}; 

#endif 