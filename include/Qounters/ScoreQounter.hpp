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

    DECLARE_METHOD(void, UpdateText);

    REGISTER_FUNCTION(ScoreQounter,
        REGISTER_FIELD(rankText);
        REGISTER_FIELD(relativeScoreText);
        REGISTER_FIELD(relativeScoreAndImmediateRankCounter);
        REGISTER_FIELD(prevImmediateRank);

        REGISTER_FIELD(mode);
        REGISTER_FIELD(customRankColors);

        REGISTER_METHOD(UpdateText);
    )

    public:
        void Configure(QountersMinus::ScoreQounterConfig config);
)
