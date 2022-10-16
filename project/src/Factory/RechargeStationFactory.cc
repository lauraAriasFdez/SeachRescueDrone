/**
 * @file RechargeStationFactory.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "RechargeStationFactory.h"

/*******************************************************************************
* Class Methods
******************************************************************************/
IEntity* RechargeStationFactory::CreateEntity(picojson::object& object,ICameraController& cameraController){
    if (object["name"].get<std::string>() == "recharge station"){
        std::cout << "We are creating a Recharge Station" << std::endl;
        RechargeStation* chargeStation= new RechargeStation(object);

        // Get the position as an array
        picojson::array position = object["position"].get<picojson::array>();
        double x = position[0].get<double>();
        double y = position[1].get<double>();
        double z = position[2].get<double>();
        Vector3 pos = Vector3(x,y,z);
        chargeStation->UpdatePosition(pos);

        // Get the direction as an array
        picojson::array dir = object["direction"].get<picojson::array>();
        x= dir[0].get<double>();
        y= dir[1].get<double>();
        z= dir[2].get<double>();
        Vector3 direct = Vector3(x,y,z);
        chargeStation->UpdateDirection(direct);

        // Get the id & type of object
        chargeStation->SetEntityId(object["entityId"].get<double>());
        chargeStation->SetId(object["id"].get<double>());
        chargeStation->SetType(object["name"].get<std::string>());

        return chargeStation;
    } // end of if Recharge Station

    return nullptr;
}