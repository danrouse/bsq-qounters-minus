#pragma once

#include "util/logger.hpp"
#include "util/song_id.hpp"
#include "Qounter.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/PlayerAllOverallStatsData.hpp"
#include "GlobalNamespace/PlayerAllOverallStatsData_PlayerOverallStatsData.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Time.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, FailQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(int, Distance);
    DECLARE_STATIC_FIELD(bool, ShowRestartsInstead);

    DECLARE_STATIC_FIELD(Il2CppString*, prevBeatmapHash);
    DECLARE_STATIC_FIELD(int, restarts);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, count, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, animationTimer, 10.0f);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(FailQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(ShowRestartsInstead);

        REGISTER_FIELD(prevBeatmapHash);
        REGISTER_FIELD(restarts);
        REGISTER_FIELD(count);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
