#pragma once

#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "config/CutQounterConfig.hpp"

Configuration& getConfig();

namespace QountersMinus {
    typedef struct _ModConfig {
        bool hideCombo = false;
        bool hideMultiplier = false;
        float comboOffset = 0.2f; // ?
        float multiplierOffset = 0.4f; // ?
        bool italicText = false;

        CutQounterConfig cutQounterConfig;
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
