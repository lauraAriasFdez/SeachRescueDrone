/**
 * @file Camera.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef CAMERA_H_
#define CAMERA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

// Image processor facade
#include "../ImageProcessing/image.h"
#include "../ImageProcessing/color.h"
#include "../ObjectDetector/ObjectDetector.h"
#include "../vector3.h"

// Camera controllers
#include "../camera_controller.h"
#include "CameraResult.h"
#include "../util/base64.h"
#include <fstream>
#include <iostream>
#include <math.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
* @brief A class that processes and takes picture of what the entity is looking at
*/

class Camera: public ICameraObserver {

public:
    /**
    * @brief A constructor for an instance of the Camera class.
    */
    Camera(int id, ICameraController* controller) : id(id), controller(controller) {
        this->controller = controller;
        this->id = id;
        controller->AddObserver(*this);  
        this->result = nullptr;  
    }

    /**
     * @brief A destructor (deallocate result mememory).
     */
    ~Camera(){
        if (this->result != nullptr)
            delete result;
    }
    
    /**
    * @brief Makes the camera take a picture using the specified camera id
    */
    void TakePicture();

    /**
    * @brief Processes images asynchronously. The returned camera result will be passed
    *        into the ImageProcessingComplete(...) method
    * 
    * @param[in] cameraId the id of the camera when created
    * @param[in] xPos the x position of the camera within the visualization
    * @param[in] yPos the y position of the camera within the visualization
    * @param[in] zPos the z position of the camera within the visualization
    * @param[in] images a vector containing the depth and color img to be process
    * @param[in] details a picson obj containing extra details
    * 
    * @return a camera result object if the robot was found with the the position of the
    *         robot or a nullPtr if robot not found
    */
    ICameraResult* ProcessImages(int cameraId, double xPos, double yPos, double zPos, const std::vector<RawCameraImage>& images, picojson::object& details) const;

    /**
    * @brief After the asynchronous image processing, this method will be synchronized with the update loop.
    * 
    * @param[in] result2 a camera result object if the robot was found with the the position of the
    *                    robot or a nullPtr if robot not found
    */
    void ImageProcessingComplete(ICameraResult* result2);

    /**
    * @brief Getter for the result of the camera
    * 
    * @return Camera has a private variable containing the result of the process img that can
    *          be shared with the Entity owner of the camera through this method
    */
    CameraResult* GetCameraResult();
    
private:
    ICameraController* controller;
    int id;
    CameraResult* result;
    
};

#endif