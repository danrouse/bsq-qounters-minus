#pragma once

#include "util/format.hpp"
#include "util/logger.hpp"
#include "QounterRegistry.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

Configuration& getConfig();

namespace QountersMinus {
    bool LoadConfig();
    void SaveConfig();
}
