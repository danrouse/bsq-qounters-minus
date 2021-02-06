#pragma once

#include "util/logger.hpp"
#include "custom-types/shared/macros.hpp"
#include "components/SettingsButtonsViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "GlobalNamespace/FadeInOutController.hpp"
#include "System/Action_1.hpp"
#include "Zenject/DiContainer.hpp"

typedef System::Action_1<Zenject::DiContainer*>* SceneTransitionDelegate;

DECLARE_CLASS_CODEGEN(QountersMinus, SettingsFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(QounterSettingsViewController,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)
