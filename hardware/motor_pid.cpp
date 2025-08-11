#include "robot_controller2_ackm/motor_pid.hpp"

namespace controller_tamiya_tt02 {

MotorPID::MotorPID() noexcept {}

MotorPIDReturnType MotorPID::initialize() noexcept {
  // Nothing to initialize
  return MotorPIDReturnType::OK;
}

int MotorPID::calculateManipulatingVariable(double target_v, double current_v,
                                            double dt) noexcept {
  if (dt <= 0.0) {
    return mv_;  // return previous mv_
  }

  // Calculate PID errors
  error_P_ = target_v - current_v;
  error_I_ += error_P_ * dt;
  error_D_ = (error_P_ - error_P_prev_) / dt;

  // Calculate manipulating variable
  mv_ = static_cast<int>(kMvCoef *
                         (kKp * error_P_ + kKi * error_I_ + kKd * error_D_));

  // Limit mv to MAX_MV
  if (mv_ > MotorPIDSetting::MAX_MV) {
    mv_ = MotorPIDSetting::MAX_MV;
  } else if (mv_ < -MotorPIDSetting::MAX_MV) {
    mv_ = -MotorPIDSetting::MAX_MV;
  }

  // Update previous error
  error_P_prev_ = error_P_;

  return mv_;
}

MotorPIDReturnType MotorPID::reset() noexcept {
  // Reset PID parameters to initial state
  error_P_ = 0.0;
  error_P_prev_ = 0.0;
  error_I_ = 0.0;
  error_D_ = 0.0;

  target_velocity_ = 0.0;
  current_velocity_ = 0.0;
  mv_ = 0;

  return MotorPIDReturnType::OK;
}

MotorPID::~MotorPID() noexcept {}

}  // namespace controller_tamiya_tt02