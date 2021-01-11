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
    static std::map<std::string, SpeedQounterMode> SpeedQounterModeLookup = {
        {"Average", SpeedQounterMode::Average},
        {"Top5Sec", SpeedQounterMode::Top5Sec},
        {"Both", SpeedQounterMode::Both},
        {"SplitAverage", SpeedQounterMode::SplitAverage},
        {"SplitBoth", SpeedQounterMode::SplitBoth}
    };

    typedef struct _SpeedQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowMultiplier;
        int distance = 2;
        SpeedQounterMode mode = SpeedQounterMode::Average;
        bool separateCutValues = true;
        int decimalPrecision = 2;
    } SpeedQounterConfig;
}
