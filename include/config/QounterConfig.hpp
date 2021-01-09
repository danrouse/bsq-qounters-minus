#pragma once

// #include "QounterRegistry.hpp"

namespace QountersMinus {
    typedef enum _QounterPosition {
        BelowCombo,
        AboveCombo,
        BelowMultiplier,
        AboveMultiplier,
        BelowEnergy,
        OverHighway
    } QounterPosition;

    typedef struct _QounterConfig {
        bool enabled = false;
        QounterPosition position = QounterPosition::BelowCombo;
    } QounterConfig;
}
