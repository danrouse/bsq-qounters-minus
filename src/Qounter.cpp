#include "Qounter.hpp"

DEFINE_CLASS(QountersMinus::Qounter);

void QountersMinus::Qounter::Awake() {}
void QountersMinus::Qounter::Destroy() {
    UnityEngine::GameObject::Destroy(gameObject);
}
void QountersMinus::Qounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {}
void QountersMinus::Qounter::OnNoteMiss(GlobalNamespace::NoteData* data) {}
void QountersMinus::Qounter::ScoreUpdated(int modifiedScore) {}
void QountersMinus::Qounter::MaxScoreUpdated(int maxModifiedScore) {}
