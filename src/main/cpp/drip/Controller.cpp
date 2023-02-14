#include "drip/Controller.hpp"

void Drip::Joystick::Update(void) {
    double Temp;

    Temp = GetX();
    if (AxisValues[0] != Temp) {
        AxisValues[0] = Temp;
        if (X.Changed) X.Changed(Temp);
    }

    Temp = GetY();
    if (AxisValues[1] != Temp) {
        AxisValues[1] = Temp;
        if (Y.Changed) Y.Changed(Temp);
    }

    Temp = GetZ();
    if (AxisValues[2] != Temp) {
        AxisValues[2] = Temp;
        if (Z.Changed) Z.Changed(Temp);
    }

    Temp = GetTwist();
    if (AxisValues[3] != Temp) {
        AxisValues[3] = Temp;
        if (Twist.Changed) Twist.Changed(Temp);
    }

    Temp = GetThrottle();
    if (AxisValues[4] != Temp) {
        AxisValues[4] = Temp;
        if (Throttle.Changed) Throttle.Changed(Temp);
    }

    if (Trigger.Pressed     &&  GetTriggerPressed())    Trigger.Pressed();
    if (Trigger.Released    &&  GetTriggerReleased())   Trigger.Released();
}

void Drip::PS4Controller::Update(void) {
    double Temp;

    Temp = GetLeftX();
    if (AxisValues[0] != Temp) {
        AxisValues[0] = Temp;
        if (LeftX.Changed) LeftX.Changed(Temp);
    }

    Temp = GetRightX();
    if (AxisValues[1] != Temp) {
        AxisValues[1] = Temp;
        if (RightX.Changed) RightX.Changed(Temp);
    }

    Temp = GetLeftY();
    if (AxisValues[2] != Temp) {
        AxisValues[2] = Temp;
        if (LeftY.Changed) LeftY.Changed(Temp);
    }

    Temp = GetRightY();
    if (AxisValues[3] != Temp) {
        AxisValues[3] = Temp;
        if (RightY.Changed) RightY.Changed(Temp);
    }

    Temp = GetL2Axis();
    if (AxisValues[4] != Temp) {
        AxisValues[4] = Temp;
        if (L2Axis.Changed) L2Axis.Changed(Temp);
    }

    Temp = GetR2Axis();
    if (AxisValues[5] != Temp) {
        AxisValues[5] = Temp;
        if (R2Axis.Changed) R2Axis.Changed(Temp);
    }

    if (L3Button.Pressed        &&  GetL3ButtonPressed())           L3Button.Pressed();
    if (L3Button.Released       &&  GetL3ButtonReleased())          L3Button.Released();

    if (R3Button.Pressed        &&  GetR3ButtonPressed())           R3Button.Pressed();
    if (R3Button.Released       &&  GetR3ButtonReleased())          R3Button.Released();

    if (L1Button.Pressed        &&  GetL1ButtonPressed())           L1Button.Pressed();
    if (L1Button.Released       &&  GetL1ButtonReleased())          L1Button.Released();

    if (R1Button.Pressed        &&  GetR1ButtonPressed())           R1Button.Pressed();
    if (R1Button.Released       &&  GetR1ButtonReleased())          R1Button.Released();

    if (CrossButton.Pressed     &&  GetCrossButtonPressed())        CrossButton.Pressed();
    if (CrossButton.Released    &&  GetCrossButtonReleased())       CrossButton.Released();

    if (CircleButton.Pressed    &&  GetCircleButtonPressed())       CircleButton.Pressed();
    if (CircleButton.Released   &&  GetCircleButtonReleased())      CircleButton.Released();

    if (SquareButton.Pressed    &&  GetSquareButtonPressed())       SquareButton.Pressed();
    if (SquareButton.Released   &&  GetSquareButtonReleased())      SquareButton.Released();

    if (TriangleButton.Pressed  &&  GetTriangleButtonPressed())     TriangleButton.Pressed();
    if (TriangleButton.Released &&  GetTriangleButtonReleased())    TriangleButton.Released();

    if (ShareButton.Pressed     &&  GetShareButtonPressed())        ShareButton.Pressed();
    if (ShareButton.Released    &&  GetShareButtonReleased())       ShareButton.Released();

    if (OptionsButton.Pressed   &&  GetOptionsButtonPressed())      OptionsButton.Pressed();
    if (OptionsButton.Released  &&  GetOptionsButtonReleased())     OptionsButton.Released();

    if (PSButton.Pressed        &&  GetPSButtonPressed())           PSButton.Pressed();
    if (PSButton.Released       &&  GetPSButtonReleased())          PSButton.Released();

    if (Touchpad.Pressed        &&  GetTouchpadPressed())           Touchpad.Pressed();
    if (Touchpad.Released       &&  GetTouchpadReleased())          Touchpad.Released();
}

void Drip::XboxController::Update(void) {
    double Temp;

    Temp = GetLeftX();
    if (AxisValues[0] != Temp) {
        AxisValues[0] = Temp;
        if (LeftX.Changed) LeftX.Changed(Temp);
    }

    Temp = GetRightX();
    if (AxisValues[1] != Temp) {
        AxisValues[1] = Temp;
        if (RightX.Changed) RightX.Changed(Temp);
    }

    Temp = GetLeftY();
    if (AxisValues[2] != Temp) {
        AxisValues[2] = Temp;
        if (LeftY.Changed) LeftY.Changed(Temp);
    }

    Temp = GetRightY();
    if (AxisValues[3] != Temp) {
        AxisValues[3] = Temp;
        if (RightY.Changed) RightY.Changed(Temp);
    }

    Temp = GetLeftTriggerAxis();
    if (AxisValues[4] != Temp) {
        AxisValues[4] = Temp;
        if (LeftTriggerAxis.Changed) LeftTriggerAxis.Changed(Temp);
    }

    Temp = GetRightTriggerAxis();
    if (AxisValues[5] != Temp) {
        AxisValues[5] = Temp;
        if (RightTriggerAxis.Changed) RightTriggerAxis.Changed(Temp);
    }

    if (LeftStickButton.Pressed     &&  GetLeftStickButtonPressed())    LeftStickButton.Pressed();
    if (LeftStickButton.Released    &&  GetLeftStickButtonReleased())   LeftStickButton.Released();

    if (RightStickButton.Pressed    &&  GetRightStickButtonPressed())   RightStickButton.Pressed();
    if (RightStickButton.Released   &&  GetRightStickButtonReleased())  RightStickButton.Released();

    if (LeftBumper.Pressed          &&  GetLeftBumperPressed())         LeftBumper.Pressed();
    if (LeftBumper.Released         &&  GetLeftBumperReleased())        LeftBumper.Released();

    if (RightBumper.Pressed         &&  GetRightBumperPressed())        RightBumper.Pressed();
    if (RightBumper.Released        &&  GetRightBumperReleased())       RightBumper.Released();

    if (AButton.Pressed             &&  GetAButtonPressed())            AButton.Pressed();
    if (AButton.Released            &&  GetAButtonReleased())           AButton.Released();

    if (BButton.Pressed             &&  GetBButtonPressed())            BButton.Pressed();
    if (BButton.Released            &&  GetBButtonReleased())           BButton.Released();

    if (XButton.Pressed             &&  GetXButtonPressed())            XButton.Pressed();
    if (XButton.Released            &&  GetXButtonReleased())           XButton.Released();

    if (YButton.Pressed             &&  GetYButtonPressed())            YButton.Pressed();
    if (YButton.Released            &&  GetYButtonReleased())           YButton.Released();

    if (BackButton.Pressed          &&  GetBackButtonPressed())         BackButton.Pressed();
    if (BackButton.Released         &&  GetBackButtonReleased())        BackButton.Released();

    if (StartButton.Pressed         &&  GetStartButtonPressed())        StartButton.Pressed();
    if (StartButton.Released        &&  GetStartButtonReleased())       StartButton.Released();
}
