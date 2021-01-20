#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"

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
        LeavePoints,
        ScoreOnly,
        RankOnly
    };
    static int ScoreQounterModeCount = 4;
    static std::map<ScoreQounterMode, std::string> ScoreQounterModeNames = {
        {ScoreQounterMode::Original, "Original"},
        {ScoreQounterMode::LeavePoints, "Don't Move Points"},
        {ScoreQounterMode::ScoreOnly, "Remove Rank"},
        {ScoreQounterMode::RankOnly, "Remove Percentage"}
    };
    static std::map<std::string, ScoreQounterMode> ScoreQounterModeLookup = {
        {"Original", ScoreQounterMode::Original},
        {"LeavePoints", ScoreQounterMode::LeavePoints},
        {"ScoreOnly", ScoreQounterMode::ScoreOnly},
        {"RankOnly", ScoreQounterMode::RankOnly}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ScoreQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(int, Distance);
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

    DECLARE_METHOD(static Qounter*, Initialize);
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

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(UpdateText);
        REGISTER_METHOD(GetRankColor);
    )
)
