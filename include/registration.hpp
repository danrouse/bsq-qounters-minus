#pragma once

#include "custom-types/shared/register.hpp"
#include "questui/shared/QuestUI.hpp"
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
            Qounters::CutQounter
        >();

        QounterRegistry::Register<Qounters::CutQounter>("Cut Qounter", "CutConfig");
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::Enabled,
            .field = "Enabled",
        });
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::Position,
            .field = "Position",
            .enumNumElements = QounterPositionCount,
            .enumDisplayNames = QounterPositionNames,
            .enumSerializedNames = QounterPositionLookup,
        });
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::Distance,
            .field = "Distance",
        });
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::SeparateSaberCounts,
            .field = "SeparateSaberCounts",
            .displayName = "Separate Saber Cuts",
            .helpText = "Shows the average cut for the left and right sabers separately.",
        });
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::SeparateCutValues,
            .field = "SeparateCutValues",
            .displayName = "Separate Cut Values",
            .helpText = "Show separate averages for angle before cut (0-70), angle after cut (0-30) and distance to center (0-15).",
        });
        QounterRegistry::RegisterConfig<Qounters::CutQounter>({
            .ptr = &Qounters::CutQounter::AveragePrecision,
            .field = "AveragePrecision",
            .displayName = "Average Cut Precision",
            .helpText = "How many decimals should be shown on the average cuts?",
            .intMin = 0,
            .intMax = 4,
        });

        // custom_types::Register::RegisterType<QountersMinus::Qounters::FailQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "FailQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::MissedQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "MissedQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::NotesLeftQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "NotesLeftQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::NotesQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "NotesQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::PPQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "PPQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::ProgressQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "ProgressQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::ScoreQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "ScoreQounter");

        // // must initialize after score
        // custom_types::Register::RegisterType<QountersMinus::Qounters::PBQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "PBQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::SpeedQounter>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "SpeedQounter");

        // custom_types::Register::RegisterType<QountersMinus::Qounters::Spinometer>();
        // QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "Spinometer");

        QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
            (ModInfo){"Qounters-", VERSION}, "Qounters-"
        );
    }
}
