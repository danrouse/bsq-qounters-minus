#include "Qounters/ProgressQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ProgressQounter);

void QountersMinus::Qounters::ProgressQounter::Configure(QountersMinus::ProgressQounterConfig config) {
    progressTimeLeft = config.progressTimeLeft;
    includeRing = config.includeRing;

    timeText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "0", false);
    timeText->set_alignment(TMPro::TextAlignmentOptions::Center);
    timeText->set_fontSize(35.0f);
    timeText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
}

void QountersMinus::Qounters::ProgressQounter::Update() {
}
