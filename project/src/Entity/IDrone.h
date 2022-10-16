/**
 * @file IDrone.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef IDRONE_H_
#define IDRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Entity.h"
#include "../vector3.h"
#include "../Movement/IMovement.h"
#include <queue>

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class IDrone:public Entity {

public:

    /**
    * @brief empty constructor 
    */
    IDrone(){}

    /**
    * @brief Constructor
    * 
    * @param[in] object picson object Object that we want to retrive info from 
    */
    IDrone(picojson::object& obj):Entity(obj){}

    /**
    * @brief Moves based on keyboard inputs 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    virtual void UpdateManualMovement (double dt) = 0;

    /**
    * @brief calculates the new position of the drone based on Euler´s integration 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    virtual void Update(double dt) = 0;

    /**
    * @brief Calculates the new patrol movement if we are still searching for the robot and
    *          have switch between manual and automatic movement 
    */
    virtual void ResetPatrol() = 0;

    /**
    * @brief getter for the velocity of the drone
    * 
    * @return vector3 representing the velocity of the drone
    */
    virtual Vector3 GetVelocity() const = 0;

    /**
    * @brief Updates the velocity of the drone
    * 
    * @param[in] newDir vector3 representing the new velocity of the object
    */
    virtual void UpdateVelocity(const Vector3& newDir) = 0;

    /**
    * @brief getter for the speed of one of the legs of the drone
    * 
    * @return double representing the speed of the index propeller 
    */
    virtual double GetPropellerSpeed(int index)= 0;

    /**
    * @brief setter for the direction of the drone based on manual movement
    * 
    * @param[in] x double representing the direction on the x direction
    * @param[in] y double representing the direction on the y direction
    * @param[in] z double representing the direction on the z direction
    * @param[in] rotate double representing the rotation value of drone
    */
    virtual void SetJoystick(double x, double y, double z, double rotate)= 0;

    /**
    * @brief getter for the state of drone´s search (robot found or Not)
    * 
    * @return boolean true if we have found robot and are moving torwards it, false otherwise
    */
    virtual bool GetSearchStatus()const =0;

    /**
    * @brief setter for the state of drone´s search (robot found or Not)
    * 
    * @param[in] status boolean true if we have found robot and are moving torwards it, false otherwise
    */
    virtual void SetSearchStatus(bool status) =0;

    /**
    * @brief getter for the last time drone took a pic
    * 
    * @return float representing time elapsed since that picture 
    */
    virtual float GetLastPictureTime()const =0;

    /**
    * @brief setter for the last time drone took a pic
    * 
    * @param[in] timePic float representing time since lastPicture 
    */
    virtual void SetLastPictureTime(float timePic) =0;

    /**
    * @brief getter for the time elapsed
    * 
    * @return float representing time elapsed (sum of updates dt´s)
    */
    virtual float GetTime()const =0;

    /**
    * @brief setter for the time elapsed
    * 
    * @param[in] t float representing time elapsed (sum of updates dt´s)
    */
    virtual void SetTime(float t) =0;

    /**
    * @brief A method to get the robot x y z position
    *    
    * @return Vector representing position where robot found
    */
    virtual Vector3 GetRobotPos ()const =0;
    /**
    * @brief A method to set the robot x y z position
    *    
    * @param[in] pos Vector representing position where robot found
    */
    virtual void SetRobotPos(Vector3 pos)  =0;
protected:
    /**
    * @brief vector3 representing the velocity of the drone
    * 
    */
    Vector3 velocity;
    /**
    * @brief float representing time of last picture taken
    */
    float lastPictureTime = 0.0;
    /**
    * @brief float representing time ellapsed
    */
    float time = 0.0;
    /**
    * @brief vector3 representing the robot position iff found
    */
    Vector3 robot_position_if_found;

    /**
    * @brief boolean representing if we have found Drone or not 
    */
    bool search = false;

    /**
    * @brief IMovement* A pointer to a movement strategy for the Done to move around the scene with
    */
    IMovement* perform;

    /**
    * @brief std::queue<Vector3> A queue representing locations the Drone should visit on the map 
    */
    std::queue<Vector3> locationsToVisit;
};

#endif