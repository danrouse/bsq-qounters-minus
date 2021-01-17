#include "util/song_id.hpp"

SongID GetSongID(GlobalNamespace::IDifficultyBeatmap* beatmap) {
    auto levelID = il2cpp_utils::RunMethod<Il2CppString*>(beatmap->get_level(), "get_levelID").value();
    return {
        to_utf8(csstrtostr(levelID)),
        beatmap->get_difficulty()
    };
}
