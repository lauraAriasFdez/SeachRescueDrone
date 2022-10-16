/**
 * @file Robot.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Robot.h"

/*******************************************************************************
 * Methods of Robot Class
 ******************************************************************************/
bool Robot::GetIsRescued() const{
    return this->isRescued;
}

void Robot::SetIsRescued(bool val){

if (val == true)
    std::string message_to_observer = "Robot has been rescued";
else
    std::string message_to_observer = "Robot Not yet rescued";

//picojson::object notification_builder = JsonHelper::CreateJsonNotification();
//JsonHelper::AddStringToJsonObject(notification_builder, "rescued Status", message_to_observer);
//Notify(notification_builder);
this->isRescued = val;
}