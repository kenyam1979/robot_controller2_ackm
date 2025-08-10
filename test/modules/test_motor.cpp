// Test items in Motor class

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>

#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

class MotorTest : public ::testing::Test {
 protected:
  void SetUp() override { motor_ = std::make_shared<Motor>(); }

  void TearDown() override {}

  std::shared_ptr<Motor> motor_;
};


// 1. Initialization of the Motor class
// 1.1 It shall initialize motor driver
TEST_F(MotorTest, 1_1_InitializeMotor) {
  ASSERT_NE(motor_, nullptr);
  ASSERT_EQ(motor_->initialize(0, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// 1.2 It shall return error on motor driver initialization failure
TEST_F(MotorTest, 1_2_InitializeMotorDriverFailure) {
  // Simulate failure by passing invalid parameters
  ASSERT_EQ(motor_->initialize(0, 0x40, nullptr),
            MotorReturnType::DRIVER_ERROR);
  ASSERT_EQ(motor_->initialize(0, 0x00, "/dev/i2c-1"),
            MotorReturnType::DRIVER_ERROR);
}

// 1.3 It shall initiate at boundary values of servo number
TEST_F(MotorTest, 1_3_InitializeBoundaryServoNumber) {
  ASSERT_EQ(motor_->initialize(0, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
  ASSERT_EQ(motor_->initialize(15, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// 1.4 It shall return error at out-of-range servo number
TEST_F(MotorTest, 1_4_InitializeOutOfRangeServoNumber) {
  ASSERT_EQ(motor_->initialize(17, 0x40, "/dev/i2c-1"), MotorReturnType::ERROR);
}

// 1.5 It shall initialize multiple motors sharing the same driver
TEST_F(MotorTest, 1_5_InitializeMultipleMotors) {
  std::shared_ptr<Motor> motor2 = std::make_shared<Motor>();
  ASSERT_NE(motor2, nullptr);
  ASSERT_EQ(motor2->initialize(1, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// 2. Manipulating Variable Operations
// 2.1 It shall get manipulating variable from PID
TEST_F(MotorTest, 2_1_GetManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->getManipulatingVariable(), 0);
}

// 2.2 It shall set manipulating variable and update motor driver
TEST_F(MotorTest, 2_2_SetManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->setManipulatingVariable(100), MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), 100);
}

// 2.3 It shall return error code on set manipulating variable failure
// TEST_F(MotorTest, 2_3_SetManipulatingVariableFailure) {
//   motor_->initialize(0, 0x40, "/dev/i2c-1");
//   ASSERT_EQ(motor_->setManipulatingVariable(10000),
//             MotorReturnType::DRIVER_ERROR);
// }

// 2.4 It shall function at boundary values of manipulating vars
TEST_F(MotorTest, 2_4_BoundaryManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");

  ASSERT_EQ(motor_->setManipulatingVariable(MotorSetting::MAX_MV),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), MotorSetting::MAX_MV);

  ASSERT_EQ(motor_->setManipulatingVariable(-MotorSetting::MAX_MV),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), -MotorSetting::MAX_MV);
}

// 2.5 It shall process properly with out-of-range values of manipulating vars
TEST_F(MotorTest, 2_5_OutOfRangeManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");

  ASSERT_EQ(motor_->setManipulatingVariable(MotorSetting::MAX_MV + 100),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), MotorSetting::MAX_MV);
}

// 3. Stop Motor Operations
// 3.1 It shall reset (or stop) the motor
TEST_F(MotorTest, 3_1_StopMotor) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->stopMotor(), MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), 0);
}

// 3.1 It shall return error code on stop motor failure
TEST_F(MotorTest, 3_4_StopMotorFailure) {
  std::shared_ptr<Motor> uninitialized_motor = std::make_shared<Motor>();
  ASSERT_EQ(uninitialized_motor->stopMotor(),
            MotorReturnType::INITIALIZATION_ERROR);
}


}  // namespace controller_tamiya_tt02