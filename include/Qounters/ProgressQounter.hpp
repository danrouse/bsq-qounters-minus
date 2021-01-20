#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"

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
    static std::map<ProgressQounterMode, std::string> ProgressQounterModeNames = {
        {ProgressQounterMode::Original, "Original"},
        {ProgressQounterMode::BaseGame, "Base Game"},
        {ProgressQounterMode::TimeInBeats, "Time in Beats"},
        {ProgressQounterMode::Percent, "Percentage"}
    };
    static std::map<std::string, ProgressQounterMode> ProgressQounterModeLookup = {
        {"Original", ProgressQounterMode::Original},
        {"BaseGame", ProgressQounterMode::BaseGame},
        {"TimeInBeats", ProgressQounterMode::TimeInBeats},
        {"Percent", ProgressQounterMode::Percent}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, ProgressQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(int, Distance);
    DECLARE_STATIC_FIELD(int, Mode);
    DECLARE_STATIC_FIELD(bool, ProgressTimeLeft);
    DECLARE_STATIC_FIELD(bool, IncludeRing);

    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, progressRing);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, length, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, songBPM, 0.0f);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::AudioTimeSyncController*, audioTimeSyncController);

    DECLARE_METHOD(static Qounter*, Initialize);
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

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
