#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _MissedQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowCombo;

        bool countBadCuts = true;
    } MissedQounterConfig;
}
