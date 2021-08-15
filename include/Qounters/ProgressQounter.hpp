#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/SongProgressUIController.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Sprite.hpp"
#include "HMUI/ImageView.hpp"

namespace QountersMinus {
    enum class ProgressQounterMode {
        Original,
        BaseGame,
        TimeInBeats,
        Percent
    };
    static int ProgressQounterModeCount = 4;
    static std::unordered_map<int, std::string> ProgressQounterModeNames = {
        {static_cast<int>(ProgressQounterMode::Original), "Original"},
        {static_cast<int>(ProgressQounterMode::BaseGame), "Base Game"},
        {static_cast<int>(ProgressQounterMode::TimeInBeats), "Time in Beats"},
        {static_cast<int>(ProgressQounterMode::Percent), "Percentage"}
    };
    static std::unordered_map<std::string, int> ProgressQounterModeLookup = {
        {"Original", static_cast<int>(ProgressQounterMode::Original)},
        {"BaseGame", static_cast<int>(ProgressQounterMode::BaseGame)},
        {"TimeInBeats", static_cast<int>(ProgressQounterMode::TimeInBeats)},
        {"Percent", static_cast<int>(ProgressQounterMode::Percent)}
    };
}

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, ProgressQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static int Mode;
    static bool ProgressTimeLeft;
    static bool IncludeRing;

    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, progressRing);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, length, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, songBPM, 0.0f);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, Update);
)
