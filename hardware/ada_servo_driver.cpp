// Test double for ada_servo_driver.hpp

#include "robot_controller2_ackm/ada_servo_driver.hpp"

AdaServoDriver::AdaServoDriver() noexcept {
  // Default constructor
}

AdaServoReturnType AdaServoDriver::initAdaServoDriver(uint8_t addr,
                                                      char *fname) noexcept {
  // Parameter check
  if (addr == 0x00) {
    return AdaServoReturnType::INVALID_PARAM;
  }
  _i2c_addr = addr;
  if (fname == nullptr) {
    return AdaServoReturnType::INVALID_PARAM;
  }
  _i2c_fname = fname;

  // Device initialization
  if ((_i2c = open(_i2c_fname, O_RDWR)) < 0) {
    return AdaServoReturnType::HW_ERROR;
  }

  if (ioctl(_i2c, I2C_SLAVE, _i2c_addr) < 0) {
    return AdaServoReturnType::HW_ERROR;
  }

  uint8_t mode1;

  setAllPWM(0, 0);
  write8(PCA9685_MODE2, OUTDRV);
  write8(PCA9685_MODE1, ALLCALL);
  usleep(500);

  mode1 = read8(PCA9685_MODE1);
  mode1 = mode1 & ~SLEEP;
  write8(PCA9685_MODE1, mode1);
  usleep(500);

  return AdaServoReturnType::OK;
}

AdaServoReturnType AdaServoDriver::setPWMFreq(float frea) noexcept {
  // Parameter check
  if (frea <= 0) {
    return AdaServoReturnType::INVALID_PARAM;
  }

  // Set PWM frequency
  float prescaleval = 25000000;

  prescaleval /= 4096;
  prescaleval /= frea;
  prescaleval -= 1;
  std::cout << "Estimated pre-scale: " << prescaleval << std::endl;

  uint8_t prescale = floor(prescaleval + 0.5);
  std::cout << "Final pre-scale: " << prescale << std::endl;

  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode & 0x7F) | 0x10;
  write8(PCA9685_MODE1, newmode);
  write8(PCA9685_PRESCALE, prescale);
  write8(PCA9685_MODE1, oldmode);
  usleep(500);
  write8(PCA9685_MODE1, oldmode | 0x80);

  return AdaServoReturnType::OK;
}

AdaServoReturnType AdaServoDriver::setPWM(uint8_t svn, uint16_t on_time,
                                          uint16_t off_time) noexcept {
  // Parameter check
  if (svn < AdaServoSetting::MIN_SERVO_NUM ||
      svn > AdaServoSetting::MAX_SERVO_NUM) {
    return AdaServoReturnType::INVALID_PARAM;
  }

  // Set PWM
  write8(LED0_ON_L + 4 * svn, (uint8_t)(0x00ff & on_time));
  write8(LED0_ON_H + 4 * svn, (uint8_t)((0xff00 & on_time) >> 8));
  write8(LED0_OFF_L + 4 * svn, (uint8_t)(0x00ff & off_time));
  write8(LED0_OFF_H + 4 * svn, (uint8_t)((0xff00 & off_time) >> 8));

  return AdaServoReturnType::OK;
}

AdaServoReturnType AdaServoDriver::setAllPWM(uint16_t on_time,
                                             uint16_t off_time) noexcept {
  write8(ALL_LED_ON_L, (uint8_t)(0x00ff & on_time));
  write8(ALL_LED_ON_H, (uint8_t)((0xff00 & on_time) >> 8));
  write8(ALL_LED_OFF_L, (uint8_t)(0x00ff & off_time));
  write8(ALL_LED_OFF_H, (uint8_t)((0xff00 & off_time) >> 8));
}

// Private primitive methods
void AdaServoDriver::write8(uint8_t addr, uint8_t d) noexcept {
  uint8_t sendData[2];

  sendData[0] = addr;
  sendData[1] = d;
  if (write(_i2c, sendData, 2) != 2) {
    std::cerr << "Faild to send i2c\n" << std::endl;
  }
}

uint8_t AdaServoDriver::read8(uint8_t addr) noexcept {
  uint8_t sendData;
  uint8_t readData;

  sendData = addr;
  if (write(_i2c, &sendData, 1) != 1) {
    std::cerr << "Failed to send i2c @read" << std::endl;
  } else {
    if (read(_i2c, &readData, 1) != 1) {
      std::cerr << "Failed to read i2c" << std::endl;
    }
  }

  return readData;
}
