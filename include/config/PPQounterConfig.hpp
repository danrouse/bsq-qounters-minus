#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _PPQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveHighway;
        int distance = 1;
        bool hideWhenUnranked = true;
    } PPQounterConfig;
}
