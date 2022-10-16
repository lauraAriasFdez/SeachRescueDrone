/**
 * @file BatteryDecorator.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BatteryDecorator.h"

/*******************************************************************************
 * Methods of BatteryDecorator Class
 ******************************************************************************/
BatteryDecorator::BatteryDecorator(IDrone* drone_obj,double level){
    batteryLevel= level;
    basicDrone = drone_obj;
}

BatteryDecorator::~BatteryDecorator(){
    delete basicDrone;
}

void BatteryDecorator::Update(double dt){
    if (batteryLevel >0){
        batteryLevel = batteryLevel - dt;
        basicDrone->Update(dt);
        return;
    }
    //std::cout<<"Drone has no battery left"<<std::endl;
    //std::string message_to_observer = "Drone has no battery left";
    //picojson::object notification_builder = JsonHelper::CreateJsonNotification();
    //JsonHelper::AddStringToJsonObject(notification_builder, "rescued Status", message_to_observer);
    //Notify(notification_builder);
}

float BatteryDecorator::GetBatteryLevel(){
    return batteryLevel;
};

/*******************************************************************************
 * IDrone methods
 ******************************************************************************/
void BatteryDecorator::UpdateManualMovement(double dt){
    if (batteryLevel >0){
        batteryLevel = batteryLevel - dt;
        basicDrone->UpdateManualMovement(dt);
        return;
    }
    std::cout<<"Drone has no battery left"<<std::endl;
    std::string message_to_observer = "Drone has no battery left";
};
void BatteryDecorator::ResetPatrol(){
    basicDrone->ResetPatrol();
};
Vector3 BatteryDecorator::GetVelocity() const{
    return(basicDrone->GetVelocity());
};
void BatteryDecorator::UpdateVelocity(const Vector3& newDir){
    basicDrone->UpdateVelocity(newDir);
};
double BatteryDecorator::GetPropellerSpeed(int index){
    return(basicDrone->GetPropellerSpeed(index));
};
void BatteryDecorator::SetJoystick(double x, double y, double z, double rotate){
    basicDrone->SetJoystick(x,y,z,rotate);
};
bool BatteryDecorator::GetSearchStatus()const{
    return (basicDrone->GetSearchStatus());
};
void BatteryDecorator::SetSearchStatus(bool status){
    basicDrone ->SetSearchStatus(status);
};
float BatteryDecorator::GetLastPictureTime()const{
    return (basicDrone->GetLastPictureTime());
};
void BatteryDecorator::SetLastPictureTime(float timePic){
    basicDrone ->SetLastPictureTime(timePic);
};
float BatteryDecorator::GetTime()const{
    return (basicDrone ->GetTime());
};
void BatteryDecorator::SetTime(float t){
    basicDrone ->SetTime(t);
};

Vector3 BatteryDecorator::GetRobotPos ()const{
    return (basicDrone->GetRobotPos());
}
void BatteryDecorator::SetRobotPos(Vector3 pos){
    basicDrone->SetRobotPos(pos);
}
/*******************************************************************************
 * Entity Methods
 ******************************************************************************/
int BatteryDecorator::GetId(){return ( basicDrone->GetId() );}
int BatteryDecorator::GetEntityId(){return ( basicDrone->GetEntityId() );};
std::string BatteryDecorator::GetType(){return ( basicDrone->GetType() );}

void BatteryDecorator::SetId(int id2) {basicDrone->SetId(id2);}
void BatteryDecorator::SetEntityId(int id2) {basicDrone->SetEntityId(id2);}
void BatteryDecorator::SetType(std::string& name) {basicDrone->SetType(name);}

void BatteryDecorator::UpdateDirection(const Vector3& newDir) {basicDrone->UpdateDirection(newDir);}
void BatteryDecorator::UpdatePosition(const Vector3& newDir) {basicDrone->UpdatePosition(newDir);}
Vector3 BatteryDecorator::GetPosition() const{return ( basicDrone->GetPosition() );}
Vector3 BatteryDecorator::GetDirection() const{return ( basicDrone->GetDirection() );}

/******************************
* CAMERA OF ENTITY 
******************************/
void BatteryDecorator::AddCamera(Camera* new_camera) {basicDrone->AddCamera(new_camera);}
Camera* BatteryDecorator::GetCamera(int idx) {return (basicDrone->GetCamera(idx));}
std::string BatteryDecorator::GetData(float dt) {return (basicDrone->GetData(dt));}