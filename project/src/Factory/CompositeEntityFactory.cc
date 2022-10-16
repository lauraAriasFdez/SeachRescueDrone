/**
 * @file CompositeEntityFactory.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "CompositeEntityFactory.h"

/*******************************************************************************
* Class Definition
******************************************************************************/
void CompositeEntityFactory::operator= (const CompositeEntityFactory& objectToCopy){
    //delete all factories in this object
    for (int i=0;i<entityFactories.size();i++){
        delete entityFactories[i];
    }
    entityFactories.clear();

    // copy factories from the other object into this object
    for (int i=0;i<objectToCopy.entityFactories.size();i++){
        this->AddFactory(objectToCopy.entityFactories[i]);
    }
}


IEntity* CompositeEntityFactory::CreateEntity(picojson::object& object,ICameraController& cameraController){
    for (int i=0;i<entityFactories.size();i++){
        IEntity* val = entityFactories[i]->CreateEntity(object,cameraController);
        if (val!=nullptr)
            return val;
    }
    return nullptr;
}

void CompositeEntityFactory::AddFactory(EntityFactory* factory){
    entityFactories.push_back(factory);
}