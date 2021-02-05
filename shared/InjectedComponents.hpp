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
    DECLARE_STATIC_FIELD(SaberManager*, saberManager);
    DECLARE_STATIC_FIELD(CoreGameHUDController*, coreGameHUDController);
    DECLARE_STATIC_FIELD(RelativeScoreAndImmediateRankCounter*, relativeScoreAndImmediateRankCounter);
    DECLARE_STATIC_FIELD(ScoreController*, scoreController);
    DECLARE_STATIC_FIELD(PlayerData*, playerData);
    DECLARE_STATIC_FIELD(IDifficultyBeatmap*, difficultyBeatmap);
    DECLARE_STATIC_FIELD(BeatmapCharacteristicSO*, beatmapCharacteristic);

    DECLARE_STATIC_FIELD(int, numInstances);
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, OnDestroy);

    REGISTER_FUNCTION(InjectedComponents,
        REGISTER_FIELD(saberManager);
        REGISTER_FIELD(coreGameHUDController);
        REGISTER_FIELD(relativeScoreAndImmediateRankCounter);
        REGISTER_FIELD(scoreController);
        REGISTER_FIELD(playerData);
        REGISTER_FIELD(difficultyBeatmap);
        REGISTER_FIELD(beatmapCharacteristic);

        REGISTER_FIELD(numInstances);
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(OnDestroy);
    )
)
