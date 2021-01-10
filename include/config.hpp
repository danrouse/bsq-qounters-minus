#pragma once

#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "config/CutQounterConfig.hpp"
#include "config/MissQounterConfig.hpp"
#include "config/NotesQounterConfig.hpp"
#include "config/NotesLeftQounterConfig.hpp"
#include "config/SpinometerConfig.hpp"
#include "config/SpeedQounterConfig.hpp"
#include "config/ScoreQounterConfig.hpp"
#include "config/PBQounterConfig.hpp"

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
        MissQounterConfig missQounterConfig;
        NotesQounterConfig notesQounterConfig;
        NotesLeftQounterConfig notesLeftQounterConfig;
        SpinometerConfig spinometerConfig;
        SpeedQounterConfig speedQounterConfig;
        ScoreQounterConfig scoreQounterConfig;
        PBQounterConfig pbQounterConfig;
    } ModConfig;

    bool LoadConfig();
    void SaveConfig();
}
