#pragma once

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"

struct SongID {
    std::string hash;
    GlobalNamespace::BeatmapDifficulty difficulty;
};

SongID GetSongID(GlobalNamespace::IDifficultyBeatmap* beatmap);
