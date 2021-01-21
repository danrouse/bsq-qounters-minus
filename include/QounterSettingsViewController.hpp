#pragma once

#include "util/logger.hpp"
#include "config.hpp"
#include "QounterRegistry.hpp"
#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/Reflection/Pointer.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus, QounterSettingsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::GameObject*>*, containers);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_FIELD(containers);
        REGISTER_METHOD(DidActivate);
    )
)

UnityEngine::GameObject* CreateQounterConfigView(UnityEngine::Transform* parent, std::string title, std::string namespaze, std::string klass, std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata);
