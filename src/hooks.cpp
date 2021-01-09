#include "hooks.hpp"

using namespace il2cpp_utils;

MAKE_HOOK_OFFSETLESS(CoreGameHUDController_Start, void, GlobalNamespace::CoreGameHUDController* self) {
    LOG_CALLER;
    CoreGameHUDController_Start(self);
    QountersMinus::QounterRegistry::Initialize();
}

// TODO: Hook to destroy?
// TODO: Score changed, max score change hooks

MAKE_HOOK_OFFSETLESS(ScoreController_Start, void, GlobalNamespace::ScoreController* self) {
    LOG_CALLER;
    ScoreController_Start(self);
    self->add_noteWasCutEvent(MakeDelegate<System::Action_3<GlobalNamespace::NoteData*, GlobalNamespace::NoteCutInfo*, int>*>(
        classof(NoteCutDelegate), self, +[](GlobalNamespace::ScoreController self, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info, int unused) {
            QountersMinus::QounterRegistry::OnNoteCut(data, info);
        }
    ));
    self->add_noteWasMissedEvent(MakeDelegate<System::Action_2<GlobalNamespace::NoteData*, int>*>(
        classof(NoteMissDelegate), self, +[](GlobalNamespace::ScoreController self, GlobalNamespace::NoteData* data, int unused) {
            QountersMinus::QounterRegistry::OnNoteMiss(data);
        }
    ));
}

void QountersMinus::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(CoreGameHUDController_Start, FindMethodUnsafe("", "CoreGameHUDController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(ScoreController_Start, FindMethodUnsafe("", "ScoreController", "Start", 0));
}
