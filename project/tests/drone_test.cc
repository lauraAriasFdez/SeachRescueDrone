/**
 * @file drone_test.cc
 *
 * @copyright 2021 Laura Arias Fernadez, Michael Weiner, and Malik Khadar. All rights reserved.
 */

#include "gtest/gtest.h"
#include "../src/Entity/Drone.h"
#include "../src/vector3.h"

class DroneTest : public ::testing::Test {
public:
  void SetUp( ) { 
    defDrone = new Drone();
    vecStop = Vector3(0, 0, 0);
    vecGo = Vector3(5, 0, 0);
  }

protected:
  Drone* defDrone; // drone created with default constructor
  Vector3 vecStop; // 0 vector
  Vector3 vecGo; // non-zero vector
};

// REGRESSION TESTS
TEST_F(DroneTest, PropellerSpeedTest) {
  EXPECT_DOUBLE_EQ(defDrone->GetPropellerSpeed(0), 1.0) << "Propeller speed is Incorrect";
}

TEST_F(DroneTest, JoystickTest) {
  defDrone->SetJoystick(1, 0, 0.5, 0);
  EXPECT_EQ(defDrone->GetDirection().GetZ(), 0.5) << "Direction updated Incorrectly";
}

TEST_F(DroneTest, SearchStatusTest) {
  defDrone->SetSearchStatus(true);
  EXPECT_EQ(defDrone->GetSearchStatus(), true) << "Search status was not set to true";

  defDrone->SetSearchStatus(false);
  EXPECT_EQ(defDrone->GetSearchStatus(), false) << "Search status was not set to false";
}

// INTEGRATION TESTS
TEST_F(DroneTest, UpdateVelocityTest) {
  defDrone->UpdateVelocity(vecGo);
  EXPECT_EQ(defDrone->GetVelocity().GetX(), vecGo.GetX()) << "Velocity was not updated correctly";

  defDrone->UpdateVelocity(vecStop);
  EXPECT_EQ(defDrone->GetVelocity().GetX(), vecStop.GetX()) << "Velocity was not updated correctly";
}

TEST_F(DroneTest, BasicMovementTest) {
  Vector3 start = defDrone->GetPosition();
  double dt = 1;

  // Check Start Position is accurate
  EXPECT_EQ(start.GetX(), 0.0) << "Drone is in the correct X-position before any movement";
  EXPECT_EQ(start.GetY(), 0.0) << "Drone is in the correct Y-position before any movement";
  EXPECT_EQ(start.GetZ(), 0.0) << "Drone is in the correct Z-position before any movement";

  // Move Drone in X-Direction
  defDrone->SetJoystick(1, 0, 0, 0);
  defDrone->UpdateVelocity(vecGo);
  defDrone->UpdateManualMovement(dt);
  Vector3 end = defDrone->GetPosition();

  EXPECT_NE(start.GetX(), end.GetX()) << "Drone did not move in the X-Direction";
  EXPECT_EQ((end - start).GetX(), 5.0) << "Drone moved to the incorrect X-position";

  // Move Drone in Y-Direction
  defDrone->SetJoystick(0, 1, 0, 0);
  Vector3 ySpeed = Vector3(0, 4, 0);
  defDrone->UpdateVelocity(ySpeed);
  defDrone->UpdateManualMovement(dt);
  end = defDrone->GetPosition();

  EXPECT_NE(start.GetY(), end.GetY()) << "Drone did not move in the Y-Direction";
  EXPECT_EQ((end - start).GetY(), 4.0) << "Drone moved to the incorrect Y-position";

  // Move Drone in Z-Direction
  defDrone->SetJoystick(0, 0, 1, 0);
  Vector3 zSpeed = Vector3(0, 0, 3);
  defDrone->UpdateVelocity(zSpeed);
  defDrone->UpdateManualMovement(dt);
  end = defDrone->GetPosition();

  EXPECT_NE(start.GetZ(), end.GetZ()) << "Drone did not move in the Z-Direction";
  EXPECT_EQ((end - start).GetZ(), 3.0) << "Drone moved to the incorrect Z-position";

  // Check Final Position is accurate
  EXPECT_EQ(end.GetX(), 5.0) << "Drone is in the correct X-position after all movement has concluded";
  EXPECT_EQ(end.GetY(), 4.0) << "Drone is in the correct Y-position after all movement has concluded";
  EXPECT_EQ(end.GetZ(), 3.0) << "Drone is in the correct Z-position after all movement has concluded";
}

TEST_F(DroneTest, AggregateMovementTest) {
  Vector3 start = defDrone->GetPosition();
  double dt = 1;

  // Check Start Position is accurate
  EXPECT_EQ(start.GetX(), 0.0) << "Drone is in the correct X-position before any movement";
  EXPECT_EQ(start.GetY(), 0.0) << "Drone is in the correct Y-position before any movement";
  EXPECT_EQ(start.GetZ(), 0.0) << "Drone is in the correct Z-position before any movement";

  // Move Drone in X, Y, and Z directions
  defDrone->SetJoystick(1, 1, 1, 0);
  Vector3 aggregateSpeed = Vector3(5, 4, 3);
  defDrone->UpdateVelocity(aggregateSpeed);
  defDrone->UpdateManualMovement(dt);
  Vector3 end = defDrone->GetPosition();

  // Check Final Position is accurate to within the nearest 0.0001
  EXPECT_NEAR(end.GetX(), sqrt(50), 0.0001) << "Drone is in the correct X-position after all movement has concluded";
  EXPECT_NEAR(end.GetY(), sqrt(50), 0.0001) << "Drone is in the correct Y-position after all movement has concluded";
  EXPECT_NEAR(end.GetZ(), sqrt(50), 0.0001) << "Drone is in the correct Z-position after all movement has concluded";
}