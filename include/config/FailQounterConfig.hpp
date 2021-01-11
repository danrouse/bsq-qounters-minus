#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _FailQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveCombo;
        int distance = 0;
        bool showRestartsInstead = true;
    } FailQounterConfig;
}
