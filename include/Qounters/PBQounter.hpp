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
    static std::map<int, std::string> PBQounterModeNames = {
        {static_cast<int>(PBQounterMode::Absolute), "Absolute"},
        {static_cast<int>(PBQounterMode::Relative), "Relative"}
    };
    static std::map<std::string, int> PBQounterModeLookup = {
        {"Absolute", static_cast<int>(PBQounterMode::Absolute)},
        {"Relative", static_cast<int>(PBQounterMode::Relative)}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, PBQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(int, Mode);
    DECLARE_STATIC_FIELD(UnityEngine::Color, BetterColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, DefaultColor);
    DECLARE_STATIC_FIELD(int, DecimalPrecision);
    DECLARE_STATIC_FIELD(int, TextSize);
    DECLARE_STATIC_FIELD(bool, UnderScore);
    DECLARE_STATIC_FIELD(bool, HideFirstScore);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, pbText);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, maxPossibleScore, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, highScore, 0);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnScoreUpdated, int modifiedScore);
    DECLARE_METHOD(void, SetPersonalBest, float ratioOfMaxScore);

    REGISTER_FUNCTION(PBQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(Mode);
        REGISTER_FIELD(BetterColor);
        REGISTER_FIELD(DefaultColor);
        REGISTER_FIELD(DecimalPrecision);
        REGISTER_FIELD(TextSize);
        REGISTER_FIELD(UnderScore);
        REGISTER_FIELD(HideFirstScore);

        REGISTER_FIELD(pbText);
        REGISTER_FIELD(maxPossibleScore);
        REGISTER_FIELD(highScore);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnScoreUpdated);
        REGISTER_METHOD(SetPersonalBest);
    )
)
