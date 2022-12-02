#pragma once

#include <functional>

#include <frc/motorcontrol/MotorController.h>

namespace Drip {
    class Motor : public frc::MotorController {
        public:
            bool LPM = false;                       // Low Power Mode

            // Extentions
            void    Invert      (void);             // Add to make inversions quicker
            void    Set         (double, double);   // Set for time
            void    operator=   (double);           // Alias for Set
            //

            // Controls
            void    Set         (double)    override;
            double  Get         (void)      const override;
            void    SetInverted (bool)      override;
            bool    GetInverted (void)      const override;
            void    Disable     (void)      override;
            void    StopMotor   (void)      override;
            //

            // Setting the motor object
           void operator= (frc::MotorController &);
            //

            Motor(void);
            Motor(frc::MotorController &);
        private:
            // Casting nullptr to a pointer of a MotorController class
            // Basically equal to (frc::MotorController &)nullptr;

            // nullptr has an address so no & (reference) needed
            // (frc::MotorController *) casts the type to frc::MotorController * (pointer of frc::MotorController)
            // Since we cannot construct with a frc::MotorController * (pointer of frc::MotorController), we need to get the reference
            // We then get the value in the reference (which is why we need to check if we can use it with PointerSet)
            std::reference_wrapper<frc::MotorController> RawObject = *(frc::MotorController *)nullptr;

            bool PointerSet = false;
            //
    };
}
