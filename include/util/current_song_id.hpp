#pragma once

#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"
#include "UnityEngine/Resources.hpp"

typedef struct _CurrentSongID {
    std::string hash;
    GlobalNamespace::BeatmapDifficulty difficulty;
} CurrentSongID;

CurrentSongID GetCurrentSongID();
