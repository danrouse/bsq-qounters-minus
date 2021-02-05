#pragma once

#include "custom-types/shared/register.hpp"
#include "questui/shared/QuestUI.hpp"
#include "QounterRegistry.hpp"
#include "InjectedComponents.hpp"
#include "QounterSettingsViewController.hpp"
#include "Qounter.hpp"
#include "Qounters/CutQounter.hpp"
#include "Qounters/FailQounter.hpp"
#include "Qounters/MissedQounter.hpp"
#include "Qounters/NotesLeftQounter.hpp"
#include "Qounters/NotesQounter.hpp"
#include "Qounters/PBQounter.hpp"
#include "Qounters/PPQounter.hpp"
#include "Qounters/ProgressQounter.hpp"
#include "Qounters/ScoreQounter.hpp"
#include "Qounters/SpeedQounter.hpp"
#include "Qounters/Spinometer.hpp"

using namespace QountersMinus;

namespace QountersMinus {
    inline void RegisterEverything() {
        custom_types::Register::RegisterTypes<
            InjectedComponents,
            Qounter,
            QounterSettingsViewController
        >();
        custom_types::Register::RegisterTypes<
            Qounters::CutQounter,
            Qounters::FailQounter,
            Qounters::MissedQounter,
            Qounters::NotesLeftQounter,
            Qounters::NotesQounter,
            Qounters::PBQounter,
            Qounters::PPQounter,
            Qounters::ProgressQounter,
            Qounters::ScoreQounter,
            Qounters::SpeedQounter,
            Qounters::Spinometer
        >();

        QounterRegistry::Register<Qounter>("Main", "Qounters-", "", true);
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::Enabled,
            .field = "Enabled",
            .helpText = "Toggles Qounters-.",
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::HideCombo,
            .field = "HideCombo",
            .displayName = "Hide Combo",
            .helpText = "Hides the Combo counter.",
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::HideMultiplier,
            .field = "HideMultiplier",
            .displayName = "Hide Multiplier",
            .helpText = "Hides the Multiplier.",
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::UprightInMultiplayer,
            .field = "UprightInMultiplayer",
            .displayName = "Upright HUD in Multiplayer",
            .helpText = "In multiplayer, the game HUD and Qounters will be vertical as in solo mode.",
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::ItalicText,
            .field = "ItalicText",
            .displayName = "Use Italic Text",
            .helpText = "Text elements will be italicized to match the base game.",
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::ComboOffset,
            .field = "ComboOffset",
            .displayName = "Combo Offset",
            .helpText = "Applies additional offset to Qounters situated above or below the Combo.",
            .floatStep = 0.1f,
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::MultiplierOffset,
            .field = "MultiplierOffset",
            .displayName = "Multiplier Offset",
            .helpText = "Applies additional offset to Qounters situated above or below the Multiplier.",
            .floatStep = 0.1f,
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::DisableIn90Degree,
            .field = "DisableIn90Degree",
            .displayName = "Disable In 90/360-Degree Maps",
            .helpText = "Disables Qounters- when playing a beatmap in 90- or 360-degree mode.",
            .floatStep = 0.1f,
        });
        QounterRegistry::RegisterConfig<Qounter>({
            .ptr = &QountersMinus::Qounter::DistanceStep,
            .field = "DistanceStep",
            .displayName = "Distance Increment",
            .helpText = "How much to adjust Distance settings per click. Lower means finer tuning.",
            .floatMin = 0.1f,
            .floatStep = 0.1f,
        });

        Qounters::CutQounter::Register();
        Qounters::FailQounter::Register();
        Qounters::MissedQounter::Register();
        Qounters::NotesLeftQounter::Register();
        Qounters::NotesQounter::Register();
        Qounters::PPQounter::Register();
        Qounters::ProgressQounter::Register();
        Qounters::ScoreQounter::Register();
        Qounters::PBQounter::Register(); // must initialize after score
        Qounters::SpeedQounter::Register();
        Qounters::Spinometer::Register();

        QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
            (ModInfo){"Qounters-", VERSION}, "Qounters-"
        );
    }
}
