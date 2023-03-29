// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Claw.h"

Claw::Claw(int lazySusan_port, int armJoints_port, int bob) :
    m_lazySusan(lazySusan_port),
    m_armJoints(armJoints_port),
    m_clawMotor(bob),
    m_claw(m_clawMotor)
{

}

void Claw::manualMove(frc::PS4Controller& controller) {
    m_lazySusan.Set(static_cast<int>(controller.GetL2Button()));
    m_lazySusan.Set(static_cast<int>(controller.GetR2Button()) - 1);
    m_claw(controller.GetCrossButton(), false);
}
