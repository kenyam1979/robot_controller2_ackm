#include <unistd.h>

#include <iostream>

#include "lgpio.h"
#include "robot_controller2_ackm/photo_encoder.hpp"

using namespace controller_tamiya_tt02;

int main() {
  PhotoEncoder pe;

  if (pe.initialize(PhotoEncoderSetting::GPIO_CHIP,
                    PhotoEncoderSetting::ENC_PIN) !=
      PhotoEncoderReturnType::OK) {
    std::cerr << "Failed to initialize PhotoEncoder." << std::endl;
    return -1;
  }

  while (1) {
    usleep(1000000);  // Sleep for 1 second
    float rpm = pe.getAngularVelocity(1.0);
    std::cout << "AV: " << rpm << std::endl;
  }

  if (pe.reset() != PhotoEncoderReturnType::OK) {
    return -1;
  }

  return 0;
}

// g++ -Wall -I./include photo_encoder.cpp test_photoencoder2.cpp -llgpio -o test_photoencoder2
