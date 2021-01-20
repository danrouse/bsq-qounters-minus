#pragma once

namespace QountersMinus {
    typedef struct _MainConfig {
        bool enabled = true;
        bool hideCombo = false;
        bool hideMultiplier = false;
        float comboOffset = 0.2f;
        float multiplierOffset = 0.4f;
        bool italicText = false;
    } MainConfig;
}
