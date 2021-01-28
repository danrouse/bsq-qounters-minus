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
#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/FadeInOutController.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "VRUIControls/VRInputModule.hpp"
#include "System/Reflection/Pointer.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "System/Action_1.hpp"
#include "Zenject/DiContainer.hpp"
#include <set>

typedef System::Action_1<Zenject::DiContainer*>* SceneTransitionDelegate;

struct NavigationButtonContext : Il2CppObject {
    UnityEngine::Transform* parent;
    std::string title;
    std::string _namespace;
    std::string _class;
    std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata;
};

DECLARE_CLASS_CODEGEN(QountersMinus, QounterSettingsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
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

void UpdateDummy(std::pair<std::string, std::string> key);
