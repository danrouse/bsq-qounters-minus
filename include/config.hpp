#pragma once

#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "config/CutQounterConfig.hpp"
#include "config/MissQounterConfig.hpp"

Configuration& getConfig();

namespace QountersMinus {
    typedef struct _ModConfig {
        bool hideCombo = false;
        bool hideMultiplier = false;
        float comboOffset = 0.2f; // ?
        float multiplierOffset = 0.4f; // ?
        bool italicText = false;

        // [ALL-QOUNTERS]
        CutQounterConfig cutQounterConfig;
        MissQounterConfig missQounterConfig;
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
