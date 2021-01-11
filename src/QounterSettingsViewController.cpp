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

#define CreateConfigIntIncrement(configVar, label) \
    QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), label, 0, 1.0f, configVar, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>( \
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) { \
            LOG_DEBUG("SET " + #configVar + " = %d", (int)val); \
            configVar = (int)val; \
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

    auto globalEnabled = CreateConfigToggle(config.enabled, "Enabled");
    QuestUI::BeatSaberUI::AddHoverHint(globalEnabled->get_gameObject(), "Toggles Qounters-.");

    auto hideCombo = CreateConfigToggle(config.hideCombo, "Hide Combo");
    QuestUI::BeatSaberUI::AddHoverHint(hideCombo->get_gameObject(), "Hides the Combo counter.");

    auto hideMultiplier = CreateConfigToggle(config.hideMultiplier, "Hide Multiplier");
    QuestUI::BeatSaberUI::AddHoverHint(hideMultiplier->get_gameObject(), "Hides the Multiplier.");

    auto italicText = CreateConfigToggle(config.italicText, "Use Italic Text");
    QuestUI::BeatSaberUI::AddHoverHint(italicText->get_gameObject(), "Text elements will be italicized to match the base game.");

    auto comboOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Combo Offset", 1, 0.1f, config.comboOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.comboOffset = %.2f", val);
            config.comboOffset = val;
            SaveConfig();
        }
    ));
    QuestUI::BeatSaberUI::AddHoverHint(comboOffset->get_gameObject(), "Applies additional offset to qounters situated above or below the Combo.");

    auto multiplierOffset = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Multiplier Offset", 1, 0.1f, config.multiplierOffset, 0.0f, 10.0f, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
        classof(UnityEngine::Events::UnityAction_1<float>*), this, +[](QountersMinus::QounterSettingsViewController* self, float val) {
            LOG_DEBUG("SET config.multiplierOffset = %.2f", val);
            config.multiplierOffset = val;
            SaveConfig();
        }
    ));
    QuestUI::BeatSaberUI::AddHoverHint(multiplierOffset->get_gameObject(), "Applies additional offset to qounters situated above or below the Multiplier.");

    //============================================================//
    // Qounter-specific configuration [ALL-QOUNTERS]
    //============================================================//

    auto cutQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Cut Qounter");
    cutQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    cutQounterTitle->set_fontSize(6.0f);

    auto cutQounterEnabled = CreateConfigToggle(config.cutQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(cutQounterPosition, config.cutQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto cutQounterDistance = CreateConfigIntIncrement(config.cutQounterConfig.distance, "Distance");
    auto cutQounterSeparateSaberCounts = CreateConfigToggle(config.cutQounterConfig.separateSaberCounts, "Separate Saber Cuts");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterSeparateSaberCounts->get_gameObject(), "Shows the average cut for the left and right sabers separately.");
    auto cutQounterSeparateCutValues = CreateConfigToggle(config.cutQounterConfig.separateCutValues, "Separate Cut Values");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterSeparateCutValues->get_gameObject(), "Show separate averages for angle before cut (0-70), angle after cut (0-30) and distance to center (0-15).");
    auto cutQounterAveragePrecision = CreateConfigIntIncrement(config.cutQounterConfig.averagePrecision, "Average Cut Precision");
    QuestUI::BeatSaberUI::AddHoverHint(cutQounterAveragePrecision->get_gameObject(), "How many decimals should be shown on the average cuts?");

    //============================================================//

    auto missedQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Miss Qounter");
    missedQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    missedQounterTitle->set_fontSize(6.0f);

    auto missedQounterEnabled = CreateConfigToggle(config.missedQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(missedQounterPosition, config.missedQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto missedQounterDistance = CreateConfigIntIncrement(config.missedQounterConfig.distance, "Distance");
    auto missedQounterCountBadCuts = CreateConfigToggle(config.missedQounterConfig.countBadCuts, "Include Bad Cuts");
    QuestUI::BeatSaberUI::AddHoverHint(missedQounterCountBadCuts->get_gameObject(), "Bad cuts count towards the Missed counter.");

    //============================================================//

    auto notesQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Notes Qounter");
    notesQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesQounterTitle->set_fontSize(6.0f);

    auto notesQounterEnabled = CreateConfigToggle(config.notesQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(notesQounterPosition, config.notesQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto notesQounterDistance = CreateConfigIntIncrement(config.notesQounterConfig.distance, "Distance");
    auto notesQounterShowPercentage = CreateConfigToggle(config.notesQounterConfig.showPercentage, "Show Percentage");
    QuestUI::BeatSaberUI::AddHoverHint(notesQounterShowPercentage->get_gameObject(), "Toggles the percentage of notes hit over total notes.");
    auto notesQounterDecimalPrecision = CreateConfigIntIncrement(config.notesQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(notesQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");

    //============================================================//

    auto notesLeftQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Notes Left Qounter");
    notesLeftQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesLeftQounterTitle->set_fontSize(6.0f);

    auto notesLeftQounterEnabled = CreateConfigToggle(config.notesLeftQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(notesLeftQounterPosition, config.notesLeftQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto notesLeftQounterDistance = CreateConfigIntIncrement(config.notesLeftQounterConfig.distance, "Distance");
    auto notesLeftQounterLabelAboveCount = CreateConfigToggle(config.notesLeftQounterConfig.labelAboveCount, "Label Above Qounter");
    QuestUI::BeatSaberUI::AddHoverHint(notesLeftQounterLabelAboveCount->get_gameObject(), "Put the label above the number, similar to a usual Qounters- qounter.");

    //============================================================//

    auto spinometerTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Spinometer");
    spinometerTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    spinometerTitle->set_fontSize(6.0f);

    auto spinometerEnabled = CreateConfigToggle(config.spinometerConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(spinometerPosition, config.spinometerConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto spinometerDistance = CreateConfigIntIncrement(config.spinometerConfig.distance, "Distance");
    CreateConfigEnumIncrement(spinometerMode, config.spinometerConfig.mode, "Mode", QountersMinus::SpinometerMode, QountersMinus::SpinometerModeCount, QountersMinus::SpinometerModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(spinometerMode->get_gameObject(), "How should this Qounter display data?");

    //============================================================//

    auto speedQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Speed Qounter");
    speedQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    speedQounterTitle->set_fontSize(6.0f);

    auto speedQounterEnabled = CreateConfigToggle(config.speedQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(speedQounterPosition, config.speedQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto speedQounterDistance = CreateConfigIntIncrement(config.speedQounterConfig.distance, "Distance");
    auto speedQounterDecimalPrecision = CreateConfigIntIncrement(config.speedQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(speedQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    CreateConfigEnumIncrement(speedQounterMode, config.speedQounterConfig.mode, "Mode", QountersMinus::SpeedQounterMode, QountersMinus::SpeedQounterModeCount, QountersMinus::SpeedQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(speedQounterMode->get_gameObject(), "How should this Qounter display data?");

    //============================================================//

    auto scoreQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Score Qounter");
    scoreQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    scoreQounterTitle->set_fontSize(6.0f);

    auto scoreQounterEnabled = CreateConfigToggle(config.scoreQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(scoreQounterPosition, config.scoreQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto scoreQounterDistance = CreateConfigIntIncrement(config.scoreQounterConfig.distance, "Distance");
    CreateConfigEnumIncrement(scoreQounterMode, config.scoreQounterConfig.mode, "Mode", QountersMinus::ScoreQounterMode, QountersMinus::ScoreQounterModeCount, QountersMinus::ScoreQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterMode->get_gameObject(), "How should this Qounter display data?");
    auto scoreQounterDecimalPrecision = CreateConfigIntIncrement(config.scoreQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    auto scoreQounterCustomRankColors = CreateConfigToggle(config.scoreQounterConfig.customRankColors, "Custom Rank Colors");
    QuestUI::BeatSaberUI::AddHoverHint(scoreQounterCustomRankColors->get_gameObject(), "Colors your Score Qounter depending on the rank you have in a song.");
    // TODO colors
    // hover hint eeach: Change the rank color for the SS rank.

    //============================================================//

    auto pbQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "PB Qounter");
    pbQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    pbQounterTitle->set_fontSize(6.0f);

    auto pbQounterEnabled = CreateConfigToggle(config.pbQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(pbQounterPosition, config.pbQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto pbQounterDistance = CreateConfigIntIncrement(config.pbQounterConfig.distance, "Distance");
    CreateConfigEnumIncrement(pbQounterMode, config.pbQounterConfig.mode, "Mode", QountersMinus::PBQounterMode, QountersMinus::PBQounterModeCount, QountersMinus::PBQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterMode->get_gameObject(), "Change color based on absolute (song maximum) or relative (current maximum) score.");
    // TODO colors
    auto pbQounterDecimalPrecision = CreateConfigIntIncrement(config.pbQounterConfig.decimalPrecision, "Percentage Precision");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterDecimalPrecision->get_gameObject(), "How precise should the percentage be?");
    auto pbQounterTextSize = CreateConfigIntIncrement(config.pbQounterConfig.textSize, "Text Size");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterTextSize->get_gameObject(), "How large should the text be?");
    auto pbQounterUnderscore = CreateConfigToggle(config.pbQounterConfig.underscore, "Below Score Qounter");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterUnderscore->get_gameObject(), "Will the Personal Best counter instead be positioned below the Score Qounter?");
    auto pbQounterHideFirstScore = CreateConfigToggle(config.pbQounterConfig.hideFirstScore, "Hide First Score");
    QuestUI::BeatSaberUI::AddHoverHint(pbQounterHideFirstScore->get_gameObject(), "Hides Personal Best if you play a map that doesnt yet have a personal best set.");


    //============================================================//

    auto failQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Fail Qounter");
    failQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    failQounterTitle->set_fontSize(6.0f);

    auto failQounterEnabled = CreateConfigToggle(config.failQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(failQounterPosition, config.failQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto failQounterDistance = CreateConfigIntIncrement(config.failQounterConfig.distance, "Distance");
    auto failQounterShowRestartsInstead = CreateConfigToggle(config.failQounterConfig.showRestartsInstead, "Track Restarts");
    QuestUI::BeatSaberUI::AddHoverHint(failQounterShowRestartsInstead->get_gameObject(), "Instead of showing global fail count, show the amount of times you have restarted the same song.");

    //============================================================//

    auto progressQounterTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Progress Qounter");
    progressQounterTitle->set_alignment(TMPro::TextAlignmentOptions::Center);
    progressQounterTitle->set_fontSize(6.0f);

    auto progressQounterEnabled = CreateConfigToggle(config.progressQounterConfig.enabled, "Enabled");
    CreateConfigEnumIncrement(progressQounterPosition, config.progressQounterConfig.position, "Position", QountersMinus::QounterPosition, QountersMinus::QounterPositionCount, QountersMinus::QounterPositionNames);
    auto progressQounterDistance = CreateConfigIntIncrement(config.progressQounterConfig.distance, "Distance");
    auto progressQounterProgressTimeLeft = CreateConfigToggle(config.progressQounterConfig.progressTimeLeft, "Show Time Left");
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterProgressTimeLeft->get_gameObject(), "Starts the counter from the end of the song and decreases while the song is played.");
    CreateConfigEnumIncrement(progressQounterMode, config.progressQounterConfig.mode, "Mode", QountersMinus::ProgressQounterMode, QountersMinus::ProgressQounterModeCount, QountersMinus::ProgressQounterModeNames);
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterMode->get_gameObject(), "How should this Qounter display data?");
    auto progressQounterIncludeRing = CreateConfigToggle(config.progressQounterConfig.includeRing, "Include Progress Ring");
    QuestUI::BeatSaberUI::AddHoverHint(progressQounterIncludeRing->get_gameObject(), "Whether or not the Progress Ring will also be affected by the \"Show Time Left\" setting. Only active in \"Original\" mode.");
}

void QountersMinus::QounterSettingsViewController::Register() {
    custom_types::Register::RegisterType<QountersMinus::QounterSettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
        (ModInfo){"Qounters-", VERSION}, "Qounters-"
    );
}
