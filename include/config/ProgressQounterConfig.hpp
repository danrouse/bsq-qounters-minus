#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    enum class ProgressQounterMode {
        Original,
        BaseGame,
        TimeInBeats,
        Percent
    };
    static int ProgressQounterModeCount = 4;
    static std::map<ProgressQounterMode, std::string> ProgressQounterModeNames = {
        {ProgressQounterMode::Original, "Original"},
        {ProgressQounterMode::BaseGame, "Base Game"},
        {ProgressQounterMode::TimeInBeats, "Time in Beats"},
        {ProgressQounterMode::Percent, "Percentage"}
    };
    static std::map<std::string, ProgressQounterMode> ProgressQounterModeLookup = {
        {"Original", ProgressQounterMode::Original},
        {"BaseGame", ProgressQounterMode::BaseGame},
        {"TimeInBeats", ProgressQounterMode::TimeInBeats},
        {"Percent", ProgressQounterMode::Percent}
    };

    typedef struct _ProgressQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowEnergy;
        bool enabled = true;
        int distance = 0;
        ProgressQounterMode mode = ProgressQounterMode::Original;
        bool progressTimeLeft = false;
        bool includeRing = false;
    } ProgressQounterConfig;
}
