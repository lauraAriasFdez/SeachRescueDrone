/**
 * @file RescueSimulation.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

 /*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "RescueSimulation.h"

 RescueSimulation::RescueSimulation(){
  // Set manual movement boolean flags to false to start with automatic patrol movement
  this->manual_mov = false;
  this->reset_drone_mov =false;
  this->rescue_drone_with_robot = false;
  this->arrived_at_robot = false;
  this->robotPos = Vector3(0,0,0);
  this->update_val = 0;
  this->robot = nullptr;

  // Add Factories of entities
  factories = CompositeEntityFactory();
  factories.AddFactory(new DroneFactory());
  factories.AddFactory(new HospitalFactory());
  factories.AddFactory(new RobotFactory());
  factories.AddFactory(new RechargeStationFactory());

  // Overwrite statistics.csv file on the start of a new RescueSimulation
  DataCollector::GetInstance().Log("dt,type,entityID,x-position,y-position,z-position", true);
}

RescueSimulation::~RescueSimulation(){
  // CompositeEntityFactory factories member variable's destructor will take care of the destruction of the factories

  // Delete all entities created
  for (int i=0;i<entities.size();i++){
      delete entities[i];
  }
  delete robot;
}

IEntity* RescueSimulation::CreateEntity(picojson::object& object, ICameraController& cameraController){
  // Attempt to create a new entity using one of the entity factories in the factories member variable with the picojson object and ICameraController passed into the method
  IEntity* ent =  factories.CreateEntity(object, cameraController);

  // If ent does not point to nullptr, an entity was successfully created, so push it onto the vector of entities created
  if (ent != nullptr) {
      if (ent->GetType()=="robot")
         this->robot= static_cast<Robot*>(ent);
      else if (ent->GetType()== "rescue drone")
          this->rescue_drone = static_cast<Drone*>(ent);
      else
        entities.push_back(ent);

      //get hospital position
      if (ent->GetType()=="hospital")
        this->hospitalPos = ent->GetPosition();
  }

  return ent;
}

void RescueSimulation::Update(float dt){
  // Iterate over all entities that have been created in the simulation
  for (int i = 0; i < entities.size(); i++) {

    // Since Drones are the only moveable object, only the Drone entities will move
    if (entities[i]->GetType()== "drone"){
        Drone* drone   = static_cast<Drone*>(entities[i]);

        // If we are switching out of manual movement, the list of locations to visit needs to be reestablished
        if (this->reset_drone_mov)
          drone->ResetPatrol();

        this->reset_drone_mov = false; // Reset the boolean flag tracking having to reset the Drone's movement to false
	
        drone->Update(dt);

        // check if we have found robot - RESUCE DRONE SHOULD START
        if (drone->GetSearchStatus()){
            this->robotPos = drone->GetRobotPos();
            float dist = std::abs((drone->GetPosition().Distance(this->robotPos)));
            if (std::abs((drone->GetPosition().Distance(this->robotPos))) <= 1.5){
              this->arrived_at_robot= true;

              // edge case in which depth img not well calculated so we need to loop through the position 
              // to find img again 
              if (this->robot == nullptr){
                std::cout << "Recalculating where robot is because depth img not accurate and robot eas not created"<<std::endl;
                drone->SetSearchStatus(false);
                drone->ResetPatrol();
                this->arrived_at_robot= false;
              }
            }
        }
        //depth img is incorrect and sometimes cannot go exactly to where robot is 
        // the following statement will work only if camera has found it and at another point it passsed nearby 
        else if (this->robot != nullptr){
          drone->SetRobotPos(robot->GetPosition());
        }
        // Log the Entity information to the CSV file on each update
        DataCollector::GetInstance().Log(entities[i]->GetData(dt), false);
    }
      
  }

  // RESCUE SIMULATION  UPDATE 
  if (this->arrived_at_robot){
      if (this->robot == nullptr){
        //depth img is incorrect and sometimes cannot go exactly to where robot is 
        rescue_drone->SetRobotPos(this->robotPos);
      }
      else{
        rescue_drone->SetRobotPos(robot->GetPosition());
        this->robotPos = robot->GetPosition();
      }
        
      rescue_drone->SetSearchStatus(true);

        // check if we have arrived near the robot 
        if (std::abs((rescue_drone->GetPosition().Distance(this->robotPos ))) <= 1.5)
              this->rescue_drone_with_robot= true;

        // set the hospital position beeline if drone with robot
        if (this->rescue_drone_with_robot)
          rescue_drone->SetRobotPos(this->hospitalPos);

        // update movement
        rescue_drone->Update(dt);
        
        // move robot also if rescue drone with robot
        if (this->rescue_drone_with_robot && this->robot != nullptr)
          robot->UpdatePosition(rescue_drone->GetPosition());
    } 

}

void RescueSimulation::UpdateManualMovement(float dt, double x, double y, double z, double rot){
  // Iterate over all entities that have been created in the simulation
  for (int i = 0; i < entities.size(); i++) {

    // Since Drones are the only moveable object, only the Drone entities will move
    if (entities[i]->GetType()== "drone"){
      Drone* drone = static_cast<Drone*>(entities[i]);
      drone->SetJoystick(x,y,z,rot);
      drone->UpdateManualMovement(dt);
      
    // check if we have found robot - RESUCE DRONE SHOULD START
      if (drone->GetSearchStatus()){
          this->robotPos = drone->GetRobotPos();
          float dist = std::abs((drone->GetPosition().Distance(this->robotPos)));
          if (std::abs((drone->GetPosition().Distance(this->robotPos))) <= 1.5){
            this->arrived_at_robot= true;
          }
      }
      //depth img is incorrect and sometimes cannot go exactly to where robot is 
      // the following statement will work only if camera has found it and at another point it passsed nearby 
      else if (this->robot != nullptr){
        drone->SetRobotPos(robot->GetPosition());
      }

      // Log the Entity information to the CSV file on each update
      DataCollector::GetInstance().Log(entities[i]->GetData(dt), false);
    }
  }

  // RESCUE SIMULATION  UPDATE 
  if (this->arrived_at_robot){
      if (this->robot == nullptr){
        //depth img is incorrect and sometimes cannot go exactly to where robot is 
        rescue_drone->SetRobotPos(this->robotPos);
      }
      else{
        rescue_drone->SetRobotPos(robot->GetPosition());
        this->robotPos = robot->GetPosition();
      }
        
      rescue_drone->SetSearchStatus(true);

        // check if we have arrived near the robot 
        if (std::abs((rescue_drone->GetPosition().Distance(this->robotPos ))) <= 1.5)
              this->rescue_drone_with_robot= true;

        // set the hospital position beeline if drone with robot
        if (this->rescue_drone_with_robot)
          rescue_drone->SetRobotPos(this->hospitalPos);

        // update movement
        rescue_drone->Update(dt);
        
        // move robot also if rescue drone with robot
        if (this->rescue_drone_with_robot && this->robot != nullptr)
          robot->UpdatePosition(rescue_drone->GetPosition());
    }

}

int RescueSimulation::GetNumberOfEntities() {
  return entities.size();
}

bool RescueSimulation::GetManualMov() {
  return this->manual_mov;
}

void RescueSimulation::SetManualMov(){
  this->manual_mov = (!(this->manual_mov)); // Swap boolean flag tracking manual movement
  this->reset_drone_mov = true; // Set boolean flag tracking if the Drone's movement locations will need to be reset on the next transfer back to automatic movement
}

double RescueSimulation::GetLowestBatteryLevel() {
  return this->lowest_battery_level;
}

void RescueSimulation::FinishUpdate(picojson::object& returnValue, std::vector<picojson::object>& entityUpdates) {
  // Reset lowest_battery_level to high default value
  this->lowest_battery_level = 10000; // this way, notifications will still work if recharging's added
  

    // pop robot and to the end of entity 
    if (this->arrived_at_robot){
      if (this->robot != nullptr)
        this->entities.push_back(robot);
      this->entities.push_back(rescue_drone);
    }
    // Iterate over all entities that have been created in the simulation to check for updates
  for (int i = 0; i < entities.size(); i++) {

    // Create an empty JSON object for the entity 
    picojson::object entity;

    // Get the type of entity 
    entity["entityId"] = picojson::value((double)entities[i]->GetEntityId());
    
    // Get the position of the Entity
    picojson::array pos;
    Vector3 positionVector = entities[i]->GetPosition();
    pos.push_back(picojson::value(positionVector.GetX()));
    pos.push_back(picojson::value(positionVector.GetY()));
    pos.push_back(picojson::value(positionVector.GetZ()));
    entity["pos"] = picojson::value(pos);

    // Get the Direction of the Entity
    picojson::array dir;
    Vector3 directionVector = entities[i]->GetDirection();
    dir.push_back(picojson::value(directionVector.GetX()));
    dir.push_back(picojson::value(directionVector.GetY()));
    dir.push_back(picojson::value(directionVector.GetZ()));
    entity["dir"] = picojson::value(dir);

    // Send the updated picojson data to the UI in the returnValue variable
    // Only send the new JSON if the Entity is a drone - as we do not how to update json for more than one 
    if (this->rescue_drone_with_robot && entities[i]->GetType()=="robot" && this->update_val==1){
      this->update_val = 0;
      returnValue["entity"+std::to_string(entities[i]->GetEntityId())] = picojson::value(entity);

    }
    else if (this->arrived_at_robot && entities[i]->GetType() == "rescue drone" ){
      this->update_val =1;
      returnValue["entity"+std::to_string(entities[i]->GetEntityId())] = picojson::value(entity);
    }
    else if  (entities[i]->GetType() == "drone"){
      returnValue["entity"+std::to_string(entities[i]->GetEntityId())] = picojson::value(entity);
      
      // Find lowest battery level among drones
      BatteryDecorator* bat_drone = static_cast<BatteryDecorator*>(entities[i]);
      
      if (bat_drone->GetBatteryLevel() < this->lowest_battery_level){
      // in the future, maybe check if also > 0 so dead drones don't spam
        this->lowest_battery_level = bat_drone->GetBatteryLevel();
      }
    } // end of update drone 

    // Update all entities
    picojson::object ret;
    ret["id"] = picojson::value((double)entities[i]->GetId());
    ret["entity"+std::to_string(entities[i]->GetEntityId())] = picojson::value(entity);
    
    entityUpdates.push_back(ret);
  }
  
    // remove the last 2
    if (this->arrived_at_robot){
      if (this->robot != nullptr)
        this->entities.pop_back();
      this->entities.pop_back();
    }
  // Send low battery notification if lowest battery is low enough
  // note, thought notif would be more bool when this decision was made
  // it's a constantly updated bar, so "low enough" is very high
  if (this->lowest_battery_level < 1000.0) {
    //std::cout << lowest_battery_level << std::endl;
    picojson::object info;
    info["type"] = picojson::value("battery");
    info["data"] = picojson::value(this->lowest_battery_level);
    picojson::object o;
    o["notification"] = picojson::value(info);
    // maybe this method could also have a vector of notifications
    entityUpdates.push_back(o);
  }
}




// PROBLEM: depth img does not calculate with accuarcy the postion of the robot if found, so there is an edge case in which 
//            drone camera has found robot, but depth img calculation does not end up close to the robot to "create entity"
//            and thereby the rescue drone update leads to errors since if found and at the position we are assuming web app will create robot entity