#include "config.hpp"

QountersMinus::ModConfig config;

Configuration& getConfig() {
    static Configuration _config((ModInfo){ID, VERSION});
    _config.Load();
    return _config;
}

bool QountersMinus::LoadConfig() {
    bool isEverythingPresent = false;
    // auto _config = getConfig();
    return isEverythingPresent;
}

void QountersMinus::SaveConfig() {

}
