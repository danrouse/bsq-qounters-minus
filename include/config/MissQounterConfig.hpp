#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _MissQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowCombo;
        
        bool countBadCuts = true;
    } MissQounterConfig;
}
