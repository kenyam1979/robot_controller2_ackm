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

////////////////////////////////////////////////////////////////////////////////////
// Test cases for the Motor class

// x. It shall initialize motor driver
TEST_F(MotorTest, InitializeMotor) {
  ASSERT_NE(motor_, nullptr);
  ASSERT_EQ(motor_->initialize(0, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// x. It shall return error on motor driver initialization failure
TEST_F(MotorTest, InitializeMotorDriverFailure) {
  // Simulate failure by passing invalid parameters
  ASSERT_EQ(motor_->initialize(0, 0x40, nullptr),
            MotorReturnType::DRIVER_ERROR);
  ASSERT_EQ(motor_->initialize(0, 0x00, "/dev/i2c-1"),
            MotorReturnType::DRIVER_ERROR);
}

// x. It shall initiate at boundary values of servo number
TEST_F(MotorTest, InitializeBoundaryServoNumber) {
  ASSERT_EQ(motor_->initialize(0, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
  ASSERT_EQ(motor_->initialize(15, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// x. It shall return error at out-of-range servo number
TEST_F(MotorTest, InitializeOutOfRangeServoNumber) {
  ASSERT_EQ(motor_->initialize(17, 0x40, "/dev/i2c-1"), MotorReturnType::ERROR);
}

// x. It shall initialize multiple motors sharing the same driver
TEST_F(MotorTest, InitializeMultipleMotors) {
  std::shared_ptr<Motor> motor2 = std::make_shared<Motor>();
  ASSERT_NE(motor2, nullptr);
  ASSERT_EQ(motor2->initialize(1, 0x40, "/dev/i2c-1"), MotorReturnType::OK);
}

// x. It shall get manipulating variable from PID
TEST_F(MotorTest, GetManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->getManipulatingVariable(), 0);
}

// x. It shall set manipulating variable and update motor driver
TEST_F(MotorTest, SetManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->setManipulatingVariable(100), MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), 100);
}

// x. It shall return error code on set manipulating variable failure
TEST_F(MotorTest, SetManipulatingVariableFailure) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->setManipulatingVariable(10000),
            MotorReturnType::DRIVER_ERROR);
}

// x. It shall reset (or stop) the motor
TEST_F(MotorTest, StopMotor) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");
  ASSERT_EQ(motor_->stopMotor(), MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), 0);
}

// x. It shall return error code on stop motor failure
TEST_F(MotorTest, StopMotorFailure) {
  std::shared_ptr<Motor> uninitialized_motor = std::make_shared<Motor>();
  ASSERT_EQ(uninitialized_motor->stopMotor(),
            MotorReturnType::INITIALIZATION_ERROR);
}

// x. It shall function at boundary values of manipulating vars
TEST_F(MotorTest, BoundaryManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");

  ASSERT_EQ(motor_->setManipulatingVariable(MotorSetting::MAX_MV),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), MotorSetting::MAX_MV);

  ASSERT_EQ(motor_->setManipulatingVariable(-MotorSetting::MAX_MV),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), -MotorSetting::MAX_MV);
}

// x. It shall process properly with out-of-range values of manipulating vars
TEST_F(MotorTest, OutOfRangeManipulatingVariable) {
  motor_->initialize(0, 0x40, "/dev/i2c-1");

  ASSERT_EQ(motor_->setManipulatingVariable(MotorSetting::MAX_MV + 100),
            MotorReturnType::OK);
  ASSERT_EQ(motor_->getManipulatingVariable(), MotorSetting::MAX_MV);
}

}  // namespace controller_tamiya_tt02