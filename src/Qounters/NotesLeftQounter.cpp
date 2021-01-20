#include "Qounters/NotesLeftQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesLeftQounter);

bool QountersMinus::Qounters::NotesLeftQounter::Enabled = false;
int QountersMinus::Qounters::NotesLeftQounter::Position = static_cast<int>(QountersMinus::QounterPosition::AboveHighway);
int QountersMinus::Qounters::NotesLeftQounter::Distance = -1;
bool QountersMinus::Qounters::NotesLeftQounter::LabelAboveCount = false;

QountersMinus::Qounter* QountersMinus::Qounters::NotesLeftQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::NotesLeftQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

void QountersMinus::Qounters::NotesLeftQounter::Start() {
    if (LabelAboveCount) CreateBasicTitle("Notes Remaining");
    CreateBasicText("");
    float yOffset = LabelAboveCount ? -30.0f : 0.0;
    float fontSize = LabelAboveCount ? 35.0f : 25.0f;
    basicText->set_fontSize(fontSize);
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, yOffset));

    notesLeft = GetNoteCount();
    UpdateValue();
}

void QountersMinus::Qounters::NotesLeftQounter::UpdateValue() {
    basicText->set_text(il2cpp_utils::createcsstr(
        (LabelAboveCount ? "" : "Notes Remaining: ") + std::to_string(notesLeft)
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
