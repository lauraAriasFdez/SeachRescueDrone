/**
 * @file DroneFactory.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "DroneFactory.h"

/*******************************************************************************
* Class Method Definition
******************************************************************************/

IEntity* DroneFactory::CreateEntity(picojson::object& object,ICameraController& cameraController){
    if (object["name"].get<std::string>() == "drone" || object["name"].get<std::string>() == "rescue drone" ){
        std::cout << "We are creating Drone" << std::endl;
        Drone* newDrone= new Drone(object);

        // Get the position as an array
        picojson::array position = object["position"].get<picojson::array>();
        double x = position[0].get<double>();
        double y = position[1].get<double>();
        double z = position[2].get<double>();
        Vector3 pos = Vector3(x,y,z);
        newDrone->UpdatePosition(pos);

        // Get the direction as an array
        picojson::array dir = object["direction"].get<picojson::array>();
        x= dir[0].get<double>();
        y= dir[1].get<double>();
        z= dir[2].get<double>();
        Vector3 direct = Vector3(x,y,z);
        newDrone->UpdateDirection(direct);

        // Get the velocity
        x=3;
        if (object["name"].get<std::string>() == "drone")
            x = object["speed"].get<double>();
        
        Vector3 vel = Vector3(x,0,0);
        newDrone->UpdateVelocity(vel);

        // Get the id & type of object
        newDrone->SetEntityId(object["entityId"].get<double>());
        newDrone->SetId(object["id"].get<double>());
        newDrone->SetType(object["name"].get<std::string>());

            // Create cameras for the entity.
        picojson::array cameras = object["cameras"].get<picojson::array>();
        for (int i = 0; i < cameras.size(); i++) {
            Camera* camera = new Camera(cameras[i].get<double>(), &cameraController);
            newDrone->AddCamera(camera);
        }

        // Get initial chargin power

	double batt;
        if (object["name"].get<std::string>() == "drone")
            batt = object["charge"].get<double>();
        // not quite sure if correct battery power
        return new BatteryDecorator(newDrone, 500);
    }
    return nullptr;
    
}
