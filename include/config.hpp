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
        bool hideCombo = false;
        bool hideMultiplier = false;
        float comboOffset = 0.2f;
        float multiplierOffset = 0.4f;
        bool italicText = false;

        // [ALL-QOUNTERS]
        CutQounterConfig cutQounterConfig;
        MissedQounterConfig missedQounterConfig;
        NotesQounterConfig notesQounterConfig;
        NotesLeftQounterConfig notesLeftQounterConfig;
        SpinometerConfig spinometerConfig;
        SpeedQounterConfig speedQounterConfig;
        ScoreQounterConfig scoreQounterConfig;
        PBQounterConfig pbQounterConfig;
        FailQounterConfig failQounterConfig;
        ProgressQounterConfig progressQounterConfig;
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
