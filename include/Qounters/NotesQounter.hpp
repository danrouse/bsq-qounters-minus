#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "config/NotesQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ColorType.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, NotesQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD_DEFAULT(int, allCuts, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, goodCuts, 0);

    DECLARE_INSTANCE_FIELD(bool, showPercentage);
    DECLARE_INSTANCE_FIELD(int, decimalPrecision);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(NotesQounter,
        REGISTER_FIELD(allCuts);
        REGISTER_FIELD(goodCuts);

        REGISTER_FIELD(showPercentage);
        REGISTER_FIELD(decimalPrecision);

        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )

    public:
        void Configure(QountersMinus::NotesQounterConfig config);
)
