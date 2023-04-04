// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/PS4Controller.h>
#include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/drive/DifferentialDrive.h>
#include "Claw.h"
#include "cameraserver/CameraServer.h"

class Robot : public frc::TimedRobot {
 public:

  Robot();

  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  frc::PS4Controller m_controller;

  frc::PWMVictorSPX m_leftMotor;

  frc::PWMVictorSPX m_rightMotor;

  frc::DifferentialDrive m_drive;

  Claw m_clawMechanism;

  cs::UsbCamera m_camera;
};
