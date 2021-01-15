#include "util/current_song_id.hpp"

CurrentSongID GetCurrentSongID() {
    auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
    auto beatmap = gameplayCoreInstaller->sceneSetupData->difficultyBeatmap;

    return {
        to_utf8(csstrtostr(reinterpret_cast<GlobalNamespace::IPreviewBeatmapLevel*>(beatmap->get_level())->get_levelID())),
        beatmap->get_difficulty()
    };
}
