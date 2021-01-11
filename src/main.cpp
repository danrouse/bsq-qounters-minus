#include "main.hpp"

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
}

extern "C" void load() {
    il2cpp_functions::Init();

    LOG_DEBUG("Registering types");
    QountersMinus::QounterRegistry::RegisterTypes();
    QountersMinus::QounterSettingsViewController::Register();

    LOG_DEBUG("Installing hooks");
    QountersMinus::InstallHooks();

    LOG_DEBUG("Loading config");
    // if (!QountersMinus::LoadConfig())
    QountersMinus::SaveConfig();
}
