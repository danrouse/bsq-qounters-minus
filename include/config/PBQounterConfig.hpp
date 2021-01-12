#pragma once

#include "QounterConfig.hpp"
#include "UnityEngine/Color.hpp"

namespace QountersMinus {
    enum class PBQounterMode {
        Absolute,
        Relative
    };
    static int PBQounterModeCount = 2;
    static std::map<PBQounterMode, std::string> PBQounterModeNames = {
        {PBQounterMode::Absolute, "Absolute"},
        {PBQounterMode::Relative, "Relative"}
    };
    static std::map<std::string, PBQounterMode> PBQounterModeLookup = {
        {"Absolute", PBQounterMode::Absolute},
        {"Relative", PBQounterMode::Relative}
    };

    typedef struct _PBQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowMultiplier;
        bool enabled = true;
        int distance = 1;
        PBQounterMode mode = PBQounterMode::Absolute;
        UnityEngine::Color betterColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);
        UnityEngine::Color defaultColor = UnityEngine::Color(1.0f, 0.647f, 0.0f, 1.0f);
        int decimalPrecision = 2;
        int textSize = 2;
        bool underScore = true;
        bool hideFirstScore = false;
    } PBQounterConfig;
}
