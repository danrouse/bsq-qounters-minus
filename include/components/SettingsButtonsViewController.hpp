#pragma once

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "QounterRegistry.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/Events/UnityAction.hpp"

struct NavigationButtonContext : Il2CppObject {
    UnityEngine::Transform* parent;
    std::string title;
    std::string _namespace;
    std::string _class;
    std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata;
};

DECLARE_CLASS_CODEGEN(QountersMinus, SettingsButtonsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, targetViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    REGISTER_FUNCTION(SettingsButtonsViewController,
        REGISTER_FIELD(targetViewController);
        REGISTER_METHOD(DidActivate);
    )
)
