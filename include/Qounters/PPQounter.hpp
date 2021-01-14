#pragma once

#include "util/logger.hpp"
#include "Qounter.hpp"
#include "config/PPQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/RelativeScoreAndImmediateRankCounter.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, PPQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RelativeScoreAndImmediateRankCounter*, relativeScoreAndImmediateRankCounter);
    DECLARE_INSTANCE_FIELD(bool, isRanked);

    DECLARE_INSTANCE_FIELD(bool, hideWhenUnranked);

    DECLARE_METHOD(void, OnScoreUpdated, int modifiedScore);

    REGISTER_FUNCTION(PPQounter,
        REGISTER_FIELD(relativeScoreAndImmediateRankCounter);
        REGISTER_FIELD(isRanked);

        REGISTER_FIELD(hideWhenUnranked);

        REGISTER_METHOD(OnScoreUpdated);
    )

    public:
        void Configure(QountersMinus::PPQounterConfig config);
)
