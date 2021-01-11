#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "note_count.hpp"
#include "Qounter.hpp"
#include "config/NotesLeftQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ColorType.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, NotesLeftQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD_DEFAULT(int, notesLeft, 0);

    DECLARE_INSTANCE_FIELD(bool, labelAboveCount);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(NotesLeftQounter,
        REGISTER_FIELD(notesLeft);

        REGISTER_FIELD(labelAboveCount);

        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )

    public:
        void Configure(QountersMinus::NotesLeftQounterConfig config);
)
