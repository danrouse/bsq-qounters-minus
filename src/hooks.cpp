#include "hooks.hpp"

using namespace QountersMinus;

MAKE_HOOK_OFFSETLESS(CoreGameHUDController_Start, void, GlobalNamespace::CoreGameHUDController* self) {
    LOG_CALLER;
    CoreGameHUDController_Start(self);
    QounterRegistry::Initialize();
}

MAKE_HOOK_OFFSETLESS(ScoreController_Start, void, GlobalNamespace::ScoreController* self) {
    LOG_CALLER;
    ScoreController_Start(self);
    self->add_noteWasCutEvent(il2cpp_utils::MakeDelegate<NoteCutDelegate>(
        classof(NoteCutDelegate), self, +[](GlobalNamespace::ScoreController* self, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info, int unused) {
            QounterRegistry::BroadcastEvent(QounterRegistry::Event::NoteCut, data, info);
        }
    ));
    self->add_noteWasMissedEvent(il2cpp_utils::MakeDelegate<NoteMissDelegate>(
        classof(NoteMissDelegate), self, +[](GlobalNamespace::ScoreController* self, GlobalNamespace::NoteData* data, int unused) {
            QounterRegistry::BroadcastEvent(QounterRegistry::Event::NoteMiss, data);
        }
    ));
    self->add_scoreDidChangeEvent(il2cpp_utils::MakeDelegate<ScoreChangeDelegate>(
        classof(ScoreChangeDelegate), self, +[](GlobalNamespace::ScoreController* self, int rawScore, int modifiedScore) {
            QounterRegistry::BroadcastEvent(QounterRegistry::Event::ScoreUpdated, modifiedScore);
        }
    ));
    self->add_immediateMaxPossibleScoreDidChangeEvent(il2cpp_utils::MakeDelegate<ScoreChangeDelegate>(
        classof(ScoreChangeDelegate), self, +[](GlobalNamespace::ScoreController* self, int rawScore, int modifiedScore) {
            QounterRegistry::BroadcastEvent(QounterRegistry::Event::MaxScoreUpdated, modifiedScore);
        }
    ));
}

MAKE_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinish, void, GlobalNamespace::BeatmapObjectExecutionRatingsRecorder::CutScoreHandler* self, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
    CutScoreHandler_HandleSwingRatingCounterDidFinish(self, swingRatingCounter);
    QounterRegistry::BroadcastEvent(QounterRegistry::Event::SwingRatingFinished, self->noteCutInfo, swingRatingCounter);
}

MAKE_HOOK_OFFSETLESS(HealthWarningFlowCoordinator_DidActivate, void, Il2CppObject* self, bool a, bool b, bool c) {
    HealthWarningFlowCoordinator_DidActivate(self, a, b, c);

    // Defer config loading to this point to give Custom Qounters a chance to register
    LOG_DEBUG("Loading config");
    if (!QountersMinus::LoadConfig()) QountersMinus::SaveConfig();

    PP::Initialize();
}

void QountersMinus::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), CoreGameHUDController_Start, il2cpp_utils::FindMethodUnsafe("", "CoreGameHUDController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), ScoreController_Start, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), CutScoreHandler_HandleSwingRatingCounterDidFinish, il2cpp_utils::FindMethodUnsafe("", "BeatmapObjectExecutionRatingsRecorder/CutScoreHandler", "HandleSwingRatingCounterDidFinish", 1));
    INSTALL_HOOK_OFFSETLESS(getLogger(), HealthWarningFlowCoordinator_DidActivate, il2cpp_utils::FindMethodUnsafe("", "HealthWarningFlowCoordinator", "DidActivate", 3));
}
