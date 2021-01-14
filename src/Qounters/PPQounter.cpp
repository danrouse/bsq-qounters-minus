#include "Qounters/PPQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::PPQounter);

void QountersMinus::Qounters::PPQounter::Configure(QountersMinus::PPQounterConfig config) {
    hideWhenUnranked = config.hideWhenUnranked;

    isRanked = true; // TODO
    if (hideWhenUnranked && !isRanked) return;

    relativeScoreAndImmediateRankCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::RelativeScoreAndImmediateRankCounter*>();

    CreateBasicText("");
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    OnScoreUpdated(0);
}

void QountersMinus::Qounters::PPQounter::OnScoreUpdated(int modifiedScore) {
    if (hideWhenUnranked && !isRanked) return;

}
