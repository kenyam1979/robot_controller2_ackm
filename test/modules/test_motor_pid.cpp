// Test items in Motor class

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>

#include "robot_controller2_ackm/motor_pid.hpp"

namespace controller_tamiya_tt02 {

class MotorPIDTest : public ::testing::Test {
 protected:
  void SetUp() override { pid_ = std::make_shared<MotorPID>(); }

  void TearDown() override {}

  std::shared_ptr<MotorPID> pid_;
};

// 1. Initialization of the MotorPID class
// 1.1 It shall initialize motor PID
TEST_F(MotorPIDTest, 1_1_InitializeMotorPID) {
  ASSERT_NE(pid_, nullptr);
  ASSERT_EQ(pid_->initialize(), MotorPIDReturnType::OK);
}

// 2. Calculate Manipulating Variable
// 2.1 It shall calculate manipulating variable based on target and current velocity


// 3. Reset PID 


}  // namespace controller_tamiya_tt02
