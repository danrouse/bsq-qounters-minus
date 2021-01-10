#pragma once

#include <map>
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace QountersMinus {
    enum class QounterPosition {
        BelowCombo,
        AboveCombo,
        BelowMultiplier,
        AboveMultiplier,
        BelowEnergy,
        OverHighway
    };

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
        int distance = 0; // NYI
    } QounterConfig;
}
