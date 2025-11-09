#include "robot_controller2_ackm/drive_motor.hpp"
#include "robot_controller2_ackm/photo_encoder.hpp"

using namespace controller_tamiya_tt02;

int main() {
  DriveMotor dm;
  PhotoEncoder pe;

  uint8_t servo_num = 0;
  if (dm.initialize(servo_num, 0x40, (char*)"/dev/i2c-1") !=
      MotorReturnType::OK) {
    std::cerr << "Failed to initialize DriveMotor" << std::endl;
    return -1;
  }

  if (pe.initialize(PhotoEncoderSetting::GPIO_CHIP,
                    PhotoEncoderSetting::ENC_PIN) !=
      PhotoEncoderReturnType::OK) {
    std::cerr << "Failed to initialize PhotoEncoder." << std::endl;
    return -1;
  }
  double av = 50.0;

  // PWM warmup
  dm.setAngularVelocity(0.0);
  usleep(1000000);

  for (double t = 0.0; t < 1.0; t += 0.1) {
    if (dm.setAngularVelocity(av) != MotorReturnType::OK) {
      std::cerr << "Failed to set AV: " << av << std::endl;
      return -1;
    }
    // std::cout << "Setting AV" << dm.getAngularVelocity() << std::endl;
    std::cout << "av: " << av << ", " << t << ", " << pe.getAngularVelocity(0.1)
              << std::endl;
    usleep(100000);  // Sleep for 0.1 second
  }

  dm.stopMotor();
  pe.reset();

  return 0;
}

// g++ -I./include ada_servo_driver.cpp  motor.cpp drive_motor.cpp
// test_drive4.cpp photo_encoder.cpp -llgpio -o test_drive4