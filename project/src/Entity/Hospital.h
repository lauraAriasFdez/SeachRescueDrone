/**
 * @file Hospital.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef HOSPITAL_H_
#define HOSPITAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Entity.h"
#include <string>

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class Hospital:public Entity {

public:
    /**
    * @brief Default constructor accepting no parameters.
    */
    Hospital(){}

    /**
    * @brief Constructor
    * 
    * @param[in] object picson object Object that we want to retrive info from 
    */
    Hospital(picojson::object& obj):Entity(obj){}

};



#endif