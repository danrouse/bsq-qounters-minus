#include "hooks.hpp"

using namespace QountersMinus;

MAKE_HOOK_MATCH(CoreGameHUDController_Start, &GlobalNamespace::CoreGameHUDController::Start, void, GlobalNamespace::CoreGameHUDController* self) {
    LOG_CALLER;
    CoreGameHUDController_Start(self);
    QounterRegistry::Initialize();
}

MAKE_HOOK_MATCH(ScoreController_Start, &GlobalNamespace::ScoreController::Start, void, GlobalNamespace::ScoreController* self) {
    LOG_CALLER;
    ScoreController_Start(self);
    self->add_noteWasCutEvent(il2cpp_utils::MakeDelegate<NoteWasCutDelegate*>(
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

std::map<GlobalNamespace::ISaberSwingRatingCounter*, GlobalNamespace::NoteCutInfo> noteCutInfos;

MAKE_HOOK_MATCH(
    CutScoreHandler_Set,
    &GlobalNamespace::BeatmapObjectExecutionRatingsRecorder_CutScoreHandler::Set,
    void,
    GlobalNamespace::BeatmapObjectExecutionRatingsRecorder_CutScoreHandler* self,
    ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo,
    GlobalNamespace::NoteExecutionRating* noteExecutionRating,
    GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter
) {
    noteCutInfos[swingRatingCounter] = noteCutInfo.heldRef;
    CutScoreHandler_Set(self, noteCutInfo, noteExecutionRating, swingRatingCounter);
}

MAKE_HOOK_MATCH(
    CutScoreHandler_HandleSaberSwingRatingCounterDidFinish,
    &GlobalNamespace::BeatmapObjectExecutionRatingsRecorder_CutScoreHandler::HandleSaberSwingRatingCounterDidFinish,
    void,
    GlobalNamespace::BeatmapObjectExecutionRatingsRecorder_CutScoreHandler* self,
    GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter
) {
    CutScoreHandler_HandleSaberSwingRatingCounterDidFinish(self, swingRatingCounter);
    QounterRegistry::BroadcastEvent(
        QounterRegistry::Event::SwingRatingFinished,
        noteCutInfos[swingRatingCounter],
        swingRatingCounter,
        self->cutDistanceToCenter
    );
    noteCutInfos.erase(swingRatingCounter);
}

MAKE_HOOK_MATCH(
    QuestAppInit_AppStartAndMultiSceneEditorSetup,
    &GlobalNamespace::QuestAppInit::AppStartAndMultiSceneEditorSetup,
    void,
    GlobalNamespace::QuestAppInit* self
) {
    QuestAppInit_AppStartAndMultiSceneEditorSetup(self);

    // Defer config loading to this point to give Custom Qounters a chance to register
    LOG_DEBUG("Loading config");
    if (!QountersMinus::LoadConfig()) QountersMinus::SaveConfig();

    PP::Initialize();
}

void QountersMinus::InstallHooks() {
    INSTALL_HOOK(getLogger(), CoreGameHUDController_Start);
    INSTALL_HOOK(getLogger(), ScoreController_Start);
    INSTALL_HOOK(getLogger(), CutScoreHandler_Set);
    INSTALL_HOOK(getLogger(), CutScoreHandler_HandleSaberSwingRatingCounterDidFinish);
    INSTALL_HOOK(getLogger(), QuestAppInit_AppStartAndMultiSceneEditorSetup);
}
