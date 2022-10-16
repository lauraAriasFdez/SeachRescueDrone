/**
 * @file Drone.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "IDrone.h"
#include "../Movement/Patrol.h"
#include "../Movement/Beeline.h"
#include "../Camera/CameraResult.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class Drone:public IDrone {

public:
    /**
    * @brief empty constructor 
    */
    Drone() {
        this->perform = new Patrol();
    }

    /**
    * @brief Constructor
    * 
    * @param[in] object picson object Object that we want to retrive info from 
    */
    Drone( picojson::object& obj):IDrone(obj) {
        this->perform = new Patrol();
    }

    /**
    * @brief A destructor for all Drone instances
    */
    ~Drone() {
        delete this->perform;
    }

    /**
    * @brief Moves based on keyboard inputs 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    void UpdateManualMovement (double dt);

    /**
    * @brief Calculates the new position of the drone based on Euler´s integration 
    * 
    * @param[in] dt period of time it has elapsed since last update
    */
    void Update(double dt);

    /**
    * @brief Calculates the new patrol movement if we are still searching for the robot and
    *          have switch between manual and automatic movement 
    */
    void ResetPatrol();

    /**
    * @brief getter for the velocity of the drone
    * 
    * @return vector3 representing the velocity of the drone
    */
    Vector3 GetVelocity() const;

    /**
    * @brief Updates the velocity of the drone
    * 
    * @param[in] newDir vector3 representing the new velocity of the object
    */
    void UpdateVelocity(const Vector3& newDir);
    
    /**
    * @brief getter for the speed of one of the legs of the drone
    * 
    * @return double representing the speed of the index propeller 
    */
    double GetPropellerSpeed(int index);

    /**
    * @brief setter for the direction of the drone based on manual movement
    * 
    * @param[in] x double representing the direction on the x direction
    * @param[in] y double representing the direction on the y direction
    * @param[in] z double representing the direction on the z direction
    * @param[in] rotate double representing the rotation value of drone
    */
    void SetJoystick(double x, double y, double z, double rotate);
    
    /**
    * @brief getter for the state of drone´s search (robot found or Not)
    * 
    * @return boolean true if we have found robot and are moving torwards it, false otherwise
    */
    bool GetSearchStatus()const;

    /**
    * @brief setter for the state of drone´s search (robot found or Not)
    * 
    * @param[in] status boolean true if we have found robot and are moving torwards it, false otherwise
    */
    void SetSearchStatus(bool status);

    /**
    * @brief getter for the last time drone took a pic
    * 
    * @return float representing time elapsed since that picture 
    */
    float GetLastPictureTime()const;

    /**
    * @brief setter for the last time drone took a pic
    * 
    * @param[in] timePic float representing time since lastPicture 
    */
    void SetLastPictureTime(float timePic);

    /**
    * @brief getter for the time elapsed
    * 
    * @return float representing time elapsed (sum of updates dt´s)
    */
    float GetTime()const;

    /**
    * @brief setter for the time elapsed
    * 
    * @param[in] t float representing time elapsed (sum of updates dt´s)
    */
    void SetTime(float t);

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
};

#endif