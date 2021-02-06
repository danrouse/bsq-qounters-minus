#pragma once

#include "util/logger.hpp"
#include "util/color_picker_button.hpp"
#include "config.hpp"
#include "QounterRegistry.hpp"
#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "VRUIControls/VRInputModule.hpp"
#include "System/Reflection/Pointer.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include <set>

DECLARE_CLASS_CODEGEN(QountersMinus, QounterSettingsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, currentView);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    // DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_FIELD(currentView);
        REGISTER_METHOD(DidActivate);
        // REGISTER_METHOD(DidDeactivate);
    )

    public:
    UnityEngine::GameObject* ReplaceQounterConfig(
        std::string title,
        std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata
    );
)

void UpdateDummy(std::pair<std::string, std::string> key);
