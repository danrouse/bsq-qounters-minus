#pragma once

#include "util/logger.hpp"
#include "util/pp.hpp"
#include "QounterRegistry.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "GlobalNamespace/CoreGameHUDController.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/BeatmapObjectExecutionRatingsRecorder_CutScoreHandler.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "System/Action_3.hpp"
#include "System/Action_2.hpp"

typedef System::Action_3<GlobalNamespace::NoteData*, GlobalNamespace::NoteCutInfo*, int>* NoteCutDelegate;
typedef System::Action_2<GlobalNamespace::NoteData*, int>* NoteMissDelegate;
typedef System::Action_2<int, int>* ScoreChangeDelegate;

namespace QountersMinus {
    void InstallHooks();
}
