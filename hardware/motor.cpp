#include "robot_controller2_ackm/motor.hpp"

namespace controller_tamiya_tt02 {

AdaServoDriver Motor::motor_driver_;

Motor::Motor() noexcept {
  manipulating_variable_ = 0;
  servo_no_ = 0;
}

MotorReturnType Motor::initialize(uint8_t svn) noexcept {
  motor_driver_.initAdaServoDriver(0x40, "/dev/i2c-1");
  motor_driver_.setPWMFreq(AdaServoSetting::PWM_FREQ);

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
  manipulating_variable_ = 0;
  motor_driver_.setPWM(servo_no_, 0, 0);
  return MotorReturnType::OK;
}

Motor::~Motor() noexcept { stopMotor(); }

}  // namespace controller_tamiya_tt02
