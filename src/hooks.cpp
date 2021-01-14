#include "hooks.hpp"

MAKE_HOOK_OFFSETLESS(CoreGameHUDController_Start, void, GlobalNamespace::CoreGameHUDController* self) {
    LOG_CALLER;
    CoreGameHUDController_Start(self);
    QountersMinus::QounterRegistry::Initialize();
}

MAKE_HOOK_OFFSETLESS(ScoreController_Start, void, GlobalNamespace::ScoreController* self) {
    LOG_CALLER;
    ScoreController_Start(self);
    self->add_noteWasCutEvent(il2cpp_utils::MakeDelegate<NoteCutDelegate>(
        classof(NoteCutDelegate), self, +[](GlobalNamespace::ScoreController* self, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info, int unused) {
            QountersMinus::QounterRegistry::OnNoteCut(data, info);
        }
    ));
    self->add_noteWasMissedEvent(il2cpp_utils::MakeDelegate<NoteMissDelegate>(
        classof(NoteMissDelegate), self, +[](GlobalNamespace::ScoreController* self, GlobalNamespace::NoteData* data, int unused) {
            QountersMinus::QounterRegistry::OnNoteMiss(data);
        }
    ));
    self->add_scoreDidChangeEvent(il2cpp_utils::MakeDelegate<ScoreChangeDelegate>(
        classof(ScoreChangeDelegate), self, +[](GlobalNamespace::ScoreController* self, int rawScore, int modifiedScore) {
            QountersMinus::QounterRegistry::OnScoreUpdated(modifiedScore);
        }
    ));
    self->add_immediateMaxPossibleScoreDidChangeEvent(il2cpp_utils::MakeDelegate<ScoreChangeDelegate>(
        classof(ScoreChangeDelegate), self, +[](GlobalNamespace::ScoreController* self, int rawScore, int modifiedScore) {
            QountersMinus::QounterRegistry::OnMaxScoreUpdated(modifiedScore);
        }
    ));
}

MAKE_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinish, void, GlobalNamespace::BeatmapObjectExecutionRatingsRecorder::CutScoreHandler* self, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
    CutScoreHandler_HandleSwingRatingCounterDidFinish(self, swingRatingCounter);
    QountersMinus::QounterRegistry::OnSwingRatingFinished(self->noteCutInfo, swingRatingCounter);
}

void QountersMinus::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), CoreGameHUDController_Start, il2cpp_utils::FindMethodUnsafe("", "CoreGameHUDController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), ScoreController_Start, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), CutScoreHandler_HandleSwingRatingCounterDidFinish, il2cpp_utils::FindMethodUnsafe("", "BeatmapObjectExecutionRatingsRecorder/CutScoreHandler", "HandleSwingRatingCounterDidFinish", 1));
}
