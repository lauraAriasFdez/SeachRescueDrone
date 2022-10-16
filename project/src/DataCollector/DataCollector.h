/**
 * @file DataCollector.h
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#ifndef DATACOLLECTOR_H_
#define DATACOLLECTOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
 * @brief A singleton class that collects and writes data to a CSV file.
 */
class DataCollector {
public:

  /**
    * @brief A static function that returns a reference to the single instance of the DataCollector class
    * 
    * @return Returns a reference to the singel instace of the DataCollector class.
    */
  static DataCollector& GetInstance();

  /**
    * @brief A function that takes in a message to write to the CSV file and a flag to control if the contents of the file are overwritten.
    * 
    * @param[in] msg A constant reference to a string containing the comma separated values to write to the CSV file
    * @param[in] overwrite A boolean flag that determines if the contents of the CSV file should be overwritten before writing the new msg.
    */  
  void Log(const std::string& msg, bool overwrite);

  /**
    * @brief Delete copy constructor to keep DataCollector as a Singleton.
    */ 
  DataCollector(const DataCollector&) = delete;

  /**
    * @brief Delete assignment operator to keep DataCollector as a Singleton.
    */ 
  void operator=(const DataCollector&) = delete;

private:
  /**
    * @brief A private constructor for the DataCollector class to prevent the creation of multiple instances of the class.Data
    */
  DataCollector() {
  }

};

#endif