#include "robot_controller2_ackm/ada_servo_driver.hpp"

int main() {
  AdaServoDriver driver;

  if (driver.initAdaServoDriver(0x40, (char*)"/dev/i2c-1") !=
      AdaServoReturnType::OK) {
    std::cerr << "Failed to initialize AdaServoDriver" << std::endl;
    return -1;
  }

  if (driver.setPWMFreq(60) != AdaServoReturnType::OK) {
    std::cerr << "Failed to set PWM frequency" << std::endl;
    return -1;
  }
  uint8_t servo_num = 1;

  // Sweep the servo from hi to low
  for (uint16_t dc = 200; dc <= 370; dc += 5) {
    driver.setPWM(servo_num, servo_num, dc);
    std::cout << "Setting duty cycle: " << dc << std::endl;
    usleep(1000000);  // Sleep for 1 second
  }


  return 0;
}

// g++ -I./include ada_servo_driver.cpp test_drive.cpp -o test_drive