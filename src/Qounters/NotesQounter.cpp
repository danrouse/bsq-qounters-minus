#include "Qounters/NotesQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesQounter);

void QountersMinus::Qounters::NotesQounter::Configure(QountersMinus::NotesQounterConfig config) {
    showPercentage = config.showPercentage;
    decimalPrecision = config.decimalPrecision;

    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "Notes", false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(20.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    std::string defaultText = "0";
    if (showPercentage) defaultText += " - " + FormatNumber(100.0f, decimalPrecision) + "%";
    notesText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), defaultText, false);
    notesText->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesText->set_fontSize(35.0f);
    notesText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
}

void QountersMinus::Qounters::NotesQounter::UpdateValue() {
    auto text = std::to_string(goodCuts) + "/" + std::to_string(allCuts);
    if (showPercentage) {
        text += " - " + FormatNumber((100.0f * goodCuts) / allCuts, decimalPrecision) + "%";
    }
    notesText->set_text(il2cpp_utils::createcsstr(text));
}

void QountersMinus::Qounters::NotesQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    allCuts++;
    if (info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
        goodCuts++;
    }
    UpdateValue();
}

void QountersMinus::Qounters::NotesQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        allCuts++;
        UpdateValue();
    }
}
