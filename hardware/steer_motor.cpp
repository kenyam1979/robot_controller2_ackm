#include "robot_controller2_ackm/steer_motor.hpp"

namespace controller_tamiya_tt02 {

SteerMotor::SteerMotor() noexcept { angle_ = 0.0; }

MotorReturnType SteerMotor::setAngle(double angle) noexcept {
  if (angle < -M_PI / 6.0 || angle > M_PI / 6.0) {
    return MotorReturnType::ERROR;
  }

  angle_ = angle;
  int mv = static_cast<int>(380.0 + angle_ * (6 / M_PI) * 60.0);
  return Motor::setManipulatingVariable(mv);
}

double SteerMotor::getAngle() const noexcept { return angle_; }

MotorReturnType SteerMotor::setNeutral() noexcept {
  return setAngle(0.0);
}

SteerMotor::~SteerMotor() noexcept {}

}  // namespace controller_tamiya_tt02
