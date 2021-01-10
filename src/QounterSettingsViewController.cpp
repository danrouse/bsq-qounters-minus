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

#define CreateConfigEnumIncrement(varName, configVar, label, enumType, enumCount, enumMap) \
   auto varName = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), label, 0, 1.0f, (float)(int)configVar, UnityEngine::Vector2(0.0f, 0.0f), nullptr); \
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

void QountersMinus::QounterSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation || !addedToHierarchy) return;

    auto layout = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    // auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(scrollContainer->get_transform());
    // layout->set_spacing(0);
    // layout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    // layout->set_padding(UnityEngine::RectOffset::New_ctor(4, 4, 4, 4));

    auto hideCombo = CreateConfigToggle(config.hideCombo, "Hide Combo");
    auto hideMultiplier = CreateConfigToggle(config.hideMultiplier, "Hide Multiplier");
    auto comboOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Combo Offset", 1, 0.1f, config.comboOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.comboOffset = %.2f", val);
            config.comboOffset = val;
            SaveConfig();
        }
    ));
    auto multiplierOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Multiplier Offset", 1, 0.1f, config.multiplierOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.multiplierOffset = %.2f", val);
            config.multiplierOffset = val;
            SaveConfig();
        }
    ));
    auto italicText = CreateConfigToggle(config.italicText, "Italic Text");

    // Qounter-specific configuration [ALL-QOUNTERS]
    //============================================================//

    auto cutQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Cut Qounter");
    cutQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    cutQounterTitle->set_fontSize(6.0f);

    auto cutQounterEnabled = CreateConfigToggle(config.cutQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(cutQounterPosition, config.cutQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
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
    CreateConfigEnumIncrement(missQounterPosition, config.missQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto missQounterCountBadCuts = CreateConfigToggle(config.missQounterConfig.countBadCuts, "Count Bad Cuts");

    //============================================================//

    auto notesQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Notes Qounter");
    notesQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesQounterTitle->set_fontSize(6.0f);

    auto notesQounterEnabled = CreateConfigToggle(config.notesQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(notesQounterPosition, config.notesQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
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
    CreateConfigEnumIncrement(notesLeftQounterPosition, config.notesLeftQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto notesLeftQounterLabelAboveCount = CreateConfigToggle(config.notesLeftQounterConfig.labelAboveCount, "Label Above Count");

    //============================================================//

    auto spinometerTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Spinometer");
    spinometerTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    spinometerTitle->set_fontSize(6.0f);

    auto spinometerEnabled = CreateConfigToggle(config.spinometerConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(spinometerPosition, config.spinometerConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    CreateConfigEnumIncrement(spinometerMode, config.spinometerConfig.mode, "Mode", QountersMinus::SpinometerMode, QountersMinus::SpinometerModeCount, QountersMinus::SpinometerModeNames);

    //============================================================//

    auto speedQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Speed Qounter");
    speedQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    speedQounterTitle->set_fontSize(6.0f);

    auto speedQounterEnabled = CreateConfigToggle(config.speedQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(speedQounterPosition, config.speedQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    CreateConfigEnumIncrement(speedQounterMode, config.speedQounterConfig.mode, "Mode", QountersMinus::SpeedQounterMode, QountersMinus::SpeedQounterModeCount, QountersMinus::SpeedQounterModeNames);
    auto speedQounterDecimalPrecision = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Decimal Precision", 0, 1.0f, config.speedQounterConfig.decimalPrecision, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.speedQounterConfig.decimalPrecision = %d", (int)val);
            config.speedQounterConfig.decimalPrecision = (int)val;
            SaveConfig();
        }
    ));

    //============================================================//

    auto scoreQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Score Qounter");
    scoreQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    scoreQounterTitle->set_fontSize(6.0f);

    auto scoreQounterEnabled = CreateConfigToggle(config.scoreQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(scoreQounterPosition, config.scoreQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    CreateConfigEnumIncrement(scoreQounterMode, config.scoreQounterConfig.mode, "Mode", QountersMinus::ScoreQounterMode, QountersMinus::ScoreQounterModeCount, QountersMinus::ScoreQounterModeNames);
    // NYI
    // auto scoreQounterCustomRankColors = CreateConfigToggle(config.scoreQounterConfig.customRankColors, "Custom Rank Colors");
}

void QountersMinus::QounterSettingsViewController::Register() {
    custom_types::Register::RegisterType<QountersMinus::QounterSettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
        (ModInfo){"Qounters-", VERSION}, "Qounters-"
    );
}
