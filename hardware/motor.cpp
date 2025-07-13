#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

AdaServoDriver Motor::motor_driver_;

Motor::Motor() noexcept {
  manipulating_variable_ = 0;
  servo_no_ = MAX_SERVO_NUM + 1; // Invalid initial value to be initialized later
}

MotorReturnType Motor::initialize(uint8_t svn, uint8_t addr, char* dev_fname) noexcept {

  if (motor_driver_.initAdaServoDriver(addr, dev_fname) != AdaServoReturnType::OK) {
    return MotorReturnType::DRIVER_ERROR;
  }
  
  if (motor_driver_.setPWMFreq(AdaServoSetting::PWM_FREQ) != AdaServoReturnType::OK) {
    return MotorReturnType::DRIVER_ERROR;
  } 

  if (svn < AdaServoSetting::MIN_SERVO_NUM ||
      svn > AdaServoSetting::MAX_SERVO_NUM) {
    return MotorReturnType::ERROR;
  }

  servo_no_ = svn;
  return MotorReturnType::OK;
}

int Motor::getManipulatingVariable() const noexcept {
  return manipulating_variable_;
}

MotorReturnType Motor::setManipulatingVariable(int mv) noexcept {
  manipulating_variable_ = mv;

  if (mv > MotorSetting::MAX_MV) {
    manipulating_variable_ = MotorSetting::MAX_MV;
  } else if (mv < -MotorSetting::MAX_MV) {
    manipulating_variable_ = -MotorSetting::MAX_MV;
  }

  motor_driver_.setPWM(servo_no_, 0, manipulating_variable_);
  return MotorReturnType::OK;

}

MotorReturnType Motor::stopMotor() noexcept {

  if (servo_no_ > AdaServoSetting::MAX_SERVO_NUM) {
    return MotorReturnType::INITIALIZATION_ERROR;
  }

  manipulating_variable_ = 0;

  if (motor_driver_.setPWM(servo_no_, 0, 0) != AdaServoReturnType::OK) {
    return MotorReturnType::DRIVER_ERROR;
  }

  return MotorReturnType::OK;
}

Motor::~Motor() noexcept { stopMotor(); }

}  // namespace controller_tamiya_tt02
