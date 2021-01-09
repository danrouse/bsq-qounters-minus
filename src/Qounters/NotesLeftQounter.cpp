#include "Qounters/NotesLeftQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::NotesLeftQounter);

int GetNoteCount() {
    int noteCount = 0;
    auto bocc = QuestUI::ArrayUtil::First<GlobalNamespace::BeatmapObjectCallbackController>(
        UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::BeatmapObjectCallbackController*>(),
        [](GlobalNamespace::BeatmapObjectCallbackController* x) { return x->get_enabled(); }
    );
    auto songTime = bocc->initData->spawningStartTime;
    // auto beatmapLinesData = bocc->initData->beatmapData->GetCopy()->beatmapLinesData;
    auto beatmapLinesData = reinterpret_cast<GlobalNamespace::BeatmapData*>(bocc->initData->beatmapData)->beatmapLinesData;
    for (int i = 0; i < beatmapLinesData->Length(); i++) {
        auto beatmapLineData = beatmapLinesData->values[i];
        auto beatmapObjectsData = beatmapLineData->beatmapObjectsData->items;
        for (int j = 0; j < beatmapObjectsData->Length(); j++) {
            auto beatmapObjectData = beatmapObjectsData->values[j];
            if (!beatmapObjectData) continue;
            if (beatmapObjectData->get_beatmapObjectType() == GlobalNamespace::BeatmapObjectType::Note) {
                auto note = reinterpret_cast<GlobalNamespace::NoteData*>(beatmapObjectData);
                if (note->colorType != GlobalNamespace::ColorType::None && note->time > songTime) {
                    noteCount++;
                }
            }
        }
    }
    return noteCount;
}

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
