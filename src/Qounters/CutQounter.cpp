#include "Qounters/CutQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::CutQounter);

void QountersMinus::Qounters::CutQounter::Awake() {
    static auto gameObjectName = il2cpp_utils::createcsstr("QountersMinus_CutQounter", il2cpp_utils::StringType::Manual);
    gameObject = UnityEngine::GameObject::New_ctor(gameObjectName);
    gameObject->get_transform()->SetParent(get_transform(), false);

    auto text = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "Test text");
    text->set_fontSize(20.0f);
}

void QountersMinus::Qounters::CutQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {}
void QountersMinus::Qounters::CutQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {}
