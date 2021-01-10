#pragma once

#include <map>

namespace QountersMinus {
    typedef enum _QounterPosition {
        BelowCombo,
        AboveCombo,
        BelowMultiplier,
        AboveMultiplier,
        BelowEnergy,
        OverHighway
    } QounterPosition;

    static int QounterPositionCount = 6;
    static std::map<QounterPosition, std::string> QounterPositionNames = {
        {QounterPosition::BelowCombo, "Below Combo"},
        {QounterPosition::AboveCombo, "Above Combo"},
        {QounterPosition::BelowMultiplier, "Below Multiplier"},
        {QounterPosition::AboveMultiplier, "Above Multiplier"},
        {QounterPosition::BelowEnergy, "Below Energy"},
        {QounterPosition::OverHighway, "Over Highway"}
    };

    typedef struct _QounterConfig {
        bool enabled = false;
        QounterPosition position = QounterPosition::BelowCombo;
    } QounterConfig;
}
