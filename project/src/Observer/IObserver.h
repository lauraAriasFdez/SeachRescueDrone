/**
 * @file IObserver.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef IOBSERVER_H_
#define IOBSERVER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <picojson.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class IObserver {
    
public:
    virtual void OnEvent(const picojson::value& notification) = 0;
};

#endif