#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _NotesQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowCombo;
        bool showPercentage = true;
        int decimalPrecision = 1;
    } NotesQounterConfig;
}
