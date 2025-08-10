#ifndef ROBOT_CONTROLLER2_ACKM__PHOTO_ENCODER_HPP_
#define ROBOT_CONTROLLER2_ACKM__PHOTO_ENCODER_HPP_

#include <iostream>

#include "lgpio.h"

namespace controller_tamiya_tt02 {

enum PhotoEncoderSetting {
  GPIO_CHIP = 4,
  ENC_PIN = 22,
  GEAR_TOOTH = 40,
};

enum PhotoEncoderReturnType {
  OK = 0,
  ERROR = -1,
  DRIVER_ERROR = -2,
  INITIALIZATION_ERROR = -3
};

class PhotoEncoder {
 public:
  PhotoEncoder() noexcept;
  PhotoEncoderReturnType initialize(int gpiochip, int pin) noexcept;
  float getRPM(float diff) noexcept;
  PhotoEncoderReturnType reset() noexcept;
  ~PhotoEncoder() noexcept;

 private:
  int gpiochip_;
  int pin_;
  int chip_;
  int count_ = 0;
  int current_ = 0;
  int previous_ = 0;

  static void encCB(int e, lgGpioAlert_p evt, void *data);

  // Only for unit testing purposes
 public:
  friend class PhotoEncoderTestFriend;
};

}  // namespace controller_tamiya_tt02

#endif  // ROBOT_CONTROLLER2_ACKM__PHOTO_ENCODER_HPP_