#pragma once

#include "custom-types/shared/register.hpp"
#include "questui/shared/QuestUI.hpp"
#include "QounterRegistry.hpp"
#include "components/InjectedComponents.hpp"
#include "components/SettingsFlowCoordinator.hpp"
#include "components/SettingsButtonsViewController.hpp"
#include "components/QounterSettingsViewController.hpp"
#include "components/Qounter.hpp"
#include "components/Qounters/CutQounter.hpp"
#include "components/Qounters/FailQounter.hpp"
#include "components/Qounters/MissedQounter.hpp"
#include "components/Qounters/NotesLeftQounter.hpp"
#include "components/Qounters/NotesQounter.hpp"
#include "components/Qounters/PBQounter.hpp"
#include "components/Qounters/PPQounter.hpp"
#include "components/Qounters/ProgressQounter.hpp"
#include "components/Qounters/ScoreQounter.hpp"
#include "components/Qounters/SpeedQounter.hpp"
#include "components/Qounters/Spinometer.hpp"

using namespace QountersMinus;

namespace QountersMinus {
    inline void RegisterEverything() {
        custom_types::Register::RegisterTypes<
            InjectedComponents,
            Qounter,
            SettingsFlowCoordinator,
            SettingsButtonsViewController,
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

        QuestUI::Register::RegisterModSettingsFlowCoordinator<QountersMinus::SettingsFlowCoordinator*>((ModInfo){"Qounters-", VERSION});
    }
}
