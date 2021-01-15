#include "util/song_id.hpp"

SongID GetSongID(GlobalNamespace::IDifficultyBeatmap* beatmap) {
    return {
        to_utf8(csstrtostr(reinterpret_cast<GlobalNamespace::IPreviewBeatmapLevel*>(beatmap->get_level())->get_levelID())),
        beatmap->get_difficulty()
    };
}
