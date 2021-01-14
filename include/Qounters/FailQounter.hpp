#pragma once

#include "util/logger.hpp"
#include "Qounter.hpp"
#include "config/FailQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerAllOverallStatsData.hpp"
#include "GlobalNamespace/PlayerAllOverallStatsData_PlayerOverallStatsData.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Time.hpp"
#include "System/Action.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, FailQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(Il2CppString*, prevBeatmapHash);
    DECLARE_STATIC_FIELD(int, restarts);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, count, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, animationTimer, 10.0f);

    DECLARE_INSTANCE_FIELD(bool, showRestartsInstead);

    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(FailQounter,
        REGISTER_FIELD(prevBeatmapHash);
        REGISTER_FIELD(restarts);
        REGISTER_FIELD(count);

        REGISTER_FIELD(showRestartsInstead);

        REGISTER_METHOD(Update);
    )

    public:
        void Configure(QountersMinus::FailQounterConfig config);
)
