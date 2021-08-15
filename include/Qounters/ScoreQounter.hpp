#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreUIController.hpp"
#include "GlobalNamespace/ImmediateRankUIPanel.hpp"
#include "GlobalNamespace/RankModel.hpp"
#include "GlobalNamespace/RankModel_Rank.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "System/Action.hpp"

namespace QountersMinus {
    enum class ScoreQounterMode {
        Original,
        ScoreOnly,
        RankOnly,
        RemoveScore
    };
    static int ScoreQounterModeCount = 4;
    static std::unordered_map<int, std::string> ScoreQounterModeNames = {
        {static_cast<int>(ScoreQounterMode::Original), "Original"},
        {static_cast<int>(ScoreQounterMode::ScoreOnly), "Remove Rank"},
        {static_cast<int>(ScoreQounterMode::RankOnly), "Remove Percentage"},
        {static_cast<int>(ScoreQounterMode::RemoveScore), "Remove Score"},
    };
    static std::unordered_map<std::string, int> ScoreQounterModeLookup = {
        {"Original", static_cast<int>(ScoreQounterMode::Original)},
        {"LeavePoints", static_cast<int>(ScoreQounterMode::Original)}, // leave reference to convert from pc config
        {"ScoreOnly", static_cast<int>(ScoreQounterMode::ScoreOnly)},
        {"RankOnly", static_cast<int>(ScoreQounterMode::RankOnly)},
        {"RemoveScore", static_cast<int>(ScoreQounterMode::RemoveScore)}
    };
}

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, ScoreQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static int Mode;
    static int DecimalPrecision;
    static bool DisplayRank; // unused?
    static bool CustomRankColors;
    static UnityEngine::Color SSColor;
    static UnityEngine::Color SColor;
    static UnityEngine::Color AColor;
    static UnityEngine::Color BColor;
    static UnityEngine::Color CColor;
    static UnityEngine::Color DColor;
    static UnityEngine::Color EColor;

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rankText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, relativeScoreText);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RankModel::Rank, prevImmediateRank);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, UpdateText);
    DECLARE_INSTANCE_METHOD(UnityEngine::Color, GetRankColor, GlobalNamespace::RankModel::Rank);
)
