#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "util/note_count.hpp"
#include "components/Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ColorType.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, NotesLeftQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(bool, LabelAboveCount);

    DECLARE_INSTANCE_FIELD_DEFAULT(int, notesLeft, 0);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(NotesLeftQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(LabelAboveCount);

        REGISTER_FIELD(notesLeft);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )
)
