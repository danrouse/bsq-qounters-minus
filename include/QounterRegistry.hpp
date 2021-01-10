#pragma once

#include <map>
#include "logger.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "questui/shared/ArrayUtil.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "TMPro/FontStyles.hpp"

// Include all Qounter types [ALL-QOUNTERS]
#include "Qounters/CutQounter.hpp"
#include "Qounters/MissQounter.hpp"
#include "Qounters/NotesQounter.hpp"
#include "Qounters/NotesLeftQounter.hpp"
#include "Qounters/Spinometer.hpp"
#include "Qounters/SpeedQounter.hpp"
#include "Qounters/ScoreQounter.hpp"

namespace QountersMinus {
    namespace QounterRegistry {
        void RegisterTypes();
        void Initialize();
        void DestroyAll();

        void OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
        void OnNoteMiss(GlobalNamespace::NoteData* data);
        void OnScoreUpdated(int modifiedScore);
        void OnMaxScoreUpdated(int maxModifiedScore);

        // Typed initializer for each Qounter type [ALL-QOUNTERS]
        void Initialize(CutQounterConfig config);
        void Initialize(MissQounterConfig config);
        void Initialize(NotesQounterConfig config);
        void Initialize(NotesLeftQounterConfig config);
        void Initialize(SpinometerConfig config);
        void Initialize(SpeedQounterConfig config);
        void Initialize(ScoreQounterConfig config);
    };
};
