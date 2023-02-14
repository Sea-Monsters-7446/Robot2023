#include "drip/Power.hpp"

bool Drip::PDP::CriticalPower(void) {
    return GetVoltage() <= 6.5;
}

bool Drip::PDP::LowPower(void) {
    return GetVoltage() <= 7.0;
}
