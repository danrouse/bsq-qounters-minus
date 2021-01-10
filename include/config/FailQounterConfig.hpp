#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _FailQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveCombo;

        bool showRestartsInstead = true;
    } FailQounterConfig;
}
