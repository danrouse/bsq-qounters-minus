#pragma once

#include "questui/shared/BeatSaberUI.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "GlobalNamespace/ColorPickerButtonController.hpp"
#include "GlobalNamespace/HSVPanelController.hpp"
#include "GlobalNamespace/ColorChangeUIEventType.hpp"
#include "System/Action_2.hpp"

typedef System::Action_2<UnityEngine::Color, GlobalNamespace::ColorChangeUIEventType>* ColorChangeDelegate;

UnityEngine::GameObject* CreateColorPickerButton(UnityEngine::Transform* parent, std::string text, UnityEngine::Color defaultColor, ColorChangeDelegate onChange);
