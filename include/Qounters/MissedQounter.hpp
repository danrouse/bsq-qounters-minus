#pragma once

#include "util/logger.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/MissedQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ColorType.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, MissedQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD_DEFAULT(int, misses, 0);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(MissedQounter,
        REGISTER_FIELD(misses);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )
)
