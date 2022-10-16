/**
 * @file Entity.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
#ifndef ENTITY_H_
#define ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "IEntity.h"
#include <iostream>
#include "../Camera/Camera.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class Entity: public IEntity{

public:

    /**
    * @brief Default constructor accepting no parameters.
    */
    Entity(){}

    /**
    * @brief Constructor
    * 
    * @param[in] object picson object Object that we want to retrive info from 
    */
    Entity(picojson::object& object){}

// THE BIG 3 since we are using allocated memory 

    /**
    * @brief A destructor that removes/deletes all observers of the entity 
    */
    virtual ~Entity(){
    std::cout << "destroying Entity observers" << std::endl;
    for (int i=0;i<observers.size();i++){
        delete observers[i];
    }
    observers.clear();


    std::cout << "destroying Entity cameras" << std::endl;
    for (int i=0;i<cameras.size();i++){
        delete cameras[i];
    }
    cameras.clear();
}


    /**
    * @brief A copy constructor that allows to copy/duplicate any Entity. 
    * 
    *  @param[in] objectToCopy The Entity object to make a deep copy from.
    */
    Entity(const Entity& objectToCopy){
        *this = objectToCopy;
    }

    /**
    * @brief Performs a deep copy of the Entity object passed in.
    *
    * @param[in] objectToCopy The Entity object to copy from.
    */
    void operator= (const Entity& objectToCopy);


    /******************************
    * NOTIFICATION OBSERVERS
    ******************************/
    /**
    * @brief Function that will add an observer to the entity
    * 
    * @param[in] new_observer New observer to be added that will receive notifications of the
    *                         entities state changes. 
    */
    void AddObserver(IObserver* new_observer);

    /**
    * @brief Function that will remove an observer from the entity
    * 
    * @param[in] observer_to_remove observer to be removed if present in the entity entities state changes. 
    */
    void RemoveObserver(IObserver* observer_to_remove);
    
    /**
    * @brief Function that will send a message to the observers of that entity
    *        so message gets notified to the UI
    * 
    * @param[in] notification message specifying the entity´s state change
    */
    void Notify(picojson::object& notification);


    /******************************
    * GETTERS & SETTERS FOR ENTITY PROPERTIES
    ******************************/
    /**
    * @brief This will return a double which represents radius of entity (for collision)
    * 
    * @return radius of the entity as a double 
    */
    double GetRadius();

    /**
    * @brief This will set a double which represents radius of entity (for collision)
    * 
    * @param[in] r radius of the entity as a double 
    */
    void SetRadius(int r);
    
    /**
    * @brief This will return an integer that represents the command in which the object was created
    * 
    * @return id representing the command number 
    */
    int GetId();

    /**
    * @brief This will set the command # in which the object was created
    * 
    * @param[in] id2 the command number as an integer
    */
    void SetId(int id2);

    /**
    * @brief This will return the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @return integer representing the type of object of the entity
    */
    int GetEntityId();

    /**
    * @brief This will set the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @param[in] id2 integer representing the type of object of the entity
    */
    void SetEntityId(int id2);
    
    /**
    * @brief This will return a string representing object type "drone", "hospital"...
    * 
    * @return string representing the type of object of the entity
    */
    std::string GetType();

    /**
    * @brief This will set the object type "drone", "hospital"...
    * 
    * @param[in] name string representing the type of object of the entity
    */
    void SetType(std::string& name);

    /**
    * @brief Updates the direction of the entity
    * 
    * @param[in] newDir vector3 representing the new direction of the object
    */
    void UpdateDirection(const Vector3& newDir);

    /**
    * @brief Updates the position of the entity
    * 
    * @param[in] newDir vector3 representing the new position of the object
    */
    void UpdatePosition(const Vector3& newDir);

    /**
    * @brief getter for entity position
    * 
    * @return Vector3 object representing the entity position
    */
    Vector3 GetPosition() const;

    /**
    * @brief getter for entity direction
    * 
    * @return Vector3 object representing the entity direction
    */
    Vector3 GetDirection() const;

    /******************************
    * CAMERA OF ENTITY 
    ******************************/
    /**
    * @brief Function that will add a camera to the vector of cameras
    *          of the entity
    * 
    * @param[in] new_camera New camera object to be added to the vector
    *                        of cameras of the entity
    */
    virtual void AddCamera(Camera* new_camera);

    /**
    * @brief Get the idx camera from the cameras of the entity
    * 
    * @param[in] idx integer representing the camera you want to get
    * 
    * @return Camera object pointer
    */
    virtual Camera* GetCamera(int idx);

    /**
    * @brief A method to get the pertinent data of an Entity to be written to CSV file.
    *
    * @param[in] dt A float representing the change in time since the last update
    * 
    * @return String Returns a string containing the comma separated data to be written to a CSV file.
    */
    std::string GetData(float dt);

protected:
// since you want derived classes acces =protected
    /**
    * @brief A vector of observer pointer objects that need to be 
    *       notify if this entity changes states
    */
    std::vector<IObserver*> observers;

    /**
    * @brief int representing command number when entity was created
    */
    int id;

    /**
    * @brief int representing type of object (0 represents a drone)
    */
    int entity_id;

    /**
    * @brief string representing object type "drone", "hospital"...
    */
    std::string type;

    /**
    * @brief A vector representing the position of the Entity.
    */
    Vector3 position;

    /**
    * @brief A vector representing the direction of the Entity.
    */
    Vector3 direction;

    /**
    * @brief A double representing the radius of the Entity.
    */
    double radius;

    /**
    * @brief A vector of pointers to instances of the Camera class representing the cameras that the Entity can use.
    */
    std::vector<Camera*> cameras;
};
#endif
