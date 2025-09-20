#ifndef ROBOT_CONTROLLER2_ACKM__DRIVE_MOTOR_HPP_
#define ROBOT_CONTROLLER2_ACKM__DRIVE_MOTOR_HPP_

#include <math.h>
#include <stdint.h>

#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

class DriveMotor : public Motor {
 public:
  DriveMotor() noexcept;
  MotorReturnType setRPM(double rpm) noexcept;
  double getRPM() const noexcept;
  MotorReturnType stopMotor() noexcept;
  ~DriveMotor() noexcept;

 private:
  double rpm_;
};

}  // namespace controller_tamiya_tt02

#endif  // ROBOT_CONTROLLER2_ACKM__DRIVE_MOTOR_HPP_