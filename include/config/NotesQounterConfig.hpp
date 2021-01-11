#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _NotesQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowCombo;
        int distance = 1;
        bool showPercentage = false;
        int decimalPrecision = 2;
    } NotesQounterConfig;
}
