#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "Qounter.hpp"
#include "config/ProgressQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Sprite.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ProgressQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, timeText);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, progressRing);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, length, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, songBPM, 0.0f);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);

    DECLARE_INSTANCE_FIELD(int, mode);
    DECLARE_INSTANCE_FIELD(bool, progressTimeLeft);
    DECLARE_INSTANCE_FIELD(bool, includeRing);

    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(ProgressQounter,
        REGISTER_FIELD(timeText);
        REGISTER_FIELD(progressRing);
        REGISTER_FIELD(length);
        REGISTER_FIELD(songBPM);
        REGISTER_FIELD(audioTimeSyncController);

        REGISTER_FIELD(mode);
        REGISTER_FIELD(progressTimeLeft);
        REGISTER_FIELD(includeRing);

        REGISTER_METHOD(Update);
    )

    public:
        void Configure(QountersMinus::ProgressQounterConfig config);
)
