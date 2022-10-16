/**
 * @file IEntity.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef IENTITY_H_
#define IENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <memory>
#include <string>
#include "../Observer/IObserver.h"
#include "../vector3.h"
#include <picojson.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class IEntity {
    
public:

    /**
    * @brief Function that will add an observer to the entity
    * 
    * @param[in] new_observer New observer to be added that will receive notifications of the
    *                         entities state changes. 
    */
    virtual void AddObserver(IObserver* new_observer) = 0;

    /**
    * @brief Function that will remove an observer from the entity
    * 
    * @param[in] observer_to_remove observer to be removed if present in the entity when the entity's state changes. 
    */
    virtual void RemoveObserver(IObserver* observer_to_remove) = 0;

    /**
    * @brief Function that will send a message to the observers of that entity
    *        so message gets notified to the UI
    * 
    * @param[in] notification message specifying the entity´s state change
    */
    virtual void Notify(picojson::object& notification) = 0; //const picojson::value& object, const IEntity& entity

    /**
    * @brief A virtual destructor needed to call sub-classes destructors
    */
    virtual ~IEntity()=default;

    /**
    * @brief This will return the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @return integer representing the type of object of the entity
    */
    virtual int GetEntityId()=0;

    /**
    * @brief This will set the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @param[in] id2 integer representing the type of object of the entity
    */
    virtual void SetEntityId(int id2)=0;

    /**
    * @brief This will return a string representing object type "drone", "hospital"...
    * 
    * @return string representing the type of object of the entity
    */
    virtual std::string GetType()=0;

    /**
    * @brief This will set the object type "drone", "hospital"...
    * 
    * @param[in] name string representing the type of object of the entity
    */
    virtual void SetType(std::string& name) =0;

    /**
    * @brief This will return an integer that represents the command in which the object was created
    * 
    * @return id representing the command number 
    */
    virtual int GetId()=0;

    /**
    * @brief This will set the command # in which the object was created
    * 
    * @param[in] id2 the command number as an integer
    */
    virtual void SetId(int id2)=0;

    /**
    * @brief Updates the direction of the entity
    * 
    * @param[in] newDir vector3 representing the new direction of the object
    */
    virtual void UpdateDirection(const Vector3& newDir)=0;

    /**
    * @brief Updates the position of the entity
    * 
    * @param[in] newDir vector3 representing the new position of the object
    */
    virtual void UpdatePosition(const Vector3& newDir)=0;

    /**
    * @brief getter for entity position
    * 
    * @return Vector3 object representing the entity position
    */
    virtual Vector3 GetPosition() const =0;

    /**
    * @brief getter for entity direction
    * 
    * @return Vector3 object representing the entity direction
    */
    virtual Vector3 GetDirection() const =0;

    /**
    * @brief A method to get the pertinent data of an Entity to be written to CSV file.
    *
    * @param[in] dt A float representing the change in time since the last update
    * 
    * @return String Returns a string containing the comma separated data to be written to a CSV file.
    */
    virtual std::string GetData(float dt) = 0;
};


#endif