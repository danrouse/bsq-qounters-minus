#pragma once

#include "format.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "config/CutQounterConfig.hpp"
#include "config/MissedQounterConfig.hpp"
#include "config/NotesQounterConfig.hpp"
#include "config/NotesLeftQounterConfig.hpp"
#include "config/SpinometerConfig.hpp"
#include "config/SpeedQounterConfig.hpp"
#include "config/ScoreQounterConfig.hpp"
#include "config/PBQounterConfig.hpp"
#include "config/FailQounterConfig.hpp"
#include "config/ProgressQounterConfig.hpp"

Configuration& getConfig();

namespace QountersMinus {
    typedef struct _ModConfig {
        bool enabled = true;
        bool hideCombo = false;
        bool hideMultiplier = false;
        float comboOffset = 0.2f;
        float multiplierOffset = 0.4f;
        bool italicText = false;

        // [ALL-QOUNTERS]
        CutQounterConfig CutQounterConfig;
        MissedQounterConfig MissedQounterConfig;
        NotesQounterConfig NotesQounterConfig;
        NotesLeftQounterConfig NotesLeftQounterConfig;
        SpinometerConfig SpinometerConfig;
        SpeedQounterConfig SpeedQounterConfig;
        ScoreQounterConfig ScoreQounterConfig;
        PBQounterConfig PBQounterConfig;
        FailQounterConfig FailQounterConfig;
        ProgressQounterConfig ProgressQounterConfig;
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
