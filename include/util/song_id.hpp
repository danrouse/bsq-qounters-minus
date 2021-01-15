#pragma once

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"

typedef struct _SongID {
    std::string hash;
    GlobalNamespace::BeatmapDifficulty difficulty;
} SongID;

SongID GetSongID(GlobalNamespace::IDifficultyBeatmap* beatmap);
