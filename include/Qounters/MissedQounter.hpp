#pragma once

#include "logger.hpp"
#include "Qounter.hpp"
#include "config/MissedQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ColorType.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, MissedQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, missText);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, misses, 0);

    DECLARE_INSTANCE_FIELD(bool, countBadCuts);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, OnNoteMiss, GlobalNamespace::NoteData* data);
    DECLARE_METHOD(void, UpdateValue);

    REGISTER_FUNCTION(MissedQounter,
        REGISTER_FIELD(missText);
        REGISTER_FIELD(misses);

        REGISTER_FIELD(countBadCuts);

        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
        REGISTER_METHOD(UpdateValue);
    )

    public:
        void Configure(QountersMinus::MissedQounterConfig config);
)