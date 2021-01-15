#include "Qounters/NotesLeftQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::NotesLeftQounter);

QountersMinus::Qounter* QountersMinus::Qounters::NotesLeftQounter::Initialize() {
    if (!config.NotesLeftQounterConfig.enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::NotesLeftQounter*>(
        config.NotesLeftQounterConfig.position, config.NotesLeftQounterConfig.distance
    );
}

void QountersMinus::Qounters::NotesLeftQounter::Start() {
    if (config.NotesLeftQounterConfig.labelAboveCount) CreateBasicTitle("Notes Remaining");
    CreateBasicText("");
    float yOffset = config.NotesLeftQounterConfig.labelAboveCount ? -30.0f : 0.0;
    float fontSize = config.NotesLeftQounterConfig.labelAboveCount ? 35.0f : 25.0f;
    basicText->set_fontSize(fontSize);
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, yOffset));

    notesLeft = GetNoteCount();
    UpdateValue();
}

void QountersMinus::Qounters::NotesLeftQounter::UpdateValue() {
    basicText->set_text(il2cpp_utils::createcsstr(
        (config.NotesLeftQounterConfig.labelAboveCount ? "" : "Notes Remaining: ") + std::to_string(notesLeft)
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
