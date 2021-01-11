#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _CutQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveHighway;
        int distance = 1;
        bool separateSaberCounts = false;
        bool separateCutValues = false;
        int averagePrecision = 1;
    } CutQounterConfig;
}
