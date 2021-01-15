#include "Qounters/PBQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::PBQounter);

QountersMinus::Qounter* QountersMinus::Qounters::PBQounter::Initialize() {
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::PBQounter*>(
        config.PBQounterConfig.position, config.PBQounterConfig.distance
    );
}

void QountersMinus::Qounters::PBQounter::Start() {
    int noteCount = GetNoteCount();
    int maxRawScore = GlobalNamespace::ScoreModel::MaxRawScoreForNumberOfNotes(noteCount);

    auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
    auto playerDataModel = UnityEngine::Object::FindObjectOfType<GlobalNamespace::PlayerDataModel*>();
    auto scoreController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::ScoreController*>();
    relativeScoreAndImmediateRankCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::RelativeScoreAndImmediateRankCounter*>();

    maxPossibleScore = GlobalNamespace::ScoreModel::GetModifiedScoreForGameplayModifiersScoreMultiplier(
        maxRawScore,
        scoreController->gameplayModifiersModel->GetTotalMultiplier(scoreController->gameplayModifiers)
    );
    auto playerLevelStats = playerDataModel->playerData->GetPlayerLevelStatsData(gameplayCoreInstaller->sceneSetupData->difficultyBeatmap);
    highScore = playerLevelStats->highScore;

    pbText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "", false);
    pbText->set_alignment(TMPro::TextAlignmentOptions::Top);
    pbText->set_fontSize(config.PBQounterConfig.textSize * 10.0f);
    pbText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    if (config.PBQounterConfig.underScore) {
        auto scoreUIController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::ScoreUIController*>();
        auto scorePosition = scoreUIController->scoreText->get_transform()->get_position();
        pbText->get_transform()->set_position(UnityEngine::Vector3(scorePosition.x, scorePosition.y - 1.08f, scorePosition.z));
    }

    SetPersonalBest((float)highScore / maxPossibleScore);
    OnScoreUpdated(0);
}

void QountersMinus::Qounters::PBQounter::SetPersonalBest(float ratioOfMaxScore) {
    if (config.PBQounterConfig.hideFirstScore && highScore == 0) {
        pbText->set_text(il2cpp_utils::createcsstr("PB: --"));
    } else {
        pbText->set_text(il2cpp_utils::createcsstr("PB: " + FormatNumber(ratioOfMaxScore * 100.0f, config.PBQounterConfig.decimalPrecision) + "%"));
    }
}

void QountersMinus::Qounters::PBQounter::OnScoreUpdated(int modifiedScore) {
    if (maxPossibleScore != 0) {
        if (modifiedScore > highScore) {
            SetPersonalBest(modifiedScore / (float)maxPossibleScore);
        }
    }

    if (config.PBQounterConfig.mode == PBQounterMode::Relative) {
        if (relativeScoreAndImmediateRankCounter->relativeScore > ((float)highScore / maxPossibleScore)) {
            pbText->set_color(config.PBQounterConfig.betterColor);
        } else {
            pbText->set_color(config.PBQounterConfig.defaultColor);
        }
    } else {
        if (modifiedScore > highScore) {
            if (!(config.PBQounterConfig.hideFirstScore && highScore == 0)) {
                pbText->set_color(config.PBQounterConfig.betterColor);
            }
        } else {
            pbText->set_color(UnityEngine::Color::Lerp(
                UnityEngine::Color::get_white(),
                config.PBQounterConfig.defaultColor,
                (float)modifiedScore / (highScore == 0 ? 1 : highScore)
            ));
        }
    }
}
