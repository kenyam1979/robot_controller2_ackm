#ifndef ROBOT_CONTROLLER2_ACKM__STEERING_MOTOR_HPP_
#define ROBOT_CONTROLLER2_ACKM__STEERING_MOTOR_HPP_

#include <stdint.h>

#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

class SteeringMotor : public Motor {
 public:
  SteeringMotor() noexcept;
  MotorReturnType setAngle(double angle) noexcept;  // angle in radians
  double getAngle() const noexcept;
  MotorReturnType setNeutral() noexcept;
  ~SteeringMotor() noexcept;

 private:
  double angle_;
};

}  // namespace controller_tamiya_tt02

#endif  // ROBOT_CONTROLLER2_ACKM__STEERING_MOTOR_HPP_