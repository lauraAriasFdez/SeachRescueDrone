/**
 * @file DataCollector.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DataCollector.h"

// Static method to return the single instance of DataCollector class
DataCollector& DataCollector::GetInstance() {
  static DataCollector instance;
  return instance;
}

void DataCollector::Log(const std::string& msg, bool overwrite) {
  if (overwrite) { // Truncate file and then write msg to file
    std::ofstream dataFile("build/statistics.csv", std::fstream::in | std::fstream::out | std::fstream::trunc);
    dataFile << msg << std::endl;
    dataFile.close();
  } else { // Append msg to file
    std::ofstream dataFile("build/statistics.csv", std::fstream::in | std::fstream::out | std::fstream::app);
    dataFile << msg << std::endl;
    dataFile.close();
  }
}