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
    static std::map<int, std::string> ProgressQounterModeNames = {
        {static_cast<int>(ProgressQounterMode::Original), "Original"},
        {static_cast<int>(ProgressQounterMode::BaseGame), "Base Game"},
        {static_cast<int>(ProgressQounterMode::TimeInBeats), "Time in Beats"},
        {static_cast<int>(ProgressQounterMode::Percent), "Percentage"}
    };
    static std::map<std::string, int> ProgressQounterModeLookup = {
        {"Original", static_cast<int>(ProgressQounterMode::Original)},
        {"BaseGame", static_cast<int>(ProgressQounterMode::BaseGame)},
        {"TimeInBeats", static_cast<int>(ProgressQounterMode::TimeInBeats)},
        {"Percent", static_cast<int>(ProgressQounterMode::Percent)}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ProgressQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(int, Mode);
    DECLARE_STATIC_FIELD(bool, ProgressTimeLeft);
    DECLARE_STATIC_FIELD(bool, IncludeRing);

    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, progressRing);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, length, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, songBPM, 0.0f);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(ProgressQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(Mode);
        REGISTER_FIELD(ProgressTimeLeft);
        REGISTER_FIELD(IncludeRing);

        REGISTER_FIELD(progressRing);
        REGISTER_FIELD(length);
        REGISTER_FIELD(songBPM);
        REGISTER_FIELD(audioTimeSyncController);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
