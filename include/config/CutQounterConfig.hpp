#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _CutQounterConfig : QounterConfig {
        QountersMinus::QounterPosition position = QountersMinus::QounterPosition::OverHighway;
        
        bool separateSaberCounts = true;
        bool separateCutValues = true;
        int averagePrecision = 1;
    } CutQounterConfig;
}
