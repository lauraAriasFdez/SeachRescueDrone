/**
 * @file RescueSimulation_test.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/Simulation/RescueSimulation.h"
#include "../src/camera_controller.h"
#include "../src/vector3.h"
#include <picojson.h>

class MockCameraController : public ICameraController {
public:
  MOCK_METHOD(void, TakePicture, (int cameraId), ());
  MOCK_METHOD(void, AddObserver, (ICameraObserver& observer), ());
  MOCK_METHOD(void, RemoveObserver, (ICameraObserver& observer), ());
};

class RescueSimulationTest : public ::testing::Test {
public:
  void SetUp( ) {
    EXPECT_CALL(cameraController, TakePicture(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(cameraController, AddObserver(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(cameraController, RemoveObserver(::testing::_)).Times(::testing::AnyNumber());
    
    simulation = new RescueSimulation();
    
    // ********************
    // picoJSON Drone Entity Creation
    // ********************

    // Set Drone Entity ID Information
    droneEntity["entityId"] = picojson::value(15.0);
    droneEntity["id"] = picojson::value(16.0);
    droneEntity["name"] = picojson::value("drone");

    // Set Drone Entity Speed
    droneEntity["speed"] = picojson::value(13.24);
    
    // Set the position of the Drone Entity
    picojson::array dronePosition;
    Vector3 dronePositionVector = Vector3(1.1, 2.2, 3.3);
    dronePosition.push_back(picojson::value(dronePositionVector.GetX()));
    dronePosition.push_back(picojson::value(dronePositionVector.GetY()));
    dronePosition.push_back(picojson::value(dronePositionVector.GetZ()));
    droneEntity["position"] = picojson::value(dronePosition);

    // Set the Direction of the Drone Entity
    picojson::array droneDirection;
    Vector3 droneDirectionVector = Vector3(4.4, 5.5 , 6.6);
    droneDirection.push_back(picojson::value(droneDirectionVector.GetX()));
    droneDirection.push_back(picojson::value(droneDirectionVector.GetY()));
    droneDirection.push_back(picojson::value(droneDirectionVector.GetZ()));
    droneEntity["direction"] = picojson::value(droneDirection);

    // Set the Cameras of the Drone Entity
    picojson::array droneCameras;
    droneCameras.push_back(picojson::value(0.0));
    droneEntity["cameras"] = picojson::value(droneCameras);

	
    // Set Drone Entity Speed
    droneEntity["charge"] = picojson::value(200.0);

    // ********************
    // picoJSON Robot Entity Creation
    // ********************

    // Set Entity ID Information
    robotEntity["entityId"] = picojson::value(2.0);
    robotEntity["id"] = picojson::value(3.0);
    robotEntity["name"] = picojson::value("robot");
    
    // Set the position of the Robot Entity
    picojson::array robotPosition;
    Vector3 robotPositionVector = Vector3(1.1, 2.2, 3.3);
    robotPosition.push_back(picojson::value(robotPositionVector.GetX()));
    robotPosition.push_back(picojson::value(robotPositionVector.GetY()));
    robotPosition.push_back(picojson::value(robotPositionVector.GetZ()));
    robotEntity["position"] = picojson::value(robotPosition);

    // Set the Direction of the Robot Entity
    picojson::array robotDirection;
    Vector3 robotDirectionVector = Vector3(4.4, 5.5, 6.6);
    robotDirection.push_back(picojson::value(robotDirectionVector.GetX()));
    robotDirection.push_back(picojson::value(robotDirectionVector.GetY()));
    robotDirection.push_back(picojson::value(robotDirectionVector.GetZ()));
    robotEntity["direction"] = picojson::value(robotDirection);

    // Set the Cameras of the Robot Entity
    picojson::array robotCameras;
    robotCameras.push_back(picojson::value(0.0));
    robotEntity["cameras"] = picojson::value(robotCameras);

    // ********************
    // picoJSON RechargeStation Entity Creation
    // ********************

    // Set Entity ID Information
    rechargeStationEntity["entityId"] = picojson::value(3.0);
    rechargeStationEntity["id"] = picojson::value(4.0);
    rechargeStationEntity["name"] = picojson::value("recharge station");
    
    // Set the position of the RechargeStation Entity
    picojson::array rechargeStationPosition;
    Vector3 rechargeStationPositionVector = Vector3(7.7, 8.8, 9.9);
    rechargeStationPosition.push_back(picojson::value(rechargeStationPositionVector.GetX()));
    rechargeStationPosition.push_back(picojson::value(rechargeStationPositionVector.GetY()));
    rechargeStationPosition.push_back(picojson::value(rechargeStationPositionVector.GetZ()));
    rechargeStationEntity["position"] = picojson::value(rechargeStationPosition);

    // Set the Direction of the RechargeStation Entity
    picojson::array rechargeStationDirection;
    Vector3 rechargeStationDirectionVector = Vector3(10.10, 11.11, 12.12);
    rechargeStationDirection.push_back(picojson::value(rechargeStationDirectionVector.GetX()));
    rechargeStationDirection.push_back(picojson::value(rechargeStationDirectionVector.GetY()));
    rechargeStationDirection.push_back(picojson::value(rechargeStationDirectionVector.GetZ()));
    rechargeStationEntity["direction"] = picojson::value(rechargeStationDirection);

    // Set the Cameras of the RechargeStation Entity
    picojson::array rechargeStationCameras;
    rechargeStationCameras.push_back(picojson::value(0.0));
    rechargeStationEntity["cameras"] = picojson::value(rechargeStationCameras);

    // ********************
    // picoJSON Hospital Entity Creation
    // ********************

    // Set Entity ID Information
    hospitalEntity["entityId"] = picojson::value(4.0);
    hospitalEntity["id"] = picojson::value(5.0);
    hospitalEntity["name"] = picojson::value("hospital");
    
    // Set the position of the Hospital Entity
    picojson::array hospitalPosition;
    Vector3 hospitalPositionVector = Vector3(13.13, 14.14, 15.15);
    hospitalPosition.push_back(picojson::value(hospitalPositionVector.GetX()));
    hospitalPosition.push_back(picojson::value(hospitalPositionVector.GetY()));
    hospitalPosition.push_back(picojson::value(hospitalPositionVector.GetZ()));
    hospitalEntity["position"] = picojson::value(hospitalPosition);

    // Set the Direction of the Hospital Entity
    picojson::array hospitalDirection;
    Vector3 hospitalDirectionVector = Vector3(16.16, 17.17, 18.18);
    hospitalDirection.push_back(picojson::value(hospitalDirectionVector.GetX()));
    hospitalDirection.push_back(picojson::value(hospitalDirectionVector.GetY()));
    hospitalDirection.push_back(picojson::value(hospitalDirectionVector.GetZ()));
    hospitalEntity["direction"] = picojson::value(hospitalDirection);

    // Set the Cameras of the RechargeStation Entity
    picojson::array hospitalCameras;
    hospitalCameras.push_back(picojson::value(0.0));
    hospitalEntity["cameras"] = picojson::value(hospitalCameras);
  }

protected:
  // Declare picoJSON objects needed for component testing
  picojson::object droneEntity;
  picojson::object robotEntity;
  picojson::object rechargeStationEntity;
  picojson::object hospitalEntity;
  
  MockCameraController cameraController;
  RescueSimulation* simulation;
};

// ********************
// Component Tests
// ********************

TEST_F(RescueSimulationTest, movementModeTest) {
	bool manMov = simulation->GetManualMov();
	simulation->SetManualMov();
	EXPECT_FALSE(simulation->GetManualMov() == manMov) << "Manual movement was not changed correctly";
	simulation->SetManualMov();
	EXPECT_TRUE(simulation->GetManualMov() == manMov) << "Manual movement was not rechanged correctly";
}

TEST_F(RescueSimulationTest, entityCreationTest) {
	EXPECT_EQ(simulation->GetNumberOfEntities(), 0) << "Non-zero number of entities detected after initialization";
	
	IEntity* Drone = simulation->CreateEntity(droneEntity, cameraController);
	IEntity* Robot = simulation->CreateEntity(robotEntity, cameraController);
	IEntity* RechargeStation = simulation->CreateEntity(rechargeStationEntity, cameraController);
	IEntity* Hospital = simulation->CreateEntity(hospitalEntity, cameraController);

	EXPECT_TRUE(Drone != nullptr) << "Drone was not created successfully";
	EXPECT_TRUE(Robot != nullptr) << "Robot was not created successfully";
	EXPECT_TRUE(RechargeStation != nullptr) << "Recharge station was not created successfully";
	EXPECT_TRUE(Hospital != nullptr) << "Hospital was not created successfully";
	
	// expect 3 because Robot is not immediately put into entity list
	EXPECT_EQ(simulation->GetNumberOfEntities(), 3) << "Incorrect number of entities created";
	
	simulation->CreateEntity(droneEntity, cameraController);
	simulation->CreateEntity(robotEntity, cameraController);
	simulation->CreateEntity(rechargeStationEntity, cameraController);
	simulation->CreateEntity(hospitalEntity, cameraController);
	
	EXPECT_EQ(simulation->GetNumberOfEntities(), 6) << "Duplicate entities not accounted for";
	
	simulation->Update(0.1);
	EXPECT_EQ(simulation->GetNumberOfEntities(), 6) << "Num entities changed after Update";
	
	simulation->UpdateManualMovement(0.1, 0, 0, 0, 0);
	EXPECT_EQ(simulation->GetNumberOfEntities(), 6) << "Num entities changed after UpdateManualMovement";
}
