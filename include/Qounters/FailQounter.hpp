#pragma once

#include "util/logger.hpp"
#include "util/current_song_id.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/FailQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerAllOverallStatsData.hpp"
#include "GlobalNamespace/PlayerAllOverallStatsData_PlayerOverallStatsData.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Time.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, FailQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(Il2CppString*, prevBeatmapHash);
    DECLARE_STATIC_FIELD(int, restarts);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, count, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, animationTimer, 10.0f);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(FailQounter,
        REGISTER_FIELD(prevBeatmapHash);
        REGISTER_FIELD(restarts);
        REGISTER_FIELD(count);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
