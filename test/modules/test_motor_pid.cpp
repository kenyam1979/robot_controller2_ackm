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
// 2.1 It shall calculate manipulating variable based on target and current
// velocity
TEST_F(MotorPIDTest, 2_1_CalculateManipulatingVariable) {
  pid_->initialize();
  double target_velocity = 5.0;
  double current_velocity = 0.0;
  double dt = 0.1;

  int mv = pid_->calculateManipulatingVariable(target_velocity,
                                               current_velocity, dt);

  ASSERT_EQ(mv, MotorPIDSetting::MAX_MV);

  target_velocity = 5.0;
  current_velocity = 5.0;
  dt = 0.1;
  mv = pid_->calculateManipulatingVariable(target_velocity, current_velocity,
                                           dt);
  ASSERT_EQ(mv, -140);
}

// 2.2 It shall return negative manipulating variable when negative target
// velocity is set
TEST_F(MotorPIDTest, 2_2_CalculateNegativeManipulatingVariable) {
  pid_->initialize();
  double target_velocity = -5.0;
  double current_velocity = 0.0;
  double dt = 0.1;

  int mv = pid_->calculateManipulatingVariable(target_velocity,
                                               current_velocity, dt);
  ASSERT_EQ(mv, -MotorPIDSetting::MAX_MV);
}

// 2.3 It shall return error when dt is zero
TEST_F(MotorPIDTest, 2_3_CalculateManipulatingVariableWithZeroDt) {
  pid_->initialize();
  double target_velocity = 5.0;
  double current_velocity = 0.0;
  double dt = 0.1;
  int mv_prev = pid_->calculateManipulatingVariable(target_velocity,
                                                    current_velocity, dt);

  target_velocity = 5.0;
  current_velocity = 5.0;
  dt = 0.0;
  int mv = pid_->calculateManipulatingVariable(target_velocity,
                                               current_velocity, dt);

  ASSERT_EQ(mv, mv_prev);
}

// 3. Reset PID
// 3.1 It shall reset PID parameters to initial state
TEST_F(MotorPIDTest, 3_1_ResetPID) {
  pid_->initialize();
  ASSERT_EQ(pid_->reset(), MotorPIDReturnType::OK);
}

}  // namespace controller_tamiya_tt02
