#include <frc/motorcontrol/PWMVictorSPX.h>

#include "PickupClaw.h"
/**
 * @brief Construct a new `PickupController` object
 * 
 */
PickupController::PickupController(frc::PWMVictorSPX& pickupMech) :
    m_pickupMech(pickupMech)
{

}
/**
 * @brief Updates the PickupMech
 * 
 */
void PickupController::operator()(bool triggerButton, bool shiftButton) {
    if (triggerButton) {
        m_pickupMech.Set((shiftButton) ? -0.3 : 0.3);
    }
    else {
        m_pickupMech.Set(0);
    }
}
