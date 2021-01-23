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
#include "System/Reflection/Pointer.hpp"

struct NavigationButtonContext : Il2CppObject {
    UnityEngine::Transform* parent;
    std::string title;
    std::string _namespace;
    std::string _class;
    std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata;
};

DECLARE_CLASS_CODEGEN(QountersMinus, QounterSettingsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_METHOD(DidActivate);
    )

    public:
    static UnityEngine::GameObject* CreateQounterConfigView(
        UnityEngine::Transform* parent,
        std::string title,
        std::string namespaze,
        std::string klass,
        std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata
    );
)
