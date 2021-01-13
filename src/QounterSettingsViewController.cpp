#include "QounterSettingsViewController.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::QounterSettingsViewController);

#define CreateConfigToggle(configVar, label) \
    QuestUI::BeatSaberUI::CreateToggle(self->layout->get_transform(), label, configVar, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>( \
        classof(UnityEngine::Events::UnityAction_1<bool>*), self, +[](QountersMinus::QounterSettingsViewController* self, bool val) { \
            LOG_DEBUG("SET " + #configVar + " = %d", val); \
            configVar = val; \
            QountersMinus::SaveConfig(); \
        } \
    ));

#define CreateConfigIntIncrement(configVar, label) \
    QuestUI::BeatSaberUI::CreateIncrementSetting(self->layout->get_transform(), label, 0, 1.0f, configVar, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>( \
        classof(UnityEngine::Events::UnityAction_1<float>*), self, +[](QountersMinus::QounterSettingsViewController* self, float val) { \
            LOG_DEBUG("SET " + #configVar + " = %d", (int)val); \
            configVar = (int)val; \
            QountersMinus::SaveConfig(); \
        } \
    ));

#define CreateConfigEnumIncrement(varName, configVar, label, enumType, enumCount, enumMap) \
   auto varName = QuestUI::BeatSaberUI::CreateIncrementSetting(self->layout->get_transform(), label, 0, 1.0f, (float)(int)configVar, UnityEngine::Vector2(0.0f, 0.0f), nullptr); \
   varName->OnValueChange = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>( \
        classof(UnityEngine::Events::UnityAction_1<float>*), varName, +[](QuestUI::IncrementSetting* self, float rawVal) { \
            auto intVal = (int)rawVal % enumCount; \
            if (intVal < 0) intVal = enumCount - (intVal * -1); \
            LOG_DEBUG("SET " + #configVar + " = %d", intVal); \
            configVar = static_cast<enumType>(intVal); \
            self->Text->SetText(il2cpp_utils::createcsstr(enumMap[configVar])); \
        } \
    ); \
    varName->Text->SetText(il2cpp_utils::createcsstr(enumMap[configVar]));

#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/ColorPickerButtonController.hpp"
#include "GlobalNamespace/HSVPanelController.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "GlobalNamespace/ColorChangeUIEventType.hpp"
#include "System/Action_2.hpp"
typedef System::Action_2<UnityEngine::Color, GlobalNamespace::ColorChangeUIEventType>* ColorChangeDelegate;
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

void HideChildren(QountersMinus::QounterSettingsViewController* self) {
    while (self->layout->get_transform()->get_childCount() > 0) {
        UnityEngine::GameObject::DestroyImmediate(self->layout->get_transform()->GetChild(0)->get_gameObject());
    }
}

void ShowMainConfig(QountersMinus::QounterSettingsViewController* self) {
    auto mainTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Qounters-");
    mainTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    mainTitle->set_fontSize(6.0f);

    auto globalEnabled = CreateConfigToggle(config.enabled, "Enabled");
    QuestUI::BeatSaberUI::AddHoverHint(globalEnabled->get_gameObject(), "Toggles Qounters-.");
    auto hideCombo = CreateConfigToggle(config.hideCombo, "Hide Combo");
    QuestUI::BeatSaberUI::AddHoverHint(hideCombo->get_gameObject(), "Hides the Combo counter.");
    auto hideMultiplier = CreateConfigToggle(config.hideMultiplier, "Hide Multiplier");
    QuestUI::BeatSaberUI::AddHoverHint(hideMultiplier->get_gameObject(), "Hides the Multiplier.");
    auto italicText = CreateConfigToggle(config.italicText, "Use Italic Text");
    QuestUI::BeatSaberUI::AddHoverHint(italicText->get_gameObject(), "Text elements will be italicized to match the base game.");
    auto comboOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(self->layout->get_transform(), "Combo Offset", 1, 0.1f, config.comboOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), self, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.comboOffset = %.2f", val);
            config.comboOffset = val;
            QountersMinus::SaveConfig();
        }
    ));
    QuestUI::BeatSaberUI::AddHoverHint(comboOffset->get_gameObject(), "Applies additional offset to qounters situated above or below the Combo.");
    auto multiplierOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(self->layout->get_transform(), "Multiplier Offset", 1, 0.1f, config.multiplierOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), self, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.multiplierOffset = %.2f", val);
            config.multiplierOffset = val;
            QountersMinus::SaveConfig();
        }
    ));
    QuestUI::BeatSaberUI::AddHoverHint(multiplierOffset->get_gameObject(), "Applies additional offset to qounters situated above or below the Multiplier.");
}

//============================================================//
// Qounter-specific configuration [ALL-QOUNTERS]
//============================================================//
void ShowCutQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto cutQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Cut Qounter");
    cutQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    cutQounterTitle->set_fontSize(6.0f);

    auto cutQounterEnabled = CreateConfigToggle(config.CutQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(cutQounterPosition, config.CutQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto cutQounterDistance = CreateConfigIntIncrement(config.CutQounterConfig.distance, "Distance");
    auto cutQounterSeparateSaberCounts = CreateConfigToggle(config.CutQounterConfig.separateSaberCounts, "Separate Saber Cuts");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterSeparateSaberCounts->get_gameObject(), "Shows the average cut for the left and right sabers separately.");
    auto cutQounterSeparateCutValues = CreateConfigToggle(config.CutQounterConfig.separateCutValues, "Separate Cut Values");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterSeparateCutValues->get_gameObject(), "Show separate averages for angle before cut (0-70), angle after cut (0-30) and distance to center (0-15).");
    auto cutQounterAveragePrecision = CreateConfigIntIncrement(config.CutQounterConfig.averagePrecision, "Average Cut Precision");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterAveragePrecision->get_gameObject(), "How many decimals should be shown on the average cuts?");
}

void ShowMissedQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto missedQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Miss Qounter");
    missedQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    missedQounterTitle->set_fontSize(6.0f);

    auto missedQounterEnabled = CreateConfigToggle(config.MissedQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(missedQounterPosition, config.MissedQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto missedQounterDistance = CreateConfigIntIncrement(config.MissedQounterConfig.distance, "Distance");
    auto missedQounterCountBadCuts = CreateConfigToggle(config.MissedQounterConfig.countBadCuts, "Include Bad Cuts");
    QuestUI::BeatSaberUI::AddHoverHint(missedQounterCountBadCuts->get_gameObject(), "Bad cuts count towards the Missed counter.");
}

void ShowNotesQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto notesQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Notes Qounter");
    notesQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesQounterTitle->set_fontSize(6.0f);

    auto notesQounterEnabled = CreateConfigToggle(config.NotesQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(notesQounterPosition, config.NotesQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto notesQounterDistance = CreateConfigIntIncrement(config.NotesQounterConfig.distance, "Distance");
    auto notesQounterShowPercentage = CreateConfigToggle(config.NotesQounterConfig.showPercentage, "Show Percentage");
    QuestUI::BeatSaberUI::AddHoverHint(notesQounterShowPercentage->get_gameObject(), "Toggles the percentage of notes hit over total notes.");
    auto notesQounterDecimalPrecision = CreateConfigIntIncrement(config.NotesQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(notesQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
}

void ShowNotesLeftQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto notesLeftQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Notes Left Qounter");
    notesLeftQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesLeftQounterTitle->set_fontSize(6.0f);

    auto notesLeftQounterEnabled = CreateConfigToggle(config.NotesLeftQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(notesLeftQounterPosition, config.NotesLeftQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto notesLeftQounterDistance = CreateConfigIntIncrement(config.NotesLeftQounterConfig.distance, "Distance");
    auto notesLeftQounterLabelAboveCount = CreateConfigToggle(config.NotesLeftQounterConfig.labelAboveCount, "Label Above Qounter");
    QuestUI::BeatSaberUI::AddHoverHint(notesLeftQounterLabelAboveCount->get_gameObject(), "Put the label above the number, similar to a usual Qounters- qounter.");
}

void ShowSpinometerConfig(QountersMinus::QounterSettingsViewController* self) {
    auto spinometerTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Spinometer");
    spinometerTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    spinometerTitle->set_fontSize(6.0f);

    auto spinometerEnabled = CreateConfigToggle(config.SpinometerConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(spinometerPosition, config.SpinometerConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto spinometerDistance = CreateConfigIntIncrement(config.SpinometerConfig.distance, "Distance");
    CreateConfigEnumIncrement(spinometerMode, config.SpinometerConfig.mode, "Mode", QountersMinus::SpinometerMode, QountersMinus::SpinometerModeCount, QountersMinus::SpinometerModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(spinometerMode->get_gameObject(), "How should self Qounter display data?");
}

void ShowSpeedQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto speedQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Speed Qounter");
    speedQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    speedQounterTitle->set_fontSize(6.0f);

    auto speedQounterEnabled = CreateConfigToggle(config.SpeedQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(speedQounterPosition, config.SpeedQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto speedQounterDistance = CreateConfigIntIncrement(config.SpeedQounterConfig.distance, "Distance");
    auto speedQounterDecimalPrecision = CreateConfigIntIncrement(config.SpeedQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(speedQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    CreateConfigEnumIncrement(speedQounterMode, config.SpeedQounterConfig.mode, "Mode", QountersMinus::SpeedQounterMode, QountersMinus::SpeedQounterModeCount, QountersMinus::SpeedQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(speedQounterMode->get_gameObject(), "How should self Qounter display data?");
}

void ShowScoreQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto scoreQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Score Qounter");
    scoreQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    scoreQounterTitle->set_fontSize(6.0f);

    auto scoreQounterEnabled = CreateConfigToggle(config.ScoreQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(scoreQounterPosition, config.ScoreQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto scoreQounterDistance = CreateConfigIntIncrement(config.ScoreQounterConfig.distance, "Distance");
    CreateConfigEnumIncrement(scoreQounterMode, config.ScoreQounterConfig.mode, "Mode", QountersMinus::ScoreQounterMode, QountersMinus::ScoreQounterModeCount, QountersMinus::ScoreQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterMode->get_gameObject(), "How should self Qounter display data?");
    auto scoreQounterDecimalPrecision = CreateConfigIntIncrement(config.ScoreQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    auto scoreQounterCustomRankColors = CreateConfigToggle(config.ScoreQounterConfig.customRankColors, "Custom Rank Colors");
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterCustomRankColors->get_gameObject(), "Colors your Score Qounter depending on the rank you have in a song.");
    auto scoreQounterSSColor = CreateColorPickerButton(self->layout->get_transform(), "SS Color", config.ScoreQounterConfig.ssColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.ssColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.ssColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterSSColor, "Change the rank color for the SS rank.");
    auto scoreQounterSColor = CreateColorPickerButton(self->layout->get_transform(), "S Color", config.ScoreQounterConfig.sColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.sColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.sColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterSColor, "Change the rank color for the S rank.");
    auto scoreQounterAColor = CreateColorPickerButton(self->layout->get_transform(), "A Color", config.ScoreQounterConfig.aColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.aColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.aColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterAColor, "Change the rank color for the A rank.");
    auto scoreQounterBColor = CreateColorPickerButton(self->layout->get_transform(), "B Color", config.ScoreQounterConfig.bColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.bColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.bColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterBColor, "Change the rank color for the B rank.");
    auto scoreQounterCColor = CreateColorPickerButton(self->layout->get_transform(), "C Color", config.ScoreQounterConfig.cColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.cColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.cColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterCColor, "Change the rank color for the C rank.");
    auto scoreQounterDColor = CreateColorPickerButton(self->layout->get_transform(), "D Color", config.ScoreQounterConfig.dColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.dColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.dColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterDColor, "Change the rank color for the D rank.");
    auto scoreQounterEColor = CreateColorPickerButton(self->layout->get_transform(), "E Color", config.ScoreQounterConfig.eColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.ScoreQounterConfig.eColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.ScoreQounterConfig.eColor = val;
            QountersMinus::SaveConfig();
        })
    );
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterEColor, "Change the rank color for the E rank.");
}

void ShowPBQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto pbQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "PB Qounter");
    pbQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    pbQounterTitle->set_fontSize(6.0f);

    auto pbQounterEnabled = CreateConfigToggle(config.PBQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(pbQounterPosition, config.PBQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto pbQounterDistance = CreateConfigIntIncrement(config.PBQounterConfig.distance, "Distance");
    CreateConfigEnumIncrement(pbQounterMode, config.PBQounterConfig.mode, "Mode", QountersMinus::PBQounterMode, QountersMinus::PBQounterModeCount, QountersMinus::PBQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterMode->get_gameObject(), "Change color based on absolute (song maximum) or relative (current maximum) score.");
    auto pbQounterBetterColor = CreateColorPickerButton(self->layout->get_transform(), "Better Color", config.PBQounterConfig.betterColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.PBQounterConfig.betterColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.PBQounterConfig.betterColor = val;
            QountersMinus::SaveConfig();
        })
    );
    auto pbQounterDefaultColor = CreateColorPickerButton(self->layout->get_transform(), "Default Color", config.PBQounterConfig.defaultColor, il2cpp_utils::MakeDelegate<ColorChangeDelegate>(
        classof(ColorChangeDelegate), self, +[](QountersMinus::QounterSettingsViewController* self, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
            LOG_DEBUG("SET config.PBQounterConfig.defaultColor = %.2f,%.2f,%2.f", val.r, val.g, val.b);
            config.PBQounterConfig.defaultColor = val;
            QountersMinus::SaveConfig();
        })
    );
    auto pbQounterDecimalPrecision = CreateConfigIntIncrement(config.PBQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    auto pbQounterTextSize = CreateConfigIntIncrement(config.PBQounterConfig.textSize, "Text Size");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterTextSize->get_gameObject(), "How large should the text be?");
    // auto pbQounterUnderscore = CreateConfigToggle(config.PBQounterConfig.underScore, "Below Score Qounter");
    // QuestUI::BeatSaberUI::AddHoverHint(pbQounterUnderscore->get_gameObject(), "Will the Personal Best counter instead be positioned below the Score Qounter?");
    auto pbQounterHideFirstScore = CreateConfigToggle(config.PBQounterConfig.hideFirstScore, "Hide First Score");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterHideFirstScore->get_gameObject(), "Hides Personal Best if you play a map that doesnt yet have a personal best set.");
}

void ShowFailQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto failQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Fail Qounter");
    failQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    failQounterTitle->set_fontSize(6.0f);

    auto failQounterEnabled = CreateConfigToggle(config.FailQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(failQounterPosition, config.FailQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto failQounterDistance = CreateConfigIntIncrement(config.FailQounterConfig.distance, "Distance");
    auto failQounterShowRestartsInstead = CreateConfigToggle(config.FailQounterConfig.showRestartsInstead, "Track Restarts");
    QuestUI::BeatSaberUI::AddHoverHint(failQounterShowRestartsInstead->get_gameObject(), "Instead of showing global fail count, show the amount of times you have restarted the same song.");
}

void ShowProgressQounterConfig(QountersMinus::QounterSettingsViewController* self) {
    auto progressQounterTitle = QuestUI::BeatSaberUI::CreateText(self->layout->get_transform(), "Progress Qounter");
    progressQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    progressQounterTitle->set_fontSize(6.0f);

    auto progressQounterEnabled = CreateConfigToggle(config.ProgressQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(progressQounterPosition, config.ProgressQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto progressQounterDistance = CreateConfigIntIncrement(config.ProgressQounterConfig.distance, "Distance");
    auto progressQounterProgressTimeLeft = CreateConfigToggle(config.ProgressQounterConfig.progressTimeLeft, "Show Time Left");
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterProgressTimeLeft->get_gameObject(), "Starts the counter from the end of the song and decreases while the song is played.");
    CreateConfigEnumIncrement(progressQounterMode, config.ProgressQounterConfig.mode, "Mode", QountersMinus::ProgressQounterMode, QountersMinus::ProgressQounterModeCount, QountersMinus::ProgressQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterMode->get_gameObject(), "How should self Qounter display data?");
    auto progressQounterIncludeRing = CreateConfigToggle(config.ProgressQounterConfig.includeRing, "Include Progress Ring");
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterIncludeRing->get_gameObject(), "Whether or not the Progress Ring will also be affected by the \"Show Time Left\" setting. Only active in \"Original\" mode.");
}

#define CreateMenuButton(label, callback) \
    QuestUI::BeatSaberUI::CreateUIButton(buttonsScroller->get_transform(), label, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>( \
        classof(UnityEngine::Events::UnityAction*), this, +[](QountersMinus::QounterSettingsViewController* self) { \
            HideChildren(self); \
            callback(self); \
        } \
    ));

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
void QountersMinus::QounterSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation || !addedToHierarchy) return;

    auto buttonsScroller = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    // buttonsScroller->GetComponent<UnityEngine::RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(-10.0f, 0.0f));
    // buttonsScroller->GetComponent<UnityEngine::RectTransform*>()->set_sizeDelta(UnityEngine::Vector2(20.0f, -1.0f));
    buttonsScroller->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>()->set_spacing(1.0f);

    auto buttonsScrollerRect = buttonsScroller->get_transform()->get_parent()->get_parent()->get_parent()->GetComponent<UnityEngine::RectTransform*>();
    buttonsScrollerRect->set_sizeDelta(UnityEngine::Vector2(-112.0f, -12.0f));
    buttonsScrollerRect->set_anchoredPosition(UnityEngine::Vector2(-52.0f, 6.0f));

    auto testButton = QuestUI::BeatSaberUI::CreateUIButton(get_transform(), "Test", "PlayButton", il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
        classof(UnityEngine::Events::UnityAction*), this, +[](QountersMinus::QounterSettingsViewController* self) {
            auto simpleLevelStarters = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleLevelStarter*>();
            for (int i = 0; i < simpleLevelStarters->Length(); i++) {
                auto starter = simpleLevelStarters->values[i];
                if (starter->get_gameObject()->get_name()->Contains(il2cpp_utils::createcsstr("PerformanceTestLevelButton"))) {
                    starter->level->set_name(il2cpp_utils::createcsstr("Qounters- Test"));
                    starter->gameplayModifiers->demoNoObstacles = true;
                    starter->StartLevel();
                    return;
                }
            }
        }
    ));
    testButton->GetComponent<UnityEngine::RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(-52.0f, -27.5f));
    testButton->GetComponent<UnityEngine::RectTransform*>()->set_sizeDelta(UnityEngine::Vector2(27.0f, 10.0f));
    CreateMenuButton("Main", ShowMainConfig);
    CreateMenuButton("Cut", ShowCutQounterConfig);
    CreateMenuButton("Fail", ShowFailQounterConfig);
    CreateMenuButton("Missed", ShowMissedQounterConfig);
    CreateMenuButton("Notes Left", ShowNotesLeftQounterConfig);
    CreateMenuButton("Notes", ShowNotesQounterConfig);
    CreateMenuButton("Personal Best", ShowPBQounterConfig);
    CreateMenuButton("Progress", ShowProgressQounterConfig);
    CreateMenuButton("Score", ShowScoreQounterConfig);
    CreateMenuButton("Speed", ShowSpeedQounterConfig);
    CreateMenuButton("Spinometer", ShowSpinometerConfig);

    layout = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    auto layoutScrollerRect = layout->get_transform()->get_parent()->get_parent()->get_parent()->GetComponent<UnityEngine::RectTransform*>();
    layoutScrollerRect->set_anchoredPosition(UnityEngine::Vector2(22.0f, 0.0f));

    ShowMainConfig(this);
}

void QountersMinus::QounterSettingsViewController::Register() {
    custom_types::Register::RegisterType<QountersMinus::QounterSettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
        (ModInfo){"Qounters-", VERSION}, "Qounters-"
    );
}
