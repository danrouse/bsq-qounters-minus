#include "Qounters/FailQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::FailQounter);

int QountersMinus::Qounters::FailQounter::restarts = 0;
Il2CppString* QountersMinus::Qounters::FailQounter::prevBeatmapHash = nullptr;

void QountersMinus::Qounters::FailQounter::Configure(QountersMinus::FailQounterConfig config) {
    showRestartsInstead = config.showRestartsInstead;

    CreateBasicTitle(showRestartsInstead ? "Restarts" : "Fails");

    auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
    auto beatmap = gameplayCoreInstaller->sceneSetupData->difficultyBeatmap;
    auto currentBeatmapHash = to_utf8(csstrtostr(reinterpret_cast<GlobalNamespace::IPreviewBeatmapLevel*>(beatmap->get_level())->get_levelID())) + "_" + std::to_string(beatmap->get_difficultyRank());

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
                self->basicText->set_text(il2cpp_utils::createcsstr(std::to_string(self->count)));
                self->animationTimer = 0.0f;
            }
        ));
    }

    CreateBasicText(std::to_string(count));
    animationTimer = 10.0f;
}

void QountersMinus::Qounters::FailQounter::Update() {
    if (animationTimer < 1.0f) {
        basicText->set_color(UnityEngine::Color::Lerp(UnityEngine::Color::get_white(), UnityEngine::Color::get_red(), animationTimer));
        animationTimer += UnityEngine::Time::get_deltaTime();
    }
}
