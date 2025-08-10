#include "robot_controller2_ackm/motor_pid.hpp"

namespace controller_tamiya_tt02 {

MotorPID::MotorPID() noexcept {}

MotorPIDReturnType MotorPID::initialize() noexcept { return MotorPIDReturnType::OK; }

MotorPID::~MotorPID() noexcept {}

}  // namespace controller_tamiya_tt02