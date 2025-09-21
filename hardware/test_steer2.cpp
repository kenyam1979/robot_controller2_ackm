#include "robot_controller2_ackm/steer_motor.hpp"

using namespace controller_tamiya_tt02;

int main() {
  SteeringMotor sm;

  uint8_t servo_num = 1;

  if (sm.initialize(servo_num, 0x40, (char*)"/dev/i2c-1") !=
      MotorReturnType::OK) {
    std::cerr << "Failed to initialize DriveMotor" << std::endl;
    return -1;
  }

  // Sweep the servo from left to right
  for (double a = -30.0; a <= 30.0; a += 5.0) {
    double angle = a * M_PI / 180.0;
    if (sm.setAngle(angle) != MotorReturnType::OK) {
      std::cerr << "Failed to set angle: " << angle << std::endl;
      return -1;
    }
    std::cout << "Setting angle(rad): " << sm.getAngle() << " angle(degree)"
              << a << std::endl;
    usleep(500000);  // Sleep for 0.5 seconds
  }

  sm.setNeutral();
  usleep(500000);  // Sleep for 0.5 seconds

  return 0;
}


// g++ -I./include ada_servo_driver.cpp motor.cpp steer_motor.cpp test_steer2.cpp -o test_steer2
