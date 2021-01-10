#include "Qounters/MissedQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::MissedQounter);

void QountersMinus::Qounters::MissedQounter::Configure(QountersMinus::MissedQounterConfig config) {
    countBadCuts = config.countBadCuts;

    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "Misses", false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(20.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    missText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "0", false);
    missText->set_alignment(TMPro::TextAlignmentOptions::Center);
    missText->set_fontSize(35.0f);
    missText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
}

void QountersMinus::Qounters::MissedQounter::UpdateValue() {
    missText->set_text(il2cpp_utils::createcsstr(std::to_string(misses)));
}

void QountersMinus::Qounters::MissedQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (countBadCuts && !info->get_allIsOK() && data->colorType != GlobalNamespace::ColorType::None) {
        misses++;
        UpdateValue();
    }
}

void QountersMinus::Qounters::MissedQounter::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (data->colorType != GlobalNamespace::ColorType::None) {
        misses++;
        UpdateValue();
    }
}
