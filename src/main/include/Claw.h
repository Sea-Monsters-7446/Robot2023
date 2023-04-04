// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/PS4Controller.h>

/**
 * @brief Class to control the CLAW mechinism
 *
 */
class Claw {
    public:
        /**
         * @brief Constructs a new instance of `Claw`
         *
         * @param pully_port The port for the pully system
         *
         * @param pickerUpper_port The port for the pickerUpper
         *
         */
        Claw(int pully_port, int pickerUpper_port);

        /**
         * @brief Moves the CLAW manualy via the controller
         *
         * @param controller A reference to an instance of a controller
         *
         * @return void
         */
        void manualMove(frc::PS4Controller& controller);

        void autoMove() = delete;

    private:
        frc::PWMVictorSPX m_pully;
        frc::PWMVictorSPX m_pickerUpper;
};
