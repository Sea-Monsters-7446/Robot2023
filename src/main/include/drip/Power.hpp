#pragma once

#include <frc/PowerDistribution.h>

namespace Drip {
    class PDP : public frc::PowerDistribution { // Pretty sure this can be global
        public:
            bool CriticalPower(void);
            bool LowPower(void);
    };
}
