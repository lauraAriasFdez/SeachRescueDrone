/**
 * @file Entity.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Entity.h"

/*******************************************************************************
 * Methods of Entity Class
 ******************************************************************************/

/******************************
* THE BIG 3 FOR MEMORY
******************************/


void Entity::operator= (const Entity& objectToCopy){
    //delete all observers of this object
    std::cout << "destroying Entity observers" << std::endl;
    for (int i=0;i<observers.size();i++){
        delete observers[i];
    }
    observers.clear();

    // copy observers from the other object into this object
    for (int i=0;i<objectToCopy.observers.size();i++){
        this->AddObserver(objectToCopy.observers[i]);
    }
}

/******************************
* NOTIFICATION OBSERVERS
******************************/

void  Entity::AddObserver(IObserver* new_observer){
    this->observers.push_back(new_observer);
}

void  Entity::RemoveObserver(IObserver* observer_to_remove){
    for (int i=0;i<observers.size();i++){
        if (observers[i] == observer_to_remove){
            observers.erase(observers.begin()+i);
            return;
        }
    }
    // possible source or error: do we need to ue the keyword delete? 

}

void  Entity::Notify(picojson::object& notification){
    /*picojson::value notification_to_send = JsonHelper::ConvertPicojsonObjectToValue(notification);
    for (int i = 0; i < observers.size();i++){
        observers[i]->OnEvent(notification_to_send);
    }*/
    return;
}

/******************************
* GETTERS & SETTERS FOR ENTITY PROPERTIES
******************************/
double Entity::GetRadius(){return radius;}
void  Entity::SetRadius(int r){radius = r;}

int  Entity::GetId(){return id;}
void  Entity::SetId(int id2){id = id2;}

int  Entity::GetEntityId(){return entity_id;}
void  Entity::SetEntityId(int id2){entity_id=id2;}

std::string  Entity::GetType(){return type;}
void  Entity::SetType(std::string& name){
    this->type = name;
}

void  Entity::UpdateDirection(const Vector3& newDir) {
    this->direction = newDir;
}
void  Entity::UpdatePosition(const Vector3& newDir) {
    this->position = newDir;
}

Vector3  Entity::GetPosition() const{return this->position;}
Vector3  Entity::GetDirection() const{return this->direction;}

// Method to return a list of comma-separated information about the Entity for a CSV file
std::string Entity::GetData(float dt) {
    std::string data;

    data += std::to_string(dt) + ","; // Log dt
    data += type + ","; // Log the type of entity
    data += std::to_string(entity_id) + ","; // Log the entity id

    data += std::to_string(position.GetX()) + ","; // Log entity x-Position
    data += std::to_string(position.GetY()) + ","; // Log entity y-Position
    data += std::to_string(position.GetZ()); // Log entity z-Position

    return data;
}

/******************************
 * CAMERA OF ENTITY 
 ******************************/
void Entity::AddCamera(Camera* new_camera){
    this->cameras.push_back(new_camera);
}

Camera* Entity::GetCamera(int idx){
    if (idx < cameras.size())
        return cameras[idx];
    return nullptr;
}
