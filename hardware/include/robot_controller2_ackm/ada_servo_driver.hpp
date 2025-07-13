// Ada I2C 16ch Servo Driver (PCA9685)

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

#define PCA9685_SUBADR1 0x02
#define PCA9685_SUBADR2 0x03
#define PCA9685_SUBADR3 0x04

#define PCA9685_MODE1 0x00
#define PCA9685_MODE2 0x01
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09

#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD

#define RESTART 0x80
#define SLEEP 0x10
#define ALLCALL 0x01
#define INVRT 0x10
#define OUTDRV 0x04

enum AdaServoSetting {
  MIN_SERVO_NUM = 0,
  MAX_SERVO_NUM = 15,
  PWM_FREQ = 60
  // ...
};

enum AdaServoReturnType {
  OK = 0,
  // INIT_ERROR = -1,
  // SET_PWM_ERROR = -2
  FAIL_EXEC = -1,
  INVALID_PARAM = -3
};

class AdaServoDriver {
 public:
  AdaServoDriver() noexcept;
  AdaServoReturnType initAdaServoDriver(uint8_t addr, char *fname) noexcept;
  // void reset(void);
  AdaServoReturnType setPWMFreq(float frea) noexcept;
  AdaServoReturnType setPWM(uint8_t srvNo, uint16_t on_time, uint16_t off_time) noexcept;
  AdaServoReturnType setAllPWM(uint16_t on_time, uint16_t off_time) noexcept;
  // void setServoPulse(uint8_t ch, double pulseWidth_us);

 private:
  int _i2c;
  uint8_t _i2c_addr = 0x40;         // Default I2C address for PCA9685
  char *_i2c_fname = "/dev/i2c-1";  // Default I2C device file

  uint8_t read8(uint8_t addr) noexcept;
  void write8(uint8_t addr, uint8_t d) noexcept;

};
