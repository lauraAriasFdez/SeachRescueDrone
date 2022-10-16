/**
 * @file RescueSimulation.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef RESCUE_SIMULATION_H_
#define RESCUE_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../vector3.h"
#include <vector>

#include "../DataCollector/DataCollector.h"

#include "../Entity/IEntity.h"
#include "../Entity/IDrone.h"
#include "../Entity/Robot.h"
#include "../Entity/Drone.h"

#include "../Decorator/BatteryDecorator.h"

#include "../Factory/DroneFactory.h"
#include "../Factory/CompositeEntityFactory.h"
#include "../Factory/HospitalFactory.h"
#include "../Factory/RobotFactory.h"
#include "../Factory/RechargeStationFactory.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A facade to start, interact, and end a rescue simulation.
 */
class RescueSimulation{
public:
    /**
     * @brief A constructor for an instance of the RescueSimulation class.
     */
    RescueSimulation();

    /**
     * @brief A destructor for an instance of the RescueSimulation class.
     */
    ~RescueSimulation();

    /**
     * @brief A method to create an entity within the rescue simulation.
     * 
     * @param[in] object A reference to an instance of a picojson::object containing the JSON for an Entity
     * @param[in] cameraController A reference to an instance of a class implementing ICameraController to be able to capture images
     *
     * @return IEntity* Returns a pointer to an IEntity if an entity was created, or a nullptr in all other situations. 
     */
	IEntity* CreateEntity(picojson::object& object, ICameraController& cameraController);

    /**
     * @brief A method to update the automatic movement of Entities within the simulation.
     * 
     * @param[in] dt A float containing the change in time since the last update
     */
    void Update(float dt);

    /**
     * @brief A method to update the automatic movement of Entities within the simulation.
     * 
     * @param[in] dt A float containing the change in time since the last update
     * @param[in] x A double containing the new x-coordinate position of the Entity
     * @param[in] y A double containing the new y-coordinate position of the Entity
     * @param[in] z A double containing the new z-coordinate position of the Entity
     * @param[in] rot A double containing the new rotation position of the Entity
     */
    void UpdateManualMovement(float dt, double x, double y, double z, double rot);

    /**
     * @brief A method that returns the number of Entities that are apart of the rescue simulation.
     * 
     * @return int Returns an integer containing how many entities are present in the simulation. 
     */
    int GetNumberOfEntities();

    /**
     * @brief A method that returns the value of the boolean flag tracking if manual movement is being used in the simulation.
     * 
     * @return boolean Returns the value of the boolean flag tracking if manual movement is being used in the simulation.
     */
    bool  GetManualMov();
    
    /**
     * @brief A method that enables manual movement for moveable entities in the simulation.
     */
    void  SetManualMov();
    
    /**
     * @brief A method that returns the lowest battery level of all the drones in the simulation.
     *
     * @return double Returns the lowest battery level of all the drones in the simulation.
     */
    double GetLowestBatteryLevel();

    /**
     * @brief A method to call after updating the simulation to pass the updates via JSON to the visual simulation that the user intreacts with.
     * 
     * @param[in] returnValue A reference to an instance of a picojson::object containing the updated JSON for an Entity
     * @param[in] entityUpdates A reference to a vector containing a list of picojson::object values containing the updates for the Entities in JSON format
     */
    void FinishUpdate(picojson::object& returnValue, std::vector<picojson::object>& entityUpdates);

private:
    /**
     * @brief A CompositeEntityFactory to track all of the EntityFactories available in the simulation.
     */
    CompositeEntityFactory factories;

    /**
     * @brief A vector containing pointers to all of the entities available within the simulation.
     */
    std::vector<IEntity*> entities;

    /**
     * @brief A boolean tracking if manual movement is being used to move the moveable entities.
     */
    bool manual_mov;

    /**
     * @brief A a boolean tracking if the Drone's locations to visit will need to be reestablished during the next switch back to automatic movement.
     */
    bool reset_drone_mov;

    /**
     * @brief A double equal to the lowest battery level of all the entities in the simulation.
     */
    double lowest_battery_level;

    /**
     * @brief A bool representing if rescue drone in progress, robot found and drone where robot is
     */
    bool arrived_at_robot;
    bool rescue_drone_with_robot;
    Vector3 robotPos;
    Robot* robot;
    Drone* rescue_drone;
    Vector3 hospitalPos;
    int update_val;
};
#endif