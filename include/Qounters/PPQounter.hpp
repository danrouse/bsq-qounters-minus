#pragma once

#include "util/logger.hpp"
#include "util/song_id.hpp"
#include "util/pp.hpp"
#include "util/format.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/PPQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"


DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, PPQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(bool, isRanked);
    DECLARE_INSTANCE_FIELD(float, maxPP);
    DECLARE_INSTANCE_FIELD(float, multiplier);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnScoreUpdated, int modifiedScore);

    REGISTER_FUNCTION(PPQounter,
        REGISTER_FIELD(isRanked);
        REGISTER_FIELD(maxPP);
        REGISTER_FIELD(multiplier);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnScoreUpdated);
    )
)
