#include "note_count.hpp"

int GetNoteCount() {
    int noteCount = 0;
    auto bocc = UnityEngine::Object::FindObjectOfType<GlobalNamespace::BeatmapObjectCallbackController*>();
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
