#include "Qounters/NotesLeftQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesLeftQounter);

void QountersMinus::Qounters::NotesLeftQounter::Configure(QountersMinus::NotesLeftQounterConfig config) {
    labelAboveCount = config.labelAboveCount;

    if (labelAboveCount) {
        auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "Notes Remaining", false);
        titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
        titleText->set_fontSize(20.0f);
        titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
    }

    float yOffset = labelAboveCount ? -30.0f : 0.0;
    float fontSize = labelAboveCount ? 35.0f : 25.0f;
    notesLeftText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "", false);
    notesLeftText->set_alignment(TMPro::TextAlignmentOptions::Center);
    notesLeftText->set_fontSize(fontSize);
    notesLeftText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, yOffset));

    notesLeft = GetNoteCount();
    UpdateValue();
}

void QountersMinus::Qounters::NotesLeftQounter::UpdateValue() {
    notesLeftText->set_text(il2cpp_utils::createcsstr(
        (labelAboveCount ? "" : "Notes Remaining: ") + std::to_string(notesLeft)
    ));
}

void QountersMinus::Qounters::NotesLeftQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        notesLeft--;
        UpdateValue();
    }
}

void QountersMinus::Qounters::NotesLeftQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        notesLeft--;
        UpdateValue();
    }
}
