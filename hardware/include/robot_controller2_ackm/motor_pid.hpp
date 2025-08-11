#ifndef ROBOT_CONTROLLER2_ACKM__MOTOR_PID_HPP_
#define ROBOT_CONTROLLER2_ACKM__MOTOR_PID_HPP

namespace controller_tamiya_tt02 {

enum MotorPIDSetting { MAX_MV = 500 };

enum MotorPIDReturnType { OK = 0, ERROR = -1 };

class MotorPID {
 public:
  MotorPID() noexcept;
  MotorPIDReturnType initialize() noexcept;
  int calculateManipulatingVariable(double target_v, double current_v,
                                    double dt) noexcept;
  MotorPIDReturnType reset() noexcept;
  ~MotorPID() noexcept;

 private:
  // PID parameters
  const double kKp = 1.0;
  const double kKi = 1.0;
  const double kKd = 0.05;
  const double kMvCoef = 70.0;

  // PID calculation
  double error_P_ = 0.0;
  double error_P_prev_ = 0.0;
  double error_I_ = 0.0;
  double error_D_ = 0.0;

  // Input(target), output(mv) and feedback(current)
  double target_velocity_ = 0.0;
  double current_velocity_ = 0.0;
  int mv_ = 0;
};

}  // namespace controller_tamiya_tt02

#endif  // ROBOT_CONTROLLER2_ACKM__MOTOR_PID_HPP