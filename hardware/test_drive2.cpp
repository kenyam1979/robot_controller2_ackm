#include "robot_controller2_ackm/drive_motor.hpp"

using namespace controller_tamiya_tt02;

int main() {
  DriveMotor dm;

  uint8_t servo_num = 0;

  if (dm.initialize(servo_num, 0x40, (char*)"/dev/i2c-1") !=
      MotorReturnType::OK) {
    std::cerr << "Failed to initialize DriveMotor" << std::endl;
    return -1;
  }

  // Sweep the servo from hi to low
  for (double rpm = 0.0; rpm < 2000.0; rpm += 100.0) {
    if (dm.setRPM(rpm) != MotorReturnType::OK) {
      std::cerr << "Failed to set RPM: " << rpm << std::endl;
      return -1;
    }
    std::cout << "Setting rpm" << dm.getRPM() << std::endl;
    usleep(1000000);  // Sleep for 1 second
  }

  dm.stopMotor();

  return 0;
}

// g++ -I./include ada_servo_driver.cpp motor.cpp drive_motor.cpp test_drive2.cpp -o test_drive2