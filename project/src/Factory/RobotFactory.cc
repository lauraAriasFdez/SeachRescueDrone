/**
 * @file RobotFactory.ccc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "RobotFactory.h"

/*******************************************************************************
* Class Methods
******************************************************************************/

IEntity* RobotFactory::CreateEntity(picojson::object& object,ICameraController& cameraController){
    if (object["name"].get<std::string>() == "robot"){
        std::cout << "We are creating a Robot" << std::endl;
        Robot* newRobot= new Robot(object);

        // Get the position as an array
        picojson::array position = object["position"].get<picojson::array>();
        double x = position[0].get<double>();
        double y = position[1].get<double>();
        double z = position[2].get<double>();
        Vector3 pos = Vector3(x,y,z);
        newRobot->UpdatePosition(pos);

        // Get the direction as an array
        picojson::array dir = object["direction"].get<picojson::array>();
        x= dir[0].get<double>();
        y= dir[1].get<double>();
        z= dir[2].get<double>();
        Vector3 direct = Vector3(x,y,z);
        newRobot->UpdateDirection(direct);

        // Get the id & type of object
        newRobot->SetEntityId(object["entityId"].get<double>());
        newRobot->SetId(object["id"].get<double>());
        newRobot->SetType(object["name"].get<std::string>());

        return newRobot;
    } // end of if Robot 

    return nullptr;
}