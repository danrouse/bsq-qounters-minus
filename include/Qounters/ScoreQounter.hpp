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
    static std::map<int, std::string> ScoreQounterModeNames = {
        {static_cast<int>(ScoreQounterMode::Original), "Original"},
        {static_cast<int>(ScoreQounterMode::ScoreOnly), "Remove Rank"},
        {static_cast<int>(ScoreQounterMode::RankOnly), "Remove Percentage"},
        {static_cast<int>(ScoreQounterMode::RemoveScore), "Remove Score"},
    };
    static std::map<std::string, int> ScoreQounterModeLookup = {
        {"Original", static_cast<int>(ScoreQounterMode::Original)},
        {"LeavePoints", static_cast<int>(ScoreQounterMode::Original)}, // leave reference to convert from pc config
        {"ScoreOnly", static_cast<int>(ScoreQounterMode::ScoreOnly)},
        {"RankOnly", static_cast<int>(ScoreQounterMode::RankOnly)},
        {"RemoveScore", static_cast<int>(ScoreQounterMode::RemoveScore)}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ScoreQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(int, Mode);
    DECLARE_STATIC_FIELD(int, DecimalPrecision);
    DECLARE_STATIC_FIELD(bool, DisplayRank); // unused?
    DECLARE_STATIC_FIELD(bool, CustomRankColors);
    DECLARE_STATIC_FIELD(UnityEngine::Color, SSColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, SColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, AColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, BColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, CColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, DColor);
    DECLARE_STATIC_FIELD(UnityEngine::Color, EColor);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rankText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, relativeScoreText);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RankModel::Rank, prevImmediateRank);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, UpdateText);
    DECLARE_METHOD(UnityEngine::Color, GetRankColor, GlobalNamespace::RankModel::Rank);

    REGISTER_FUNCTION(ScoreQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(Mode);
        REGISTER_FIELD(DecimalPrecision);
        REGISTER_FIELD(DisplayRank);
        REGISTER_FIELD(CustomRankColors);
        REGISTER_FIELD(SSColor);
        REGISTER_FIELD(SColor);
        REGISTER_FIELD(AColor);
        REGISTER_FIELD(BColor);
        REGISTER_FIELD(CColor);
        REGISTER_FIELD(DColor);
        REGISTER_FIELD(EColor);

        REGISTER_FIELD(rankText);
        REGISTER_FIELD(relativeScoreText);
        REGISTER_FIELD(prevImmediateRank);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(UpdateText);
        REGISTER_METHOD(GetRankColor);
    )
)
