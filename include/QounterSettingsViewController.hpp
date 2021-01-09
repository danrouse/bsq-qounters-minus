#pragma once

#include "config.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus, QounterSettingsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_METHOD(DidActivate);
    )

    public:
        static void Register();
)
