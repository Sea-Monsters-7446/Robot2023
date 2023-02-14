#pragma once

#include <functional>

#include <frc/Joystick.h>
#include <frc/PS4Controller.h>
#include <frc/XboxController.h>

namespace Drip {
    class AxisTrigger {
        public:
            std::function<void(double)> Changed;
    };

    class ButtonTrigger {
        public:
            std::function<void(void)> Pressed;
            std::function<void(void)> Released;
    };

    class POVTrigger { // So most of these controllers have this, but they don't use them?
        public:
            std::function<void(double)> Changed;
    };

    class Joystick : public frc::Joystick {
        public:
            AxisTrigger X;
            AxisTrigger Y;
            AxisTrigger Z;
            
            AxisTrigger Twist;
            AxisTrigger Throttle;

            ButtonTrigger Trigger;
            ButtonTrigger Top;

            void Update(void);

            Joystick(int Port) : frc::Joystick(Port) { ; }
        private:
            double AxisValues[5];
    };

    class PS4Controller : public frc::PS4Controller {
        public:
            // Sticks
            AxisTrigger LeftX;
            AxisTrigger RightX;
            AxisTrigger LeftY;
            AxisTrigger RightY;

            ButtonTrigger L3Button;
            ButtonTrigger R3Button;
            //

            // Bumpers and triggers
            AxisTrigger L2Axis;
            AxisTrigger R2Axis;

            ButtonTrigger L1Button;
            ButtonTrigger R1Button;
            //

            // Face buttons and the other ones
            ButtonTrigger CrossButton;
            ButtonTrigger CircleButton;
            ButtonTrigger SquareButton;
            ButtonTrigger TriangleButton;
            ButtonTrigger ShareButton;
            ButtonTrigger OptionsButton;
            ButtonTrigger PSButton;
            ButtonTrigger Touchpad;
            //

            void Update(void);

            PS4Controller(int Port) : frc::PS4Controller(Port) { ; }
        private:
            double AxisValues[6];
    };

    class XboxController : public frc::XboxController {
        public:
            // Sticks
            AxisTrigger LeftX;
            AxisTrigger RightX;
            AxisTrigger LeftY;
            AxisTrigger RightY;

            ButtonTrigger LeftStickButton;
            ButtonTrigger RightStickButton;
            //

            // Bumpers and triggers
            AxisTrigger LeftTriggerAxis;
            AxisTrigger RightTriggerAxis;

            ButtonTrigger LeftBumper;
            ButtonTrigger RightBumper;
            //

            // Face buttons and the other ones
            ButtonTrigger AButton;
            ButtonTrigger BButton;
            ButtonTrigger XButton;
            ButtonTrigger YButton;
            ButtonTrigger BackButton;
            ButtonTrigger StartButton;
            //

            void Update(void);

            XboxController(int Port) : frc::XboxController(Port) { ; }
        private:
            double AxisValues[6];
    };
}
