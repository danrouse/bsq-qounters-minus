#pragma once

#include "QounterConfig.hpp"

namespace QountersMinus {
    typedef struct _NotesLeftQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::OverHighway;
        bool labelAboveCount = false;
    } NotesLeftQounterConfig;
}
