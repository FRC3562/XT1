// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
// #include <frc/motorcontrol/PWMSparkMax.h>
#include "rev/CANSparkMax.h"

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with tank steering and an Xbox controller.
 */
class Robot : public frc::TimedRobot {
 // rev::CANSparkMax m_leftMotor{0};
 // frc::PWMSparkMax m_rightMotor{1};
 // frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::XboxController m_driverController{0};

  static const int leftLeadDeviceID = 2, leftFollowDeviceID = 4, rightLeadDeviceID = 1, rightFollowDeviceID = 3;
  rev::CANSparkMax m_leftLeadMotor{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightLeadMotor{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftFollowMotor{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightFollowMotor{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

  frc::DifferentialDrive m_robotDrive{m_leftLeadMotor, m_rightLeadMotor};


 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    // m_rightMotor.SetInverted(true);

    m_leftFollowMotor.Follow(m_leftLeadMotor);
    m_rightFollowMotor.Follow(m_rightLeadMotor);
  }

  void TeleopPeriodic() override {
    // Drive with tank style
    m_robotDrive.TankDrive(-m_driverController.GetLeftY(),
                           -m_driverController.GetRightY());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
