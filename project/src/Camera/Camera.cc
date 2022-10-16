/**
 * @file Camera.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "Camera.h"

/*******************************************************************************
 * Methods of Camera Class
 ******************************************************************************/
void Camera::TakePicture() {
        controller->TakePicture(id);
    }

ICameraResult* Camera::ProcessImages(int cameraId, double xPos, double yPos, double zPos, const std::vector<RawCameraImage>& images, picojson::object& details) const {

    // Define facade that will look at picture taken by camera to see if robot found
    ObjectDetector obj_detector = ObjectDetector();

    // Write picture to file __________________________________
    if (cameraId == id || cameraId < 0) {
        // These will output the image to files.  Ultimately this is just for debugging:
        std::ofstream colorFile ("color.jpg", std::ios::out | std::ios::binary);
        colorFile.write (reinterpret_cast<const char*>(images[0].data), images[0].length);
        std::ofstream depthFile ("depth.jpg", std::ios::out | std::ios::binary);
        depthFile.write (reinterpret_cast<const char*>(images[1].data), images[1].length);
               

        // Generate the result of image processing. __________________________________
        if (images[0].length == 0){
            std::cout<<"empty color pic" << std::endl;
            return NULL;
        }

        cv::Mat img_matrix = imread("color.jpg");
        bool found = obj_detector.Found(img_matrix);
            
        
        // If robot found return a Camera Result else return nullptr  __________________________________
        if (found == true){

            // Return value
            CameraResult* result2 = new CameraResult();
            Vector3 cameraPos = Vector3(xPos,yPos,zPos);
            result2->SetFoundRobot(found);


            // SAVE IMG OF FOUND (debugging purposes & grading purposes)
            std::ofstream foundFile ("found.jpg", std::ios::out | std::ios::binary);
            foundFile.write (reinterpret_cast<const char*>(images[0].data), images[0].length);

            //1- Get from object detector which ith pixel we want to calculate as the robot (big cluster of orange)
            int robot_x, robot_y;
            obj_detector.GetRobotPos(robot_x,robot_y);

            //2- Get the r,g,b values of that pixel from DEPTH img and  Convert RGB to values between 0-1 
            Image depth_img = Image((unsigned char*)images[1].data, images[1].length);
            Color* robot_pixel = depth_img.GetPixel(robot_x,robot_y);

            double red = ((double) robot_pixel->GetRed())/255.0;
            double blue = ((double) robot_pixel->GetBlue())/255.0;
            double green = ((double) robot_pixel->GetGreen())/255.0;

            //3- Use the depth value to calculate position of robot            
            Vector3 DirectionUnitVec = (Vector3(red,green,blue)- Vector3(0.5,0.5,0.5)) * 2.0;
            double mag = DirectionUnitVec.Magnitude();
            Vector3 direction = DirectionUnitVec/mag;
                            
            // 4. Distance = (1.0 - magnitude of directionUnitVector) * 50.0
            double distance = (1.0 -  mag) * 50.0;
            

            //5 -Robot Location = CameraPosition + (Distance * DirectionUnitVec)
            std::cout<< "camera pos is x: "<< cameraPos.GetX() << "y: "<<cameraPos.GetY()<<" z "<<cameraPos.GetZ() <<std::endl;
            Vector3 pos_robot = cameraPos + (direction * distance);
            pos_robot.SetY(1.0);
            result2->SetFoundRobot(pos_robot);  
            return result2;

        } // end if found robot
    } // end if camera exist
    
    return NULL;
}


void Camera::ImageProcessingComplete(ICameraResult* result2) {

    // if null meaning no camers OR NOT found
    if (result2==NULL || result2==nullptr)
        return;

    // if result2 is NOT a null value it means we have FOUND ROBOT
    // get info from result passed
    CameraResult& res = *static_cast<CameraResult*>(result2);    
    if (res.GetFoundRobot()) {
        Vector3 pos = res.GetRobotPos();
        std::cout << "The robot was found here: " << pos.GetX() << ", " << pos.GetY() << ", " << pos.GetZ() << std::endl;
    }

    // We want to store the result of the camera when the robot was found
    if (this->result != nullptr){
            delete result;
    }
    this->result = static_cast<CameraResult*>(result2);
}

CameraResult* Camera::GetCameraResult(){return this->result;} 