#include "Motor.hpp"

#include <frc/Timer.h>

// This is a comment because Carter wanted more comments

void Drip::Motor::Set(double Input) {
    if (!PointerSet) return;
    if (LPM) Input *= 0.5;
    RawObject.get().Set(Input); // Get the actual motor and set it
}

void Drip::Motor::Set(double Input, double Time) {
    frc::Timer TimerObj;

    TimerObj.Start();
    Set(Input);
    while (!TimerObj.HasElapsed( units::second_t(Time) )) {
        ;
    }

    TimerObj.Stop();
    Set(0.0);
    // Because when Timer gets created at start and deleted at end, no need for resetting it
}

double Drip::Motor::Get(void) const {
    if (!PointerSet) return 0.0;
    return RawObject.get().Get();
}

void Drip::Motor::SetInverted(bool Input) {
    if (!PointerSet) return;
    RawObject.get().SetInverted(Input);
}

bool Drip::Motor::GetInverted(void) const {
    if (!PointerSet) return false;
    return RawObject.get().GetInverted();
}

void Drip::Motor::Invert(void) {
    if (!PointerSet) return;
    SetInverted(!GetInverted());
}

void Drip::Motor::Disable(void) {
    if (!PointerSet) return;
    RawObject.get().Disable();
}


void Drip::Motor::StopMotor(void) {
    if (!PointerSet) return;
    RawObject.get().StopMotor();
}

void Drip::Motor::operator= (frc::MotorController &Input) {
    RawObject = Input;
    PointerSet = true;
}

void Drip::Motor::operator= (double Input) {
    Set(Input);
}

Drip::Motor::Motor(void) {
    return;
}

Drip::Motor::Motor(frc::MotorController &Input) {
    RawObject = Input;
    PointerSet = true;
}
