#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/ScoreQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreUIController.hpp"
#include "GlobalNamespace/ImmediateRankUIPanel.hpp"
#include "GlobalNamespace/RankModel.hpp"
#include "GlobalNamespace/RankModel_Rank.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ScoreQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rankText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, relativeScoreText);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RankModel::Rank, prevImmediateRank);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, UpdateText);
    DECLARE_METHOD(UnityEngine::Color, GetRankColor, GlobalNamespace::RankModel::Rank);

    REGISTER_FUNCTION(ScoreQounter,
        REGISTER_FIELD(rankText);
        REGISTER_FIELD(relativeScoreText);
        REGISTER_FIELD(prevImmediateRank);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(UpdateText);
        REGISTER_METHOD(GetRankColor);
    )
)
