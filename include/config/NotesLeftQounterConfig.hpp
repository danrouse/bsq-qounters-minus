#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _NotesLeftQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::AboveHighway;
        int distance = -1;
        bool labelAboveCount = false;
    } NotesLeftQounterConfig;
}
