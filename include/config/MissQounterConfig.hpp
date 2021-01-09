#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _MissQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::OverHighway;
        
        bool countBadCuts = true;
    } MissQounterConfig;
}
