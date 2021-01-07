#include "hooks.hpp"

using namespace il2cpp_utils;

extern QountersMinus::ModConfig config;

#include "GlobalNamespace/CoreGameHUDController.hpp"
MAKE_HOOK_OFFSETLESS(CoreGameHUDController_Start, void, GlobalNamespace::CoreGameHUDController* self) {
    LOG_CALLER;
    CoreGameHUDController_Start(self);
    for (auto qounterConfig : config.qounterConfigs) {
        QountersMinus::QounterRegistry::Initialize(qounterConfig);
    }
}

// MAKE_HOOK_OFFSETLESS(CoreGameHUDController_OnDestroy, void, GlobalNamespace::CoreGameHUDController* self) {
//     LOG_CALLER;
//     QountersMinus::QounterRegistry::DestroyAll();
//     CoreGameHUDController_OnDestroy(self);
// }

#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/NoteController.hpp"
MAKE_HOOK_OFFSETLESS(ScoreController_HandleNoteWasMissed, void, GlobalNamespace::ScoreController* self, GlobalNamespace::NoteController* noteController) {
    LOG_CALLER;
    QountersMinus::QounterRegistry::OnNoteMiss(noteController->noteData);
}
#include "GlobalNamespace/NoteCutInfo.hpp"
MAKE_HOOK_OFFSETLESS(ScoreController_HandleNoteWasCut, void, GlobalNamespace::ScoreController* self, GlobalNamespace::NoteController* noteController, GlobalNamespace::NoteCutInfo* noteCutInfo) {
    LOG_CALLER;
    QountersMinus::QounterRegistry::OnNoteCut(noteController->noteData, noteCutInfo);
}

void QountersMinus::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(CoreGameHUDController_Start, FindMethodUnsafe("", "CoreGameHUDController", "Start", 0));
    // INSTALL_HOOK_OFFSETLESS(CoreGameHUDController_OnDestroy, FindMethodUnsafe("", "CoreGameHUDController", "OnDestroy", 0));
    INSTALL_HOOK_OFFSETLESS(ScoreController_HandleNoteWasMissed, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "HandleNoteWasMissed", 1));
    INSTALL_HOOK_OFFSETLESS(ScoreController_HandleNoteWasCut, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "HandleNoteWasCut", 2));
}
