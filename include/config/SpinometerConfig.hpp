#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef enum _SpinometerMode {
        Average,
        SplitAverage,
        Highest
    } SpinometerMode;

    static int SpinometerModeCount = 3;
    static std::map<SpinometerMode, std::string> SpinometerModeNames = {
        {SpinometerMode::Average, "Average"},
        {SpinometerMode::SplitAverage, "Split Average"},
        {SpinometerMode::Highest, "Highest"}
    };

    typedef struct _SpinometerConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveMultiplier;
        
        SpinometerMode mode = SpinometerMode::SplitAverage;
        bool separateCutValues = true;
        int averagePrecision = 1;
    } SpinometerConfig;
}
