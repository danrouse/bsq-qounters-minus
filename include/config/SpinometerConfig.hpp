#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    enum class SpinometerMode {
        Average,
        SplitAverage,
        Highest
    };
    static int SpinometerModeCount = 3;
    static std::map<SpinometerMode, std::string> SpinometerModeNames = {
        {SpinometerMode::Average, "Average"},
        {SpinometerMode::SplitAverage, "Split Average"},
        {SpinometerMode::Highest, "Highest"}
    };

    typedef struct _SpinometerConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveMultiplier;
        int distance = 0;
        SpinometerMode mode = SpinometerMode::SplitAverage;
    } SpinometerConfig;
}
