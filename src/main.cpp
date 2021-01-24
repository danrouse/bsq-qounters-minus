#include "main.hpp"
#include "config.hpp"

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
}

extern "C" void load() {
    il2cpp_functions::Init();
    QuestUI::Init();
    QountersMinus::RegisterEverything();

    LOG_DEBUG("Installing hooks");
    QountersMinus::InstallHooks();
}
