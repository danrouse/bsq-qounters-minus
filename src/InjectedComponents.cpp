#include "InjectedComponents.hpp"

using namespace QountersMinus;
using namespace GlobalNamespace;

DEFINE_CLASS(QountersMinus::InjectedComponents);

int InjectedComponents::numInstances = 0;
SaberManager* InjectedComponents::saberManager;
CoreGameHUDController* InjectedComponents::coreGameHUDController;
RelativeScoreAndImmediateRankCounter* InjectedComponents::relativeScoreAndImmediateRankCounter;
ScoreController* InjectedComponents::scoreController;
PlayerData* InjectedComponents::playerData;
IDifficultyBeatmap* InjectedComponents::difficultyBeatmap;

void QountersMinus::InjectedComponents::Awake() {
    if (numInstances++ == 0) {
        saberManager = UnityEngine::Object::FindObjectOfType<SaberManager*>();
        coreGameHUDController = UnityEngine::Object::FindObjectOfType<CoreGameHUDController*>();
        relativeScoreAndImmediateRankCounter = UnityEngine::Object::FindObjectOfType<RelativeScoreAndImmediateRankCounter*>();
        scoreController = UnityEngine::Object::FindObjectOfType<ScoreController*>();
        playerData = UnityEngine::Object::FindObjectOfType<PlayerDataModel*>()->playerData;

        auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
        difficultyBeatmap = gameplayCoreInstaller->sceneSetupData->difficultyBeatmap;
    }
}

void QountersMinus::InjectedComponents::OnDestroy() {
    if (--numInstances == 0) {
        saberManager = nullptr;
        coreGameHUDController = nullptr;
        relativeScoreAndImmediateRankCounter = nullptr;
        scoreController = nullptr;
        playerData = nullptr;
        difficultyBeatmap = nullptr;
    }
}
