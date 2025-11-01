#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

// These macros are defined according to the PCA9685 datasheet
// Reference https://www.nxp.jp/docs/en/data-sheet/PCA9685.pdf
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

// Enumeration for servo settings
enum AdaServoSetting { MIN_SERVO_NUM = 0, MAX_SERVO_NUM = 15, PWM_FREQ = 60 };

// Enumeration for return types of AdaServoDriver functions
enum AdaServoReturnType {
  OK = 0,
  ERROR = -1,
  HW_ERROR = -2,
  INVALID_PARAM = -3
};

// This class provides an interface to control the PCA9685 servo driver via I2C
// PCA9685 is I2C 16ch Servo Driver from Adafruit which can control up to 16
// servos with PWM via I2C interface.
class AdaServoDriver {
 public:
  // This constructor do actually nothing
  AdaServoDriver() noexcept;

  // This function initialize the PCA9685 servo driver
  AdaServoReturnType initAdaServoDriver(uint8_t addr, char* fname) noexcept;

  // This function set the PWM frequency for the servo driver
  AdaServoReturnType setPWMFreq(float frea) noexcept;

  // This function set the PWM duty cycle for a specific servo channel
  AdaServoReturnType setPWM(uint8_t srvNo, uint16_t on_time,
                            uint16_t off_time) noexcept;

  // This function set the PWM duty cycle for all servo channels
  AdaServoReturnType setAllPWM(uint16_t on_time, uint16_t off_time) noexcept;

  // This function close the I2C device file and reset the driver
  // AdaServoReturnType resetAdaServoDriver() noexcept;
  ~AdaServoDriver() noexcept;

 private:
  int _i2c;
  uint8_t _i2c_addr = 0x40;         // Default I2C address for PCA9685
  char* _i2c_fname = "/dev/i2c-1";  // Default I2C device file

  // These functions are primitive functions to read/write 8bits data from/to
  // a specific register address
  uint8_t read8(uint8_t addr) noexcept;
  void write8(uint8_t addr, uint8_t d) noexcept;
};
