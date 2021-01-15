#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/ProgressQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "GlobalNamespace/SongProgressUIController.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Sprite.hpp"
#include "HMUI/ImageView.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ProgressQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, progressRing);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, length, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, songBPM, 0.0f);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(ProgressQounter,
        REGISTER_FIELD(progressRing);
        REGISTER_FIELD(length);
        REGISTER_FIELD(songBPM);
        REGISTER_FIELD(audioTimeSyncController);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
