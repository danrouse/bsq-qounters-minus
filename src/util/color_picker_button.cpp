#include "util/color_picker_button.hpp"

UnityEngine::GameObject* CreateColorPickerButton(UnityEngine::Transform* parent, std::string text, UnityEngine::Color defaultColor, ColorChangeDelegate onChange) {
    // use QuestUI toggle as starting point to make positioning and sizing easier
    auto fakeToggle = QuestUI::BeatSaberUI::CreateToggle(parent, text, nullptr);
    auto gameObject = fakeToggle->get_transform()->get_parent()->get_gameObject();
    UnityEngine::Object::Destroy(fakeToggle->get_gameObject());

    // create element that gets toggled to contain the actual picker
    auto pickerModalGO = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("QountersMinusColorPickerModal"));
    auto pickerModalGORect = pickerModalGO->AddComponent<UnityEngine::RectTransform*>();
    pickerModalGORect->set_anchorMin(UnityEngine::Vector2(1.0f, 1.0f));
    pickerModalGORect->set_anchorMax(UnityEngine::Vector2(1.0f, 1.0f));
    pickerModalGORect->set_sizeDelta(UnityEngine::Vector2(40.0f, 40.0f));
    pickerModalGO->get_transform()->SetParent(parent, false);
    pickerModalGO->SetActive(false);

    // extra close button other than re-clicking the color button
    // auto closeButton = QuestUI::BeatSaberUI::CreateUIButton(gameObject->get_transform(), "Close", "PracticeButton", UnityEngine::Vector2(15.0f, -0.5f), il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
    //     classof(UnityEngine::Events::UnityAction*), pickerModalGO, +[](UnityEngine::GameObject* pickerModalGO) {
    //         pickerModalGO->SetActive(false);
    //     }
    // ));
    // closeButton->get_gameObject()->SetActive(false);

    // initialize the color button that toggles the picker open
    static auto colorPickerButtonControllers = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::ColorPickerButtonController*>();
    static auto buttonBase = colorPickerButtonControllers->values[0]->get_gameObject();
    auto buttonGO = UnityEngine::Object::Instantiate(buttonBase, gameObject->get_transform(), false);
    auto buttonRect = buttonGO->GetComponent<UnityEngine::RectTransform*>();
    buttonRect->set_anchorMin(UnityEngine::Vector2(1.0f, 0.5f));
    buttonRect->set_anchorMax(UnityEngine::Vector2(1.0f, 0.5f));
    buttonRect->set_anchoredPosition(UnityEngine::Vector2(-1.0f, -0.5f));
    buttonRect->set_pivot(UnityEngine::Vector2(1.0f, 0.5f));
    auto colorPickerButtonController = buttonGO->GetComponent<GlobalNamespace::ColorPickerButtonController*>();
    colorPickerButtonController->SetColor(defaultColor);

    // initialize the picker itself
    static auto hsvColorPickers = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::HSVPanelController*>();
    static auto pickerBase = hsvColorPickers->values[0]->get_gameObject();
    auto pickerGO = UnityEngine::Object::Instantiate(pickerBase, pickerModalGO->get_transform(), false);
    auto hsvPanelController = pickerGO->GetComponent<GlobalNamespace::HSVPanelController*>();
    UnityEngine::Object::Destroy(pickerGO->get_transform()->Find(il2cpp_utils::createcsstr("ColorPickerButtonPrimary"))->get_gameObject());
    auto pickerRect = pickerGO->GetComponent<UnityEngine::RectTransform*>();
    pickerRect->set_pivot(UnityEngine::Vector2(0.25f, 0.77f));
    pickerRect->set_localScale(UnityEngine::Vector3(0.75f, 0.75f, 0.75f));

    // event bindings
    hsvPanelController->add_colorDidChangeEvent(il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), colorPickerButtonController, +[](GlobalNamespace::ColorPickerButtonController* buttonController, UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType eventType) {
            buttonController->SetColor(color);
        })
    );
    hsvPanelController->add_colorDidChangeEvent(onChange);
    colorPickerButtonController->button->get_onClick()->AddListener(il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
        classof(UnityEngine::Events::UnityAction*), pickerModalGO, +[](UnityEngine::GameObject* pickerModalGO) {
            pickerModalGO->SetActive(!pickerModalGO->get_activeSelf());
        }
    ));

    return buttonGO;
}
