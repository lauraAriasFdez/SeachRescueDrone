/**
 * @file CameraResult.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */
 
#ifndef CAMERA_RESULT_H_
#define CAMERA_RESULT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../vector3.h"
#include "../camera_controller.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief A class that strores the result of processing an img when looking for a robot
*/
class CameraResult:public ICameraResult {
public:
    /**
    * @brief An empty constructor
    */
    CameraResult(){}

    /**
    * @brief Getter of img result
    * 
    * @return true if robot was found when processing this img, false otherwise
    */
    bool GetFoundRobot ()const;

    /**
    * @brief Setter of img result
    * 
    * @param[in] f true if robot was found when processing this img, false otherwise
    */
    void SetFoundRobot(bool f);

    /**
    * @brief Getter of robot position
    * 
    * @return a Vector3 with the x,y,z values of where the robot is located in the map
    */
    Vector3 GetRobotPos ()const;

    /**
    * @brief Setter of robot pos
    * 
    * @param[in] pos a Vector3 with the x,y,z values of where the robot is located in the map
    */
    void SetFoundRobot(Vector3 pos);

private:
        bool found;
        Vector3 robot_pos;
};

#endif