#pragma once

#include "QounterRegistry.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

Configuration& getConfig();

namespace QountersMinus {
    typedef struct _ModConfig {
        std::vector<QounterConfig> qounterConfigs = {
            {QounterType::CutQounter, QounterPosition::BelowCombo}
        };
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
