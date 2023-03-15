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
        Claw() = delete;
        
        /**
         * @brief Constructs a new instance of `Claw`
         *
         * @param lazySusan_port The port of the "Lazy Susan"
         *
         * @param armVertical_port The port for the vertical leg of the CLAW
         *
         * @param armHorizontal_port The port for the horizontal leg of the CLAW
         *
         * @param armJoints_port The port for the joints of the CLAW
         *
         */
        Claw(int lazySusan_port, int armVertical_port, int armHorizontal_port, int armJoints_port);

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
        frc::PWMVictorSPX m_lazySusan;
        frc::PWMVictorSPX m_armVertical;
        frc::PWMVictorSPX m_armHorizontal;
        frc::PWMVictorSPX m_armJoints;
};
