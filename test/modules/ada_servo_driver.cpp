// Test double for ada_servo_driver.hpp

#include "robot_controller2_ackm/ada_servo_driver.hpp"

AdaServoDriver::AdaServoDriver() noexcept {
  // Default constructor
}

AdaServoReturnType AdaServoDriver::initAdaServoDriver(uint8_t addr,
                                                      char *fname) noexcept {
  // Initialize the I2C device

  if (addr == 0x00) {
    return AdaServoReturnType::INVALID_PARAM;
  }
  _i2c_addr = addr;
  if (fname == nullptr) {
    return AdaServoReturnType::INVALID_PARAM;
  }
  _i2c_fname = fname;

  return AdaServoReturnType::OK;
}

AdaServoReturnType AdaServoDriver::setPWMFreq(float frea) noexcept {
  return AdaServoReturnType::OK;
}

AdaServoReturnType AdaServoDriver::setPWM(uint8_t svn, uint16_t on_time,
                                          uint16_t off_time) noexcept {
  if (svn < AdaServoSetting::MIN_SERVO_NUM ||
      svn > AdaServoSetting::MAX_SERVO_NUM) {
    return AdaServoReturnType::INVALID_PARAM;
  }
  return AdaServoReturnType::OK;
}
