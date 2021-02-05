#pragma once

#include "util/logger.hpp"
#include "util/song_id.hpp"
#include "util/pp.hpp"
#include "util/format.hpp"
#include "components/Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, PPQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(bool, HideWhenUnranked);

    DECLARE_INSTANCE_FIELD(bool, isRanked);
    DECLARE_INSTANCE_FIELD(float, maxPP);
    DECLARE_INSTANCE_FIELD(float, multiplier);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnScoreUpdated, int modifiedScore);

    REGISTER_FUNCTION(PPQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(HideWhenUnranked);

        REGISTER_FIELD(isRanked);
        REGISTER_FIELD(maxPP);
        REGISTER_FIELD(multiplier);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnScoreUpdated);
    )
)
