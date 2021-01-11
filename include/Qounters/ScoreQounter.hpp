#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "Qounter.hpp"
#include "config/ScoreQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "GlobalNamespace/ScoreUIController.hpp"
#include "GlobalNamespace/ImmediateRankUIPanel.hpp"
#include "GlobalNamespace/RankModel.hpp"
#include "GlobalNamespace/RankModel_Rank.hpp"
#include "GlobalNamespace/RelativeScoreAndImmediateRankCounter.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ScoreQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rankText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, relativeScoreText);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RelativeScoreAndImmediateRankCounter*, relativeScoreAndImmediateRankCounter);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RankModel::Rank, prevImmediateRank);

    DECLARE_INSTANCE_FIELD(int, mode);
    DECLARE_INSTANCE_FIELD(bool, customRankColors);
    DECLARE_INSTANCE_FIELD(int, decimalPrecision);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, ssColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, sColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, aColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, bColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, cColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, dColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, eColor);

    DECLARE_METHOD(void, UpdateText);
    DECLARE_METHOD(UnityEngine::Color, GetRankColor, GlobalNamespace::RankModel::Rank);

    REGISTER_FUNCTION(ScoreQounter,
        REGISTER_FIELD(rankText);
        REGISTER_FIELD(relativeScoreText);
        REGISTER_FIELD(relativeScoreAndImmediateRankCounter);
        REGISTER_FIELD(prevImmediateRank);

        REGISTER_FIELD(mode);
        REGISTER_FIELD(customRankColors);
        REGISTER_FIELD(decimalPrecision);
        REGISTER_FIELD(ssColor);
        REGISTER_FIELD(sColor);
        REGISTER_FIELD(aColor);
        REGISTER_FIELD(bColor);
        REGISTER_FIELD(cColor);
        REGISTER_FIELD(dColor);
        REGISTER_FIELD(eColor);

        REGISTER_METHOD(UpdateText);
        REGISTER_METHOD(GetRankColor);
    )

    public:
        void Configure(QountersMinus::ScoreQounterConfig config);
)
