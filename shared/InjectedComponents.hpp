#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "GlobalNamespace/RelativeScoreAndImmediateRankCounter.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IDifficultyBeatmapSet.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"

using namespace GlobalNamespace;

DECLARE_CLASS_CODEGEN(QountersMinus, InjectedComponents, UnityEngine::MonoBehaviour,
    static SaberManager* saberManager;
    static CoreGameHUDController* coreGameHUDController;
    static RelativeScoreAndImmediateRankCounter* relativeScoreAndImmediateRankCounter;
    static ScoreController* scoreController;
    static PlayerData* playerData;
    static IDifficultyBeatmap* difficultyBeatmap;
    static BeatmapCharacteristicSO* beatmapCharacteristic;

    static int numInstances;
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
)
