#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef enum _SpinometerMode {
        Average,
        SplitAverage,
        Highest
    } SpinometerMode;

    typedef struct _SpinometerConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveMultiplier;
        
        SpinometerMode mode = SpinometerMode::SplitAverage;
        bool separateCutValues = true;
        int averagePrecision = 1;
    } SpinometerConfig;
}
