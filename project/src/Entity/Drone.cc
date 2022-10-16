/**
 * @file Drone.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Drone.h"

/*******************************************************************************
 * Methods of Drone Class
 ******************************************************************************/


/******************************
 * MOVEMENT
 ******************************/
void Drone::UpdateManualMovement (double dt){
    //1. Take a picture every 3 seconds with front camera____________________
    this->time += dt;
    if (this->time-this->lastPictureTime > 3.0) {
        
        if ((this->GetCamera(0)) != nullptr)
            (this->GetCamera(0))->TakePicture();

        this->lastPictureTime = this->time;
    }
    
    // 2. If camera exists and I have not found robot: check result of camera image___________________
    if ((this->GetCamera(0)) != nullptr && !this->search){
        CameraResult* result = (this->GetCamera(0))->GetCameraResult();
        if (result != nullptr){
            this->search= result->GetFoundRobot();
            Vector3 pos = result->GetRobotPos();
            if (this->search){
                std::cout << "DRONE info: The robot was found here: " << pos.GetX() << ", " << pos.GetY() << ", " << pos.GetZ() << std::endl;
                this->robot_position_if_found = Vector3(((float)pos.GetX()),((float)pos.GetY()),((float)pos.GetZ()));
            }
        }
    }

    // Not eurlers integration because we depend on setjoystick 
    this->UpdatePosition(this->GetPosition() + this->GetDirection() * velocity.Magnitude()* dt);
}


void Drone::Update(double dt){
    //1. Take a picture every 3 seconds with front camera____________________
    this->time += dt;
    if (this->time-this->lastPictureTime > 3.0) {
        
        if ((this->GetCamera(0)) != nullptr)
            (this->GetCamera(0))->TakePicture();

        this->lastPictureTime = this->time;
    }

    // 2. If camera exists and I have not found robot: check result of camera image___________________
    if ((this->GetCamera(0)) != nullptr && !this->search){
        CameraResult* result = (this->GetCamera(0))->GetCameraResult();
        if (result != nullptr){
            this->search= result->GetFoundRobot();
            Vector3 pos = result->GetRobotPos();
            if (this->search){
                std::cout << "DRONE info: The robot was found here: " << pos.GetX() << ", " << pos.GetY() << ", " << pos.GetZ() << std::endl;
                this->robot_position_if_found = Vector3(((float)pos.GetX()),((float)pos.GetY()),((float)pos.GetZ()));
            }
        }
    }

    /////////////////MOVEMENT BASED ON RESULTS 
    //3.  Do a Patrol to populate the queue of locations to visit if !search && locationsToVisit is empty___________________
    if (!this->search && this->locationsToVisit.size() == 0) { 
        this->perform->Move(this->position, this->locationsToVisit);
    } 
    
    //4. If we have found the Robot Beeline it to the Robot ___________________
    if (this->search) {
        this->locationsToVisit = std::queue<Vector3>(); // Clear the queue of locations to visit
        
        // Free the memory of the current perform that is pointing to a Patrol Movement and set it to be a Beeline
        delete perform;
        this->perform = new Beeline();
        
        // Call Beeline with the position of the Robot
        // robot_position_if_found set when analyzing camera results
        this->perform->Move(this->robot_position_if_found, this->locationsToVisit); 

        // PRINTING PATROL MOVEMENT = WORKING 
        //std::cout<<"Patrol movement"<<std::endl;
        //this->robot_position_if_found.Print();

    }

    //5. If the queue of locations has a point to visit, set it location in the front of the queue to be the Drone's direction
    if (locationsToVisit.size() > 0) {
        this->UpdateDirection(locationsToVisit.front());

        // Debug
        //if (this->search)
            //std::cout<<"going to x: "<<this->direction.GetX()<<" y "<<this->direction.GetY()<<" z "<<  this->direction.GetZ()<<std::endl;
    } else {
        this->UpdateDirection(this->position);
    }

    // ********************************************
    // 6. Euler´s Integration if not arrived to destination ___________________
    // ********************************************
    if (std::abs((this->position.Distance(this->direction))) <= 0.5 ) { 
        // If we have arrived we can pop it from queue           
        locationsToVisit.pop(); // Pop the location from the queue of places to visit as we are there
        this->UpdateDirection(this->direction - this->position); 

            
        return;
    } else {
        // Euler Integration
        Vector3 d = (this->direction - this->position); // Calculate the new direction that we need to be moving
        d = d/d.Magnitude(); // Normalize the new direction vector

        this->velocity = d * this->velocity.Magnitude();// Calculate the velocity of the drone
        Vector3 distanceTraveled = this->velocity * dt; // Calculate the distance traveled over the time step

        // Move the drone to the new position
        this->UpdatePosition(this->GetPosition() + distanceTraveled);

        //this makes sure camera looks in the right direction (in the direction of position moving)
        this->UpdateDirection(this->direction - this->position);
    }
}


void Drone::ResetPatrol(){
    // if we are still looking for robot
    if (!this->search){
        this->locationsToVisit = std::queue<Vector3>(); // Clear the queue of locations to visit
        this->perform->Move(this->position, this->locationsToVisit);
    }else {
        // error in drone creation
        delete this->perform;
        this->perform = new Patrol();
        this->locationsToVisit = std::queue<Vector3>(); // Clear the queue of locations to visit
        this->perform->Move(this->position, this->locationsToVisit);
    }
}
/******************************
 * MOVEMENT GETTERS
 ******************************/
Vector3 Drone::GetVelocity() const{return this->velocity;};

void Drone::UpdateVelocity(const Vector3& newDir) {
    this->velocity = newDir;
}

double Drone::GetPropellerSpeed(int index){
    return 1.0;
}

void Drone::SetJoystick(double x, double y, double z, double rotate){ 
    this->UpdateDirection(Vector3(x,y,z));
}

bool Drone::GetSearchStatus()const{
    return this->search;
}

Vector3 Drone::GetRobotPos ()const{
    return (this->robot_position_if_found);
}
void Drone::SetRobotPos(Vector3 pos){
    this->robot_position_if_found=pos;
}
/******************************
 * NOTIFICATION----------
 ******************************/
void Drone::SetSearchStatus(bool status){
    if (status == true) 
        std::string message_to_observer = "Drone has found Robot (Beeline Movement starting)";
    else
        std::string message_to_observer = "Drone has not found Robot (Patrol Movement starting)";
    this->search = status;
    //picojson::object notification_builder = JsonHelper::CreateJsonNotification();
    //JsonHelper::AddStringToJsonObject(notification_builder, "Drone Search Status", message_to_observer);
    //Notify(notification_builder);
}


/******************************
 * CAMERA NEEDED GETTERS 
 ******************************/
float Drone::GetLastPictureTime()const{
    return this->lastPictureTime;
}

void Drone::SetLastPictureTime(float timePic){
    this->lastPictureTime = timePic;
}

float Drone::GetTime()const{
    return this->time;
}

void Drone::SetTime(float t) {
    this->time = t;
}
