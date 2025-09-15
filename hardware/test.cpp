#include "robot_controller2_ackm/ada_servo_driver.hpp"

int main() {
  AdaServoDriver driver;
  driver.initAdaServoDriver(0x40, (char*)"/dev/i2c-1");

  driver.setPWMFreq(60);

  uint8_t servo_num = 0;

  // Set the initial duty cycle to 380 (which corresponds to 0 degrees)
  driver.setPWM(servo_num, 0, 380);

  // Sweep the servo from left to right
  for (uint16_t dc = 320; dc <= 445; dc += 5) {
    driver.setPWM(servo_num, 0, dc);
    std::cout << "Setting duty cycle: " << dc << std::endl;
    usleep(500000);  // Sleep for 0.5 seconds
  }

  return 0;
}

// g++ -I./include ada_servo_driver.cpp test.cpp