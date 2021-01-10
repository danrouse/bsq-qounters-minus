#include "QounterSettingsViewController.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::QounterSettingsViewController);

#define CreateConfigToggle(configVar, label) \
    QuestUI::BeatSaberUI::CreateToggle(layout->get_transform(), label, configVar, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>( \
        classof(UnityEngine::Events::UnityAction_1<bool>*), this, +[](QountersMinus::QounterSettingsViewController* self, bool val) { \
            LOG_DEBUG("SET " + #configVar + " = %d", val); \
            configVar = val; \
            SaveConfig(); \
        } \
    ));

// #include "Polyglot/LocalizedTextMeshProUGUI.hpp"
// #include "HMUI/SimpleTextDropdown.hpp"
// #include "HMUI/DropdownWithTableView.hpp"
// #include "TMPro/TextMeshProUGUI.hpp"
// #include "questui/shared/ArrayUtil.hpp"
// #include "GlobalNamespace/NoteJumpStartBeatOffsetDropdown.hpp"
// #include "UnityEngine/Resources.hpp"
// #include "UnityEngine/Transform.hpp"
// #include "System/Action_2.hpp"

// HMUI::SimpleTextDropdown* CreateTextDropdown(
//     UnityEngine::Transform* parent,
//     std::string text,
//     std::vector<std::string> values,
//     int selectedIndex,
//     UnityEngine::Vector2 anchoredPosition,
//     System::Action_2<HMUI::DropdownWithTableView*, int>* onChange
// ) {
//     auto template = QuestUI::ArrayUtil::First(
//         QuestUI::ArrayUtil::Select<UnityEngine::GameObject*>(
//             UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::SimpleTextDropdown*>(),
//             [](HMUI::SimpleTextDropdown* x) { return x->get_transform()->get_parent()->get_gameObject(); }
//         ),
//         [](UnityEngine::GameObject* x) { return to_utf8(csstrtostr(x->get_name())) == "NJBSO"; }
//     );
//     auto gameObject = UnityEngine::Object::Instantiate(template, parent, false);
//     static auto name = il2cpp_utils::createcsstr("QountersMinusTextDropdown", il2cpp_utils::StringType::Manual);
//     gameObject->set_name(name);
//     gameObject->SetActive(false);

//     auto labelText = gameObject->get_transform()->Find(il2cpp_utils::createcsstr("Label"))->get_gameObject();
//     UnityEngine::Object::Destroy(labelText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());
//     TMPro::TextMeshProUGUI* textMesh = labelText->GetComponent<TMPro::TextMeshProUGUI*>();
//     textMesh->SetText(il2cpp_utils::createcsstr(text));
//     textMesh->set_richText(true);
    
//     UnityEngine::Object::Destroy(gameObject->GetComponentInChildren<GlobalNamespace::NoteJumpStartBeatOffsetDropdown*>());
//     auto dropdown = gameObject->GetComponentInChildren<HMUI::SimpleTextDropdown*>();
//     // toggle->set_interactable(true);
//     // toggle->set_isOn(currentValue);
//     // dropdown->

//     // toggle->onValueChanged = Toggle::ToggleEvent::New_ctor();
//     // if(onToggle)
//     //     toggle->onValueChanged->AddListener(onToggle);
    
//     auto rectTransform = gameObject->GetComponent<UnityEngine::RectTransform*>();
//     rectTransform->set_anchoredPosition(anchoredPosition);
//     // LayoutElement* layout = gameObject->GetComponent<LayoutElement*>();
//     // layout->set_preferredWidth(90.0f);
//     gameObject->SetActive(true);
//     return dropdown;
// }

#include "UnityEngine/RectOffset.hpp"
#include "logger.hpp"

void QountersMinus::QounterSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation || !addedToHierarchy) return;

    auto layout = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    // auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(scrollContainer->get_transform());
    // layout->set_spacing(0);
    // layout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    // layout->set_padding(UnityEngine::RectOffset::New_ctor(4, 4, 4, 4));

    // bool hideCombo = false;
    // bool hideMultiplier = false;
    // float comboOffset = 0.2f; // ?
    // float multiplierOffset = 0.4f; // ?
    // bool italicText = false;

    // Qounter-specific configuration [ALL-QOUNTERS]
    //============================================================//

    auto cutQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Cut Qounter");
    cutQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    cutQounterTitle->set_fontSize(6.0f);

    auto cutQounterEnabled = CreateConfigToggle(config.cutQounterConfig.enabled, "Enabled");
    auto cutQounterSeparateSaberCounts = CreateConfigToggle(config.cutQounterConfig.separateSaberCounts, "Separate Saber Counts");
    auto cutQounterSeparateCutValues = CreateConfigToggle(config.cutQounterConfig.separateCutValues, "Separate Cut Values");
    auto cutQounterAveragePrecision = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Average Precision", 0, 1.0f, config.cutQounterConfig.averagePrecision, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.cutQounterConfig.averagePrecision = %d", (int)val);
            config.cutQounterConfig.averagePrecision = (int)val;
            SaveConfig();
        }
    ));

    //============================================================//

    auto missQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Miss Qounter");
    missQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    missQounterTitle->set_fontSize(6.0f);
    
    auto missQounterEnabled = CreateConfigToggle(config.missQounterConfig.enabled, "Enabled");
    auto missQounterCountBadCuts = CreateConfigToggle(config.missQounterConfig.countBadCuts, "Count Bad Cuts");

    //============================================================//

    auto notesQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Notes Qounter");
    notesQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesQounterTitle->set_fontSize(6.0f);
    
    auto notesQounterEnabled = CreateConfigToggle(config.notesQounterConfig.enabled, "Enabled");
    auto notesQounterShowPercentage = CreateConfigToggle(config.notesQounterConfig.showPercentage, "Show Percentage");
    auto notesQounterDecimalPrecision = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Decimal Precision", 0, 1.0f, config.notesQounterConfig.decimalPrecision, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.notesQounterConfig.decimalPrecision = %d", (int)val);
            config.notesQounterConfig.decimalPrecision = (int)val;
            SaveConfig();
        }
    ));

    //============================================================//

    auto notesLeftQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Notes Left Qounter");
    notesLeftQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesLeftQounterTitle->set_fontSize(6.0f);
    
    auto notesLeftQounterEnabled = CreateConfigToggle(config.notesLeftQounterConfig.enabled, "Enabled");
    auto notesLeftQounterLabelAboveCount = CreateConfigToggle(config.notesLeftQounterConfig.labelAboveCount, "Label Above Count");

    //============================================================//

    auto spinometerTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Spinometer");
    spinometerTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    spinometerTitle->set_fontSize(6.0f);
    
    auto spinometerEnabled = CreateConfigToggle(config.spinometerConfig.enabled, "Enabled");
    // TODO: mode selector
    
}

void QountersMinus::QounterSettingsViewController::Register() {
    custom_types::Register::RegisterType<QountersMinus::QounterSettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
        (ModInfo){"Qounters-", VERSION}, "Qounters-"
    );
}
