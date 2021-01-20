#include "Qounters/PBQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::PBQounter);

bool QountersMinus::Qounters::PBQounter::Enabled = true;
int QountersMinus::Qounters::PBQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowMultiplier);
int QountersMinus::Qounters::PBQounter::Distance = 1;
int QountersMinus::Qounters::PBQounter::Mode = static_cast<int>(QountersMinus::PBQounterMode::Absolute);
UnityEngine::Color QountersMinus::Qounters::PBQounter::BetterColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::PBQounter::DefaultColor = UnityEngine::Color(1.0f, 0.647f, 0.0f, 1.0f);
int QountersMinus::Qounters::PBQounter::DecimalPrecision = 2;
int QountersMinus::Qounters::PBQounter::TextSize = 2;
bool QountersMinus::Qounters::PBQounter::UnderScore = true;
bool QountersMinus::Qounters::PBQounter::HideFirstScore = false;

QountersMinus::Qounter* QountersMinus::Qounters::PBQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::PBQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

void QountersMinus::Qounters::PBQounter::Start() {
    int noteCount = GetNoteCount();
    int maxRawScore = GlobalNamespace::ScoreModel::MaxRawScoreForNumberOfNotes(noteCount);

    maxPossibleScore = GlobalNamespace::ScoreModel::GetModifiedScoreForGameplayModifiersScoreMultiplier(
        maxRawScore,
        refs->scoreController->gameplayModifiersModel->GetTotalMultiplier(refs->scoreController->gameplayModifiers)
    );
    auto playerLevelStats = refs->playerData->GetPlayerLevelStatsData(refs->difficultyBeatmap);
    highScore = playerLevelStats->highScore;

    pbText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "", false);
    pbText->set_alignment(TMPro::TextAlignmentOptions::Top);
    pbText->set_fontSize(TextSize * 10.0f);
    pbText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    if (UnderScore) {
        auto scoreUIController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::ScoreUIController*>();
        auto scorePosition = scoreUIController->scoreText->get_transform()->get_position();
        pbText->get_transform()->set_position(UnityEngine::Vector3(scorePosition.x, scorePosition.y - 1.08f, scorePosition.z));
    }

    SetPersonalBest((float)highScore / maxPossibleScore);
    OnScoreUpdated(0);
}

void QountersMinus::Qounters::PBQounter::SetPersonalBest(float ratioOfMaxScore) {
    if (HideFirstScore && highScore == 0) {
        pbText->set_text(il2cpp_utils::createcsstr("PB: --"));
    } else {
        pbText->set_text(il2cpp_utils::createcsstr("PB: " + FormatNumber(ratioOfMaxScore * 100.0f, DecimalPrecision) + "%"));
    }
}

void QountersMinus::Qounters::PBQounter::OnScoreUpdated(int modifiedScore) {
    if (maxPossibleScore != 0) {
        if (modifiedScore > highScore) {
            SetPersonalBest(modifiedScore / (float)maxPossibleScore);
        }
    }

    if (Mode == static_cast<int>(PBQounterMode::Relative)) {
        if (refs->relativeScoreAndImmediateRankCounter->relativeScore > ((float)highScore / maxPossibleScore)) {
            pbText->set_color(BetterColor);
        } else {
            pbText->set_color(DefaultColor);
        }
    } else {
        if (modifiedScore > highScore) {
            if (!(HideFirstScore && highScore == 0)) {
                pbText->set_color(BetterColor);
            }
        } else {
            pbText->set_color(UnityEngine::Color::Lerp(
                UnityEngine::Color::get_white(),
                DefaultColor,
                (float)modifiedScore / (highScore == 0 ? 1 : highScore)
            ));
        }
    }
}
