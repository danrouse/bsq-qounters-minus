#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _MissedQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowCombo;
        bool enabled = true;
        int distance = 0;
        bool countBadCuts = true;
    } MissedQounterConfig;
}
