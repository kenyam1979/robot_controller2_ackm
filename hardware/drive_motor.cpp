#include "robot_controller2_ackm/drive_motor.hpp"

namespace controller_tamiya_tt02 {

DriveMotor::DriveMotor() noexcept { rpm_ = 0.0; }

MotorReturnType DriveMotor::setRPM(double rpm) noexcept {
  if (rpm < 0.0 || rpm > 2000.0) {
    return MotorReturnType::ERROR;
  }

  rpm_ = rpm;
  int mv = static_cast<int>(9.5 * pow(2000.0 - rpm_, 1.0 / 3.0) + 250.0);
  return Motor::setManipulatingVariable(mv);
}

double DriveMotor::getRPM() const noexcept { return rpm_; }

MotorReturnType DriveMotor::setAngularVelocity(double avel) noexcept {
  double rpm = avel * 60.0 / (2.0 * M_PI);
  return setRPM(rpm);
}

double DriveMotor::getAngularVelocity() const noexcept {
  return rpm_ / 60.0 * (2.0 * M_PI);
}

MotorReturnType DriveMotor::stopMotor() noexcept {
  rpm_ = 0.0;
  return Motor::stopMotor();
}

DriveMotor::~DriveMotor() noexcept {}

}  // namespace controller_tamiya_tt02
