#include "components/SettingsFlowCoordinator.hpp"
#include "components/QounterSettingsViewController.hpp"

DEFINE_CLASS(QountersMinus::SettingsFlowCoordinator);

static bool isTutorialSceneForceUnloaded = false;

void DisableAllNonImportantObjects(UnityEngine::Transform* original, UnityEngine::Transform* source, std::set<std::string> importantObjects) {
    for (int i = 0; i < source->get_childCount(); i++) {
        auto child = source->GetChild(i);
        if (importantObjects.contains(to_utf8(csstrtostr(child->get_name())))) {
            auto loopback = child;
            while (loopback != original) {
                loopback->get_gameObject()->SetActive(true);
                loopback = loopback->get_parent();
            }
        } else {
            child->get_gameObject()->SetActive(false);
            DisableAllNonImportantObjects(original, child, importantObjects);
        }
    }
}

void LoadTutorialScene() {
    isTutorialSceneForceUnloaded = false;
    auto gameScenesManager = UnityEngine::Object::FindObjectOfType<GlobalNamespace::GameScenesManager*>();
    gameScenesManager->neverUnloadScenes->Add(il2cpp_utils::createcsstr("MenuViewControllers"));
    gameScenesManager->neverUnloadScenes->Add(il2cpp_utils::createcsstr("MenuCore"));
    gameScenesManager->neverUnloadScenes->Add(il2cpp_utils::createcsstr("MainMenu"));

    auto menuTransitionsHelper = UnityEngine::Object::FindObjectOfType<GlobalNamespace::MenuTransitionsHelper*>();
    menuTransitionsHelper->tutorialScenesTransitionSetupData->Init();

    gameScenesManager->PushScenes(menuTransitionsHelper->tutorialScenesTransitionSetupData, 0.0f, nullptr, il2cpp_utils::MakeDelegate<SceneTransitionDelegate>(
        classof(SceneTransitionDelegate), gameScenesManager, +[](GlobalNamespace::GameScenesManager* gameScenesManager, Zenject::DiContainer* diContainer) {
            auto tutorialTransform = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("TutorialGameplay"))->get_transform();
            // if (mainSettings.screenDisplacementEffectsEnabled) menuShockwave.gameObject.SetActive(false);
            UnityEngine::Object::FindObjectOfType<GlobalNamespace::SongPreviewPlayer*>()->CrossfadeToDefault();
            // UnityEngine::Object::FindObjectOfType<VRUIControls::VRInputModule*>()->get_gameObject()->SetActive(false);
            DisableAllNonImportantObjects(tutorialTransform, tutorialTransform, {
                "EventSystem",
                "ControllerLeft",
                "ControllerRight"
            });
        }
    ));
}

void ResetSceneAfterUnload(GlobalNamespace::GameScenesManager* gameScenesManager, Zenject::DiContainer* diContainer) {
    gameScenesManager->neverUnloadScenes->Remove(il2cpp_utils::createcsstr("MenuViewControllers"));
    gameScenesManager->neverUnloadScenes->Remove(il2cpp_utils::createcsstr("MenuCore"));
    gameScenesManager->neverUnloadScenes->Remove(il2cpp_utils::createcsstr("MainMenu"));
    isTutorialSceneForceUnloaded = true;

    UnityEngine::Object::FindObjectOfType<GlobalNamespace::FadeInOutController*>()->FadeIn();
    UnityEngine::Object::FindObjectOfType<GlobalNamespace::SongPreviewPlayer*>()->CrossfadeToDefault();
}

void UnloadTutorialScene(GlobalNamespace::GameScenesManager* gameScenesManager, SceneTransitionDelegate onUnload) {
    // if (mainSettings.screenDisplacementEffectsEnabled) menuShockwave.gameObject.SetActive(true);
    // UnityEngine::Object::FindObjectOfType<VRUIControls::VRInputModule*>()->get_gameObject()->SetActive(true);
    gameScenesManager->PopScenes(0.0f, nullptr, onUnload);
}

void QountersMinus::SettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (addedToHierarchy) LoadTutorialScene();

    if (firstActivation) {
        SetTitle(il2cpp_utils::createcsstr("Wake me up inside (save me)"), HMUI::ViewController::AnimationType::Out);
        showBackButton = true;
        auto dummyViewController = QuestUI::BeatSaberUI::CreateViewController();
        auto mainViewController = QuestUI::BeatSaberUI::CreateViewController<QountersMinus::QounterSettingsViewController*>();
        auto buttonsViewController = QuestUI::BeatSaberUI::CreateViewController<QountersMinus::SettingsButtonsViewController*>();
        ProvideInitialViewControllers(dummyViewController, nullptr, mainViewController, buttonsViewController, nullptr);
    }
}

void QountersMinus::SettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    // if (ActiveViewController != ModSettingsButtonsViewController) {
    //     SetTitle(il2cpp_utils::createcsstr("Mod Settings"), ViewController::AnimationType::Out);
    //     ReplaceTopViewController(ModSettingsButtonsViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);
    //     ActiveViewController = ModSettingsButtonsViewController;
    // } else {
    auto gameScenesManager = UnityEngine::Object::FindObjectOfType<GlobalNamespace::GameScenesManager*>();
    UnloadTutorialScene(gameScenesManager, il2cpp_utils::MakeDelegate<SceneTransitionDelegate>(
        classof(SceneTransitionDelegate), gameScenesManager, ResetSceneAfterUnload
    ));
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    // }
}
