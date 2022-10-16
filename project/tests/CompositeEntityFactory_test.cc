/**
 * @file CompositeEntityFactory_test.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/camera_controller.h"
#include "../src/Factory/CompositeEntityFactory.h"
#include "../src/Factory/EntityFactory.h"
#include "../src/Factory/DroneFactory.h"
#include "../src/Factory/RobotFactory.h"
#include "../src/Factory/RechargeStationFactory.h"
#include "../src/Factory/HospitalFactory.h"
#include "../src/vector3.h"
#include <picojson.h>

class MockCameraController : public ICameraController {
public:
  MOCK_METHOD(void, TakePicture, (int cameraId), ());
  MOCK_METHOD(void, AddObserver, (ICameraObserver& observer), ());
  MOCK_METHOD(void, RemoveObserver, (ICameraObserver& observer), ());
};

class CompositeEntityFactoryTest : public ::testing::Test {
public:
  void SetUp( ) { 
    EXPECT_CALL(cameraController, TakePicture(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(cameraController, AddObserver(::testing::_)).Times(::testing::AnyNumber());
    EXPECT_CALL(cameraController, RemoveObserver(::testing::_)).Times(::testing::AnyNumber());

    compositeFactory = CompositeEntityFactory();
    droneFactory = new DroneFactory();
    robotFactory = new RobotFactory();
    rechargeStationFactory = new RechargeStationFactory();
    hospitalFactory = new HospitalFactory();

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
  // Declare Factories needed for the integration and regression testing
  CompositeEntityFactory compositeFactory;
  EntityFactory* droneFactory;
  EntityFactory* robotFactory;
  EntityFactory* rechargeStationFactory;
  EntityFactory* hospitalFactory;

  MockCameraController cameraController;

  // Declare picoJSON objects needed for integration and regression testing
  picojson::object droneEntity;
  picojson::object robotEntity;
  picojson::object rechargeStationEntity;
  picojson::object hospitalEntity;
};

// ********************
// Integration Tests with CompositeFactory class and Drone, Robot, Hospital, and RechargeStation Factory classes
// ********************

TEST_F(CompositeEntityFactoryTest, DroneCreationTest) {
  // Create DroneFactory and Test Creation of a Drone
  compositeFactory.AddFactory(droneFactory);
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IDrone* tmpDrone = dynamic_cast<IDrone*>(testDrone);

  EXPECT_TRUE(tmpDrone != nullptr) << "tmpDrone is NULL, so DroneFactory could not detect JSON was for a Drone";
  EXPECT_TRUE(tmpDrone->GetEntityId() == 15) << "tmpDrone entity_id is not being set to the correct value";
  EXPECT_TRUE(tmpDrone->GetId() == 16) << "tmpDrone id is not being set to the correct value";
  
  EXPECT_TRUE(tmpDrone->GetType() == "drone") << "tmpDrone type is not being set to the correct value";
  EXPECT_TRUE(tmpDrone->GetSearchStatus() == false) << "tmpDrone search is not set to false upon creation";

  EXPECT_TRUE(tmpDrone->GetPosition().GetX() == 1.1) << "tmpDrone x-component position is incorrect";
  EXPECT_TRUE(tmpDrone->GetPosition().GetY() == 2.2) << "tmpDrone y-component position is incorrect";
  EXPECT_TRUE(tmpDrone->GetPosition().GetZ() == 3.3) << "tmpDrone z-component position is incorrect";

  EXPECT_TRUE(tmpDrone->GetDirection().GetX() == 4.4) << "tmpDrone x-component position is incorrect";
  EXPECT_TRUE(tmpDrone->GetDirection().GetY() == 5.5) << "tmpDrone y-component position is incorrect";
  EXPECT_TRUE(tmpDrone->GetDirection().GetZ() == 6.6) << "tmpDrone z-component position is incorrect";

  EXPECT_TRUE(tmpDrone->GetVelocity().GetX() == 13.24) << "tmpDrone x-component velocity is incorrect";
  EXPECT_TRUE(tmpDrone->GetVelocity().GetY() == 0) << "tmpDrone y-component velocity is incorrect";
  EXPECT_TRUE(tmpDrone->GetVelocity().GetZ() == 0) << "tmpDrone z-component velocity is incorrect";

  EXPECT_TRUE(tmpDrone->GetCamera(0) != nullptr) << "tmpDrone does not have the camera it has been assigned";
}

TEST_F(CompositeEntityFactoryTest, RobotCreationTest) {
  // Create RobotFactory and Test Creation of a Robot Entity
  compositeFactory.AddFactory(robotFactory);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  Robot* tmpRobot = dynamic_cast<Robot*>(testRobot);

  EXPECT_TRUE(tmpRobot != nullptr) << "tmpRobot is NULL, so RobotFactory could not detect JSON was for a Robot";
  EXPECT_TRUE(tmpRobot->GetEntityId() == 2.0) << "tmpRobot entity_id is not being set to the correct value";
  EXPECT_TRUE(tmpRobot->GetId() == 3.0) << "tmpRobot id is not being set to the correct value";
  
  EXPECT_TRUE(tmpRobot->GetType() == "robot") << "tmpRobot type is not being set to the correct value";
  EXPECT_TRUE(tmpRobot->GetIsRescued() == false) << "tmpRobot rescued boolean flag is not set to false upon creation";
    
  EXPECT_TRUE(tmpRobot->GetPosition().GetX() == 1.1) << "tmpRobot x-component position is incorrect";
  EXPECT_TRUE(tmpRobot->GetPosition().GetY() == 2.2) << "tmpRobot y-component position is incorrect";
  EXPECT_TRUE(tmpRobot->GetPosition().GetZ() == 3.3) << "tmpRobot z-component position is incorrect";

  EXPECT_TRUE(tmpRobot->GetDirection().GetX() == 4.4) << "tmpRobot x-component direction is incorrect";
  EXPECT_TRUE(tmpRobot->GetDirection().GetY() == 5.5) << "tmpRobot y-component direction is incorrect";
  EXPECT_TRUE(tmpRobot->GetDirection().GetZ() == 6.6) << "tmpRobot z-component direction is incorrect";

  EXPECT_FALSE(tmpRobot->GetCamera(0) != nullptr) << "tmpRobot does not have the camera it has been assigned";
}

TEST_F(CompositeEntityFactoryTest, RechargeStationCreationTest) {
  // Create RechargeStationFactory and Test Creation of a RechargeStation Entity
  compositeFactory.AddFactory(rechargeStationFactory);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  RechargeStation* tmpRechargeStation = dynamic_cast<RechargeStation*>(testRechargeStation);

  EXPECT_TRUE(tmpRechargeStation != nullptr) << "tmpRechargeStation is NULL, so RobotFactory could not detect JSON was for a Robot";
  EXPECT_TRUE(tmpRechargeStation->GetEntityId() == 3.0) << "tmpRechargeStation entity_id is not being set to the correct value";
  EXPECT_TRUE(tmpRechargeStation->GetId() == 4.0) << "tmpRechargeStation id is not being set to the correct value";
  
  EXPECT_TRUE(tmpRechargeStation->GetType() == "recharge station") << "tmpRechargeStation type is not being set to the correct value";
    
  EXPECT_TRUE(tmpRechargeStation->GetPosition().GetX() == 7.7) << "tmpRechargeStation x-component position is incorrect";
  EXPECT_TRUE(tmpRechargeStation->GetPosition().GetY() == 8.8) << "tmpRechargeStation y-component position is incorrect";
  EXPECT_TRUE(tmpRechargeStation->GetPosition().GetZ() == 9.9) << "tmpRechargeStation z-component position is incorrect";

  EXPECT_TRUE(tmpRechargeStation->GetDirection().GetX() == 10.10) << "tmpRechargeStation x-component direction is incorrect";
  EXPECT_TRUE(tmpRechargeStation->GetDirection().GetY() == 11.11) << "tmpRechargeStation y-component direction is incorrect";
  EXPECT_TRUE(tmpRechargeStation->GetDirection().GetZ() == 12.12) << "tmpRechargeStation z-component direction is incorrect";

  EXPECT_FALSE(tmpRechargeStation->GetCamera(0) != nullptr) << "tmpRechargeStation does not have the camera it has been assigned";
}

TEST_F(CompositeEntityFactoryTest, HospitalCreationTest) {
  // Create HospitalFactor and Test Creation of a Hospital Entity
  compositeFactory.AddFactory(hospitalFactory);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);
  Hospital* tmpHospital = dynamic_cast<Hospital*>(testHospital);

  EXPECT_TRUE(tmpHospital != nullptr) << "tmpHospital is NULL, so RobotFactory could not detect JSON was for a Robot";
  EXPECT_TRUE(tmpHospital->GetEntityId() == 4.0) << "tmpHospital entity_id is not being set to the correct value";
  EXPECT_TRUE(tmpHospital->GetId() == 5.0) << "tmpHospital id is not being set to the correct value";
  
  EXPECT_TRUE(tmpHospital->GetType() == "hospital") << "tmpHospital type is not being set to the correct value";
    
  EXPECT_TRUE(tmpHospital->GetPosition().GetX() == 13.13) << "tmpHospital x-component position is incorrect";
  EXPECT_TRUE(tmpHospital->GetPosition().GetY() == 14.14) << "tmpHospital y-component position is incorrect";
  EXPECT_TRUE(tmpHospital->GetPosition().GetZ() == 15.15) << "tmpHospital z-component position is incorrect";

  EXPECT_TRUE(tmpHospital->GetDirection().GetX() == 16.16) << "tmpHospital x-component direction is incorrect";
  EXPECT_TRUE(tmpHospital->GetDirection().GetY() == 17.17) << "tmpHospital y-component direction is incorrect";
  EXPECT_TRUE(tmpHospital->GetDirection().GetZ() == 18.18) << "tmpHospital z-component direction is incorrect";

  EXPECT_FALSE(tmpHospital->GetCamera(0) != nullptr) << "tmpHospital does not have the camera it has been assigned";
}

// // ********************
// // Regression Tests ensuring that the CompositeFactory, DroneFactory, RobotFactory, HospitalFactory, and RechargeStationFactory only create the appropriate entities
// // ********************

TEST_F(CompositeEntityFactoryTest, EmptyCompositeFactoryCreatesNoEntities) {
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);

  EXPECT_TRUE(testDrone == nullptr) << "testDrone is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRobot == nullptr) << "testRobot is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRechargeStation == nullptr) << "testRechargeStation is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testHospital == nullptr) << "testHospital is not NULL, so an Entity was created when it should not have been";
}

TEST_F(CompositeEntityFactoryTest, CompositeFactoryWithOnlyDroneFactoryCreatesOnlyDroneEntity) {
  compositeFactory.AddFactory(droneFactory);
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);

  EXPECT_TRUE(testDrone != nullptr) << "testDrone is NULL, so an Entity was not created when it should have been";
  EXPECT_TRUE(testRobot == nullptr) << "testRobot is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRechargeStation == nullptr) << "testRechargeStation is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testHospital == nullptr) << "testHospital is not NULL, so an Entity was created when it should not have been";
}

TEST_F(CompositeEntityFactoryTest, CompositeFactoryWithOnlyRobotFactoryCreatesOnlyRobotEntity) {
  compositeFactory.AddFactory(robotFactory);
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);

  EXPECT_TRUE(testDrone == nullptr) << "testDrone is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRobot != nullptr) << "testRobot is not NULL, so an Entity was not created when it should have been";
  EXPECT_TRUE(testRechargeStation == nullptr) << "testRechargeStation is not NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testHospital == nullptr) << "testHospital is not NULL, so an Entity was created when it should not have been";
}

TEST_F(CompositeEntityFactoryTest, CompositeFactoryWithOnlyRechargeStationFactoryCreatesOnlyRechargeStationEntity) {
  compositeFactory.AddFactory(rechargeStationFactory);
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);

  EXPECT_TRUE(testDrone == nullptr) << "testDrone is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRobot == nullptr) << "testRobot is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRechargeStation != nullptr) << "testRechargeStation is NULL, so an Entity was not created when it should have been";
  EXPECT_TRUE(testHospital == nullptr) << "testHospital is not NULL, so an Entity was created when it should not have been";
}

TEST_F(CompositeEntityFactoryTest, CompositeFactoryWithOnlyHospitalFactoryCreatesOnlyHospitalEntity) {
  compositeFactory.AddFactory(hospitalFactory);
  IEntity* testDrone = compositeFactory.CreateEntity(droneEntity, cameraController);
  IEntity* testRobot = compositeFactory.CreateEntity(robotEntity, cameraController);
  IEntity* testRechargeStation = compositeFactory.CreateEntity(rechargeStationEntity, cameraController);
  IEntity* testHospital = compositeFactory.CreateEntity(hospitalEntity, cameraController);

  EXPECT_TRUE(testDrone == nullptr) << "testDrone is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRobot == nullptr) << "testRobot is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testRechargeStation == nullptr) << "testRechargeStation is NULL, so an Entity was created when it should not have been";
  EXPECT_TRUE(testHospital != nullptr) << "testHospital is NULL, so an Entity was not created when it should have been";
}
