#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "util/note_count.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ScoreUIController.hpp"
#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/PlayerLevelStatsData.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "UnityEngine/Resources.hpp"

namespace QountersMinus {
    enum class PBQounterMode {
        Absolute,
        Relative
    };
    static int PBQounterModeCount = 2;
    static std::unordered_map<int, std::string> PBQounterModeNames = {
        {static_cast<int>(PBQounterMode::Absolute), "Absolute"},
        {static_cast<int>(PBQounterMode::Relative), "Relative"}
    };
    static std::unordered_map<std::string, int> PBQounterModeLookup = {
        {"Absolute", static_cast<int>(PBQounterMode::Absolute)},
        {"Relative", static_cast<int>(PBQounterMode::Relative)}
    };
}

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, PBQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static int Mode;
    static UnityEngine::Color BetterColor;
    static UnityEngine::Color DefaultColor;
    static int DecimalPrecision;
    static int TextSize;
    static bool UnderScore;
    static bool HideFirstScore;

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, pbText);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, maxPossibleScore, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, highScore, 0);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnScoreUpdated, int modifiedScore);
    DECLARE_INSTANCE_METHOD(void, SetPersonalBest, float ratioOfMaxScore);
)
