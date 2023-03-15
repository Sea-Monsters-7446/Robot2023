// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Claw.h"

Claw::Claw(int lazySusan_port, int armVertical_port, int armHorizontal_port, int armJoints_port) :
    m_lazySusan(lazySusan_port),
    m_armVertical(armVertical_port),
    m_armHorizontal(armHorizontal_port),
    m_armJoints(armJoints_port)
{

}

void Claw::manualMove(frc::PS4Controller& controller) {
    
}
