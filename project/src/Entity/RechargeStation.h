/**
 * @file RechargeStation.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Entity.h"
#include <string>

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
class RechargeStation:public Entity {

public:

    /**
    *
    *@brief Constructors
    * 
    */
    RechargeStation(){}

    /**
    * @brief Constructor
    * 
    * @param[in] object picson object Object that we want to retrive info from 
    */
    RechargeStation(picojson::object& obj):Entity(obj){}

};



#endif