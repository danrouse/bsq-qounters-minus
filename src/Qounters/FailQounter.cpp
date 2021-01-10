#include "Qounters/FailQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::FailQounter);

int QountersMinus::Qounters::FailQounter::restarts = 0;
Il2CppString* QountersMinus::Qounters::FailQounter::prevBeatmapHash = nullptr;

void QountersMinus::Qounters::FailQounter::Configure(QountersMinus::FailQounterConfig config) {
    showRestartsInstead = config.showRestartsInstead;

    auto titleTextVal = showRestartsInstead ? "Restarts" : "Fails";
    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), titleTextVal, false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(20.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
    auto beatmap = gameplayCoreInstaller->sceneSetupData->difficultyBeatmap;
    auto currentBeatmapHash = to_utf8(csstrtostr(beatmap->get_level()->get_levelID())) + "_" + std::to_string(beatmap->get_difficultyRank());

    if (showRestartsInstead) {
        if (prevBeatmapHash != nullptr && to_utf8(csstrtostr(prevBeatmapHash)) == currentBeatmapHash) {
            restarts++;
            count = restarts;
        } else {
            restarts = count = 0;
            prevBeatmapHash = il2cpp_utils::createcsstr(currentBeatmapHash, il2cpp_utils::StringType::Manual);
        }
    } else {
        auto playerDataModel = UnityEngine::Object::FindObjectOfType<GlobalNamespace::PlayerDataModel*>();
        count = playerDataModel->playerData->playerAllOverallStatsData->get_allOverallStatsData()->failedLevelsCount;
        auto gameEnergyCounter = UnityEngine::Object::FindObjectOfType<GlobalNamespace::GameEnergyCounter*>();
        gameEnergyCounter->add_gameEnergyDidReach0Event(il2cpp_utils::MakeDelegate<System::Action*>(
            classof(System::Action*), this, +[](QountersMinus::Qounters::FailQounter* self) {
                self->count += 1;
                self->failText->set_text(il2cpp_utils::createcsstr(std::to_string(self->count)));
                self->animationTimer = 0.0f;
            }
        ));
    }

    failText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), std::to_string(count), false);
    failText->set_alignment(TMPro::TextAlignmentOptions::Center);
    failText->set_fontSize(35.0f);
    failText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
    animationTimer = 10.0f;
}

void QountersMinus::Qounters::FailQounter::Update() {
    if (animationTimer < 1.0f) {
        failText->set_color(UnityEngine::Color::Lerp(UnityEngine::Color::get_white(), UnityEngine::Color::get_red(), animationTimer));
        animationTimer += UnityEngine::Time::get_deltaTime();
    }
}
