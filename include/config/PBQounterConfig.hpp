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

    typedef struct _PBQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowMultiplier;

        PBQounterMode mode = PBQounterMode::Absolute;
        int decimalPrecision = 2;
        int textSize = 2;
        bool underscore = true;
        bool hideFirstScore = false;

        UnityEngine::Color betterColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);
        UnityEngine::Color defaultColor = UnityEngine::Color(1.0f, 0.647f, 0.0f, 1.0f);
    } PBQounterConfig;
}
