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

namespace QountersMinus {
    inline void RegisterEverything() {
        custom_types::Register::RegisterType<QountersMinus::InjectedComponents>();
        custom_types::Register::RegisterType<QountersMinus::Qounter>();

        custom_types::Register::RegisterType<QountersMinus::Qounters::CutQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "CutQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::FailQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "FailQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::MissedQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "MissedQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::NotesLeftQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "NotesLeftQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::NotesQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "NotesQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::PPQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "PPQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::ProgressQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "ProgressQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::ScoreQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "ScoreQounter");

        // must initialize after score
        custom_types::Register::RegisterType<QountersMinus::Qounters::PBQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "PBQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::SpeedQounter>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "SpeedQounter");

        custom_types::Register::RegisterType<QountersMinus::Qounters::Spinometer>();
        QountersMinus::QounterRegistry::Register("QountersMinus::Qounters", "Spinometer");

        custom_types::Register::RegisterType<QountersMinus::QounterSettingsViewController>();
        QuestUI::Register::RegisterModSettingsViewController<QountersMinus::QounterSettingsViewController*>(
            (ModInfo){"Qounters-", VERSION}, "Qounters-"
        );
    }
}
