/**
 * @file HospitalFactory.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "HospitalFactory.h"

/*******************************************************************************
* Class Method Definition
******************************************************************************/
IEntity* HospitalFactory::CreateEntity(picojson::object& object,ICameraController& cameraController){
    if (object["name"].get<std::string>() == "hospital"){
        std::cout << "We are creating Hospital" << std::endl;
        Hospital* newHospital= new Hospital(object);

        // Get the position as an array
        picojson::array position = object["position"].get<picojson::array>();
        double x = position[0].get<double>();
        double y = position[1].get<double>();
        double z = position[2].get<double>();
        Vector3 pos = Vector3(x,y,z);
        newHospital->UpdatePosition(pos);

        // Get the direction as an array
        picojson::array dir = object["direction"].get<picojson::array>();
        x= dir[0].get<double>();
        y= dir[1].get<double>();
        z= dir[2].get<double>();
        Vector3 direct = Vector3(x,y,z);
        newHospital->UpdateDirection(direct);

        // Get the id & type of object
        newHospital->SetEntityId(object["entityId"].get<double>());
        newHospital->SetId(object["id"].get<double>());
        newHospital->SetType(object["name"].get<std::string>());
        return newHospital;
    }
    return nullptr;
    
}