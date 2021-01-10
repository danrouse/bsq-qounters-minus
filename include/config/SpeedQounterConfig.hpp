#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    enum class SpeedQounterMode {
        Average,
        Top5Sec,
        Both,
        SplitAverage,
        SplitBoth
    };

    static int SpeedQounterModeCount = 5;
    static std::map<SpeedQounterMode, std::string> SpeedQounterModeNames = {
        {SpeedQounterMode::Average, "Average"},
        {SpeedQounterMode::Top5Sec, "Top from 5 Seconds"},
        {SpeedQounterMode::Both, "Both Metrics"},
        {SpeedQounterMode::SplitAverage, "Split Average"},
        {SpeedQounterMode::SplitBoth, "Split Both Metrics"}
    };

    typedef struct _SpeedQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowMultiplier;

        SpeedQounterMode mode = SpeedQounterMode::Average;
        bool separateCutValues = true;
        int decimalPrecision = 2;
    } SpeedQounterConfig;
}
