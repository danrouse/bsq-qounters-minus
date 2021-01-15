#include "Qounters/PPQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::PPQounter);


static const float MULT_DISAPPEARINGARROWS_ORIGINAL = 0.07f;
static const float MULT_DISAPPEARINGARROWS_SCORESABER = 0.02f;
static const float MULT_GHOSTNOTES_ORIGINAL = 0.11f;
static const float MULT_GHOSTNOTES_SCORESABER = 0.04f;
static const float MULT_FASTERSONG_ORIGINAL = 0.08f;
static const float MULT_FASTERSONG_SCORESABER = 0.08f;

GlobalNamespace::GameplayModifiers* RemovePositiveModifiers(GlobalNamespace::GameplayModifiers* modifiers) {
    return GlobalNamespace::GameplayModifiers::New_ctor(
        modifiers->demoNoFail,
        modifiers->demoNoObstacles,
        modifiers->energyType,
        modifiers->noFail,
        modifiers->instaFail,
        modifiers->failOnSaberClash,
        modifiers->enabledObstacleType,
        modifiers->noBombs,
        modifiers->fastNotes,
        modifiers->strictAngles,
        false,
        modifiers->songSpeed == GlobalNamespace::GameplayModifiers::SongSpeed::Faster ?
            (GlobalNamespace::GameplayModifiers::SongSpeed)GlobalNamespace::GameplayModifiers::SongSpeed::Normal : modifiers->songSpeed,
        modifiers->noArrows,
        false
    );
}

float CalculateMultiplier(std::string songID) {
    auto scoreController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::ScoreController*>();
    auto modifiers = QountersMinus::PP::SongAllowsPositiveModifiers(songID) ?
        scoreController->gameplayModifiers : RemovePositiveModifiers(scoreController->gameplayModifiers);
    auto multiplier = scoreController->gameplayModifiersModel->GetTotalMultiplier(modifiers);

    // ScoreSaber weights these multipliers differently
    if (modifiers->get_disappearingArrows())
        multiplier += (MULT_DISAPPEARINGARROWS_SCORESABER - MULT_DISAPPEARINGARROWS_ORIGINAL);
    if (modifiers->get_ghostNotes())
        multiplier += (MULT_GHOSTNOTES_SCORESABER - MULT_GHOSTNOTES_ORIGINAL);
    if (modifiers->get_songSpeed() == GlobalNamespace::GameplayModifiers::SongSpeed::Faster)
        multiplier += (MULT_FASTERSONG_SCORESABER - MULT_FASTERSONG_ORIGINAL);

    return multiplier;
}

void QountersMinus::Qounters::PPQounter::Configure(QountersMinus::PPQounterConfig config) {
    hideWhenUnranked = config.hideWhenUnranked;

    auto songID = GetCurrentSongID();
    auto ppData = QountersMinus::PP::BeatmapMaxPP(songID.hash, songID.difficulty);
    isRanked = ppData.has_value();
    if (hideWhenUnranked && !isRanked) return;

    if (isRanked) maxPP = ppData.has_value() ? ppData.value() : 0.0f;
    relativeScoreAndImmediateRankCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::RelativeScoreAndImmediateRankCounter*>();
    multiplier = CalculateMultiplier(songID.hash);
    CreateBasicText("PP: --");
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
}

void QountersMinus::Qounters::PPQounter::OnScoreUpdated(int modifiedScore) {
    if (hideWhenUnranked && !isRanked) return;
    if (maxPP > 0.0f) {
        auto accuracy = relativeScoreAndImmediateRankCounter->relativeScore * multiplier;
        auto currentPP = QountersMinus::PP::CalculatePP(maxPP, accuracy);
        basicText->set_text(il2cpp_utils::createcsstr("PP: " + FormatNumber(currentPP, 2)));
    }
}
