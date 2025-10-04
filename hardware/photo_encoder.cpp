#include "robot_controller2_ackm/photo_encoder.hpp"

namespace controller_tamiya_tt02 {

void PhotoEncoder::encCB(int e, lgGpioAlert_p evt, void *data) {
  *(int *)data += 1;
  // std::cout << *(int*)data << std::endl;
}

PhotoEncoder::PhotoEncoder() noexcept {}

PhotoEncoderReturnType PhotoEncoder::initialize(int gpiochip,
                                                int pin) noexcept {
  gpiochip_ = gpiochip;
  pin_ = pin;

  chip_ = lgGpiochipOpen(gpiochip_);
  if (chip_ < 0) {
    // std::cerr << lguErrorText(chip_) << std::endl;
    return PhotoEncoderReturnType::DRIVER_ERROR;
  }

  if (lgGpioSetAlertsFunc(chip_, pin_, PhotoEncoder::encCB, &count_) < 0) {
    return PhotoEncoderReturnType::DRIVER_ERROR;
  }

  if (lgGpioClaimAlert(chip_, 0, LG_RISING_EDGE, pin_, -1) < 0) {
    return PhotoEncoderReturnType::DRIVER_ERROR;
  }

  return PhotoEncoderReturnType::OK;
}

float PhotoEncoder::getRPM(float diff) noexcept {
  if (diff <= 0.0) {
    return HUGE_VAL; //PhotoEncoderReturnType::ERROR  // Avoid division by zero
  }

  float rpm = 0.0;
  current_ = count_;
  rpm = ((float)(current_ - previous_) / PhotoEncoderSetting::GEAR_TOOTH) /
        diff * 60.0;
  previous_ = current_;
  return rpm;
}


float PhotoEncoder::getAngularVelocity(float diff) noexcept {
  if (diff <= 0.0) {
    return HUGE_VAL;  // PhotoEncoderReturnType::ERROR  // Avoid division by zero
  }
  float rpm = getRPM(diff);
  return rpm / 60.0 * (2.0 * M_PI);
}

PhotoEncoderReturnType PhotoEncoder::reset() noexcept {
  if (lgGpiochipClose(chip_) < 0) {
    return PhotoEncoderReturnType::DRIVER_ERROR;
  }

  count_ = 0;
  current_ = 0;
  previous_ = 0;

  return PhotoEncoderReturnType::OK;
}

PhotoEncoder::~PhotoEncoder() noexcept {}

}  // namespace controller_tamiya_tt02
