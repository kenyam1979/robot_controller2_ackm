#ifndef MOTOR__TAMIYA_TT02_HPP_
#define MOTOR__TAMIYA_TT02_HPP_

#include <stdint.h>

#include "robot_controller2_ackm/ada_servo_driver.hpp"

namespace controller_tamiya_tt02 {

enum MotorSetting {
  MAX_MV = 500,
};

enum MotorReturnType {
  OK = 0,
  ERROR = -1,
  DRIVER_ERROR = -2,
  INITIALIZATION_ERROR = -3
};

class Motor {
 public:
  Motor() noexcept;
  MotorReturnType initialize(uint8_t svn, uint8_t addr,
                             char* dev_fname) noexcept;
  MotorReturnType setManipulatingVariable(int mv) noexcept;
  int getManipulatingVariable() const noexcept;
  MotorReturnType stopMotor() noexcept;
  ~Motor() noexcept;

 private:
  static AdaServoDriver motor_driver_;
  int manipulating_variable_;
  uint8_t servo_no_;
};

}  // namespace controller_tamiya_tt02

#endif  // MOTOR__TAMIYA_TT02_HPP_