// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Claw.h"

Claw::Claw(int pully_port, int pickerUpper_port) :
    m_pully(pully_port),
    m_pickerUpper(pickerUpper_port)
{

}

void Claw::manualMove(frc::PS4Controller& controller) {
    if (controller.GetL1Button()) {
        m_pully.Set(1);
    }
    if (controller.GetR1Button()) {
        m_pully.Set(-1);
    }
    if (controller.GetL2Button()) {
        m_pickerUpper.Set(1);
    }
    if (controller.GetR2Button()) {
        m_pickerUpper.Set(-1);
    }
}
