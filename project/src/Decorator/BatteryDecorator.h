/**
 * @file BatteryDecorator.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include "../Entity/IDrone.h"
#include "../Entity/Drone.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class BatteryDecorator: public IDrone{

public:

    /**
    * @brief constructor, sets battery level
    * 
    * @param[in] drone_obj IDrone* base drone to be decorated
    * @param[in] level double amount of battery that the drone starts with
    */
    BatteryDecorator(IDrone* drone_obj,double level=1000);

    /**
    * @brief A destructor for all BatteryDecorator instances
    */
    ~BatteryDecorator();

    /**
    * @brief Calculates the new position of the drone based on Euler´s integration 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    void Update(double dt);

    /**
    * @brief Returns the battery level of the drone 
    */
    float GetBatteryLevel();

/*******************************************************************************
 * IDrone Methods
 ******************************************************************************/
    /**
    * @brief Moves based on keyboard inputs 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    virtual void UpdateManualMovement(double dt);

    /**
    * @brief Calculates the new patrol movement if we are still searching for the robot and
    *          have switch between manual and automatic movement 
    */
    virtual void ResetPatrol();

    /**
    * @brief getter for the velocity of the drone
    * 
    * @return vector3 representing the velocity of the drone
    */
    virtual Vector3 GetVelocity() const;

    /**
    * @brief Updates the velocity of the drone
    * 
    * @param[in] newDir vector3 representing the new velocity of the object
    */
    virtual void UpdateVelocity(const Vector3& newDir);

    /**
    * @brief getter for the speed of one of the legs of the drone
    * 
    * @return double representing the speed of the index propeller 
    */
    virtual double GetPropellerSpeed(int index);

    /**
    * @brief setter for the direction of the drone based on manual movement
    * 
    * @param[in] x double representing the direction on the x direction
    * @param[in] y double representing the direction on the y direction
    * @param[in] z double representing the direction on the z direction
    * @param[in] rotate double representing the rotation value of drone
    */
    virtual void SetJoystick(double x, double y, double z, double rotate);

    /**
    * @brief getter for the state of drone´s search (robot found or Not)
    * 
    * @return boolean true if we have found robot and are moving torwards it, false otherwise
    */
    virtual bool GetSearchStatus()const;

    /**
    * @brief setter for the state of drone´s search (robot found or Not)
    * 
    * @param[in] status boolean true if we have found robot and are moving torwards it, false otherwise
    */
    virtual void SetSearchStatus(bool status);

    /**
    * @brief getter for the last time drone took a pic
    * 
    * @return float representing time elapsed since that picture 
    */
    virtual float GetLastPictureTime()const;

    /**
    * @brief setter for the last time drone took a pic
    * 
    * @param[in] timePic float representing time since lastPicture 
    */
    virtual void SetLastPictureTime(float timePic);

    /**
    * @brief getter for the time elapsed
    * 
    * @return float representing time elapsed (sum of updates dt´s)
    */
    virtual float GetTime()const;

    /**
    * @brief setter for the time elapsed
    * 
    * @param[in] t float representing time elapsed (sum of updates dt´s)
    */
    virtual void SetTime(float t);

/*******************************************************************************
 * Entity Methods
 ******************************************************************************/

    /**
    * @brief This will return an integer that represents the command in which the object was created
    * 
    * @return id representing the command number 
    */
    int GetId();

    /**
    * @brief This will return the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @return integer representing the type of object of the entity
    */
    int GetEntityId();

    /**
    * @brief This will return a string representing object type "drone", "hospital"...
    * 
    * @return string representing the type of object of the entity
    */
    std::string GetType();

    /**
    * @brief This will set the command # in which the object was created
    * 
    * @param[in] id2 the command number as an integer
    */
    void SetId(int id2);

    /**
    * @brief This will set the Entity Id, meaning the type of object (0 represents a drone)
    * 
    * @param[in] id2 integer representing the type of object of the entity
    */
    void SetEntityId(int id2);

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
    *  of the entity
    * 
    * @param[in] new_camera New camera object to be added to the vector
    *  of cameras of the entity
    */
    void AddCamera(Camera* new_camera);

    /**
    * @brief Get the idx camera from the cameras of the entity
    * 
    * @param[in] idx integer representing the camera you want to get
    * 
    * @return Camera object pointer
    */
    Camera* GetCamera(int idx);

    /**
    * @brief A method to get the pertinent data of an Entity to be written to CSV file.
    *
    * @param[in] dt A float representing the change in time since the last update
    * 
    * @return String Returns a string containing the comma separated data to be written to a CSV file.
    */
    std::string GetData(float dt);

    /**
    * @brief A method to get the robot x y z position
    *    
    * @return Vector representing position where robot found
    */
    Vector3 GetRobotPos ()const;
    
    /**
    * @brief A method to set the robot x y z position
    *    
    * @param[in] pos Vector representing position where robot found
    */
    void SetRobotPos(Vector3 pos);

private:
    /**
    * @brief double representing battery level at start of simulation
    */
    double batteryLevel;

    /**
    * @brief IDrone* representing the base drone to be decorated
    */
    IDrone* basicDrone;
};

#endif