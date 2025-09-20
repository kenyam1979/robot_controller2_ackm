#ifndef ROBOT_CONTROLLER2_ACKM__STEER_MOTOR_HPP_
#define ROBOT_CONTROLLER2_ACKM__STEER_MOTOR_HPP_

#include <stdint.h>

#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

class SteerMotor : public Motor {
 public:
  SteerMotor() noexcept;
  MotorReturnType setAngle(double angle) noexcept;
  double getAngle() const noexcept;
  MotorReturnType setNeutral() noexcept;
  ~SteerMotor() noexcept;

 private:
  double angle_;
};

}  // namespace controller_tamiya_tt02

#endif  // ROBOT_CONTROLLER2_ACKM__STEER_MOTOR_HPP_