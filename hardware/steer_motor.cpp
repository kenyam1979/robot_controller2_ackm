#include "robot_controller2_ackm/steer_motor.hpp"

namespace controller_tamiya_tt02 {

SteeringMotor::SteeringMotor() noexcept { angle_ = 0.0; }

MotorReturnType SteeringMotor::setAngle(double angle) noexcept {
  if (angle < -M_PI / 6.0) {
    angle = -M_PI / 6.0;
  }
  if (angle > M_PI / 6.0) {
    angle = M_PI / 6.0;
    // return MotorReturnType::ERROR;
  }

  angle_ = angle;
  int mv = static_cast<int>(380.0 - 2.0 * angle_ * 180.0 / M_PI);
  return Motor::setManipulatingVariable(mv);
}

double SteeringMotor::getAngle() const noexcept { return angle_; }

MotorReturnType SteeringMotor::setNeutral() noexcept { return setAngle(0.0); }

SteeringMotor::~SteeringMotor() noexcept {}

}  // namespace controller_tamiya_tt02
