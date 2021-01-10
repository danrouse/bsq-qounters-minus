#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "Qounter.hpp"
#include "config/NotesLeftQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/BeatmapData.hpp"
#include "GlobalNamespace/BeatmapLineData.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController_InitData.hpp"
#include "GlobalNamespace/BeatmapObjectData.hpp"
#include "GlobalNamespace/BeatmapObjectType.hpp"
#include "GlobalNamespace/ColorType.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, NotesLeftQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, notesLeftText);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, notesLeft, 0);

    DECLARE_INSTANCE_FIELD(bool, labelAboveCount);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(NotesLeftQounter,
        REGISTER_FIELD(notesLeftText);
        REGISTER_FIELD(notesLeft);

        REGISTER_FIELD(labelAboveCount);

        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )

    public:
        void Configure(QountersMinus::NotesLeftQounterConfig config);
)
