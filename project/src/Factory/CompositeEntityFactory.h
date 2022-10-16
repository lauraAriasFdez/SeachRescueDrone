/**
 * @file CompositeEntityFactory.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef COMPOSITE_ENTITY_FACTORY_H_
#define COMPOSITE_ENTITY_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "EntityFactory.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>

/*******************************************************************************
 * Class Definition
 ******************************************************************************/

class CompositeEntityFactory: public EntityFactory {
public:

    /**
    *
    *@brief Default Constructor
    * 
    */
    CompositeEntityFactory(){}


    // THE BIG 3 since we are using allocated memory 
    /**
    *
    *@brief Destructor deleating all factories
    * 
    */
    ~CompositeEntityFactory(){
        // std::cout << "destroying Factories in Composite Entity Factory" << std::endl;
        for (int i=0;i<entityFactories.size();i++){
            delete entityFactories[i];
        }
        entityFactories.clear();
    }

    /**
    *
    *@brief Copy Constructor
    *
    * @param[in] objectToCopy CompositeEntityFactory to copy 
    * 
    */
    CompositeEntityFactory(const CompositeEntityFactory& objectToCopy){
        *this = objectToCopy;
    }

    /**
    *
    *@brief equality overload operator
    *
    * @param[in] objectToCopy CompositeEntityFactory to copy 
    * 
    */
    void operator= (const CompositeEntityFactory& objectToCopy);

    // OTHER METHODS
    /**
    *
    *@brief calls factories and creates the enitity based on the picson object
    *
    * @param[in] object json object representing the entity that needs to be created
    * 
    * @return entity based on parameter/argument created 
    * 
    */
	IEntity* CreateEntity(picojson::object& object,ICameraController& cameraController);


    /**
    *
    *@brief EntityFactoryadded to the collection of factories in this object
    *
    * @param[in] factory object factory that needs to be added 
    * 
    */
    void AddFactory(EntityFactory* factory);

    

private:
    /**
    *
    *@brief vector containing pointers to factories
    * 
    */
    std::vector<EntityFactory*> entityFactories;
}; 

#endif 





/*  SIMULATION


// 1,2,3 IN CONSTRUCTOR
// 1- FACTORY
CompositeEntityFactory factories = CompositeEntityFactory();
factories.AddFactory(new DroneFactory());
factories.AddFactory(new RobotFactory());

//2- ENTITIES CREATION 
//creat json file representing drone, and another representing robot
// the battery decorator will take care of deleting the drone pointer
IEntity* drone = new BatteryDecorator(factories.CreateEntity(object));
IEntity* robot = factories.CreateEntity(object2);

//3 ADD OBSERVERS TO ENTITIES
// the enitity will take care of deleting the observers pointer
drone ->AddObserver(new WebObserver());
robot->AddObserver(new WebObserver());


// Simulation will have an update function just like drone
//4- MOVE DRONE UNTIL ROBOT FOUND
// please use the ChangeStatus() to change movement from patrol to Beeline
//dynamic cast if we want to use Update but with batteryDecorator
// if we want to use battery decorator use cast to IDrone rather than Drone itself
// battery will make sure Drone does not move any more if no more mattery 

IDrone* actualDrone   = dynamic_cast<IDrone*>(drone);
// make drone take picture and check to see if robot found
// if robot found change status of drone to beeline and update destination
actualDrone->Update(dt);


//5- END OF SIMULATION DELETE OBJECTS CREATED
    // compositeEntityFactory will take care of the Drone& Robot Factory delete
    // the battery decorator will take care of deleting the drone pointer
    // the enitity will take care of deleting the observers pointer
    delete drone;
    delete robot;
*/