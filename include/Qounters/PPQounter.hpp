#pragma once

#include "util/logger.hpp"
#include "util/song_id.hpp"
#include "util/pp.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, PPQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static bool HideWhenUnranked;

    DECLARE_INSTANCE_FIELD(bool, isRanked);
    DECLARE_INSTANCE_FIELD(float, maxPP);
    DECLARE_INSTANCE_FIELD(float, multiplier);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnScoreUpdated, int modifiedScore);
)
