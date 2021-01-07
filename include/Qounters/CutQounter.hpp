#pragma once

#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, CutQounter, QountersMinus::Qounter,
    DECLARE_OVERRIDE_METHOD(void, Awake, il2cpp_utils::FindMethodUnsafe("QountersMinus", "Qounter", "Awake", 0));
    DECLARE_OVERRIDE_METHOD(void, OnNoteCut, il2cpp_utils::FindMethodUnsafe("QountersMinus", "Qounter", "OnNoteCut", 2), GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_OVERRIDE_METHOD(void, OnNoteMiss, il2cpp_utils::FindMethodUnsafe("QountersMinus", "Qounter", "OnNoteMiss", 1), GlobalNamespace::NoteData* data);

    REGISTER_FUNCTION(CutQounter,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(OnNoteMiss);
    )
)
