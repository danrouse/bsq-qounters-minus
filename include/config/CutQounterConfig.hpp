#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _CutQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::OverHighway;

        bool separateSaberCounts = false;
        bool separateCutValues = false;
        int averagePrecision = 1;
    } CutQounterConfig;
}
