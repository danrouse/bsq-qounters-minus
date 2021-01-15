#pragma once

#include <map>
#include "util/logger.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/Animator.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "TMPro/FontStyles.hpp"

// [ALL-QOUNTERS]
#include "Qounters/CutQounter.hpp"
#include "Qounters/MissedQounter.hpp"
#include "Qounters/NotesQounter.hpp"
#include "Qounters/NotesLeftQounter.hpp"
#include "Qounters/Spinometer.hpp"
#include "Qounters/SpeedQounter.hpp"
#include "Qounters/ScoreQounter.hpp"
#include "Qounters/PBQounter.hpp"
#include "Qounters/FailQounter.hpp"
#include "Qounters/ProgressQounter.hpp"
#include "Qounters/PPQounter.hpp"

#define RegisterQounterType(type) \
    static QountersMinus::Qounters::type* type; \
    void Initialize(type##Config config);

namespace QountersMinus {
    namespace QounterRegistry {
        void RegisterTypes();
        void Initialize();
        void DestroyAll();

        void OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
        void OnNoteMiss(GlobalNamespace::NoteData* data);
        void OnScoreUpdated(int modifiedScore);
        void OnMaxScoreUpdated(int maxModifiedScore);
        void OnSwingRatingFinished(GlobalNamespace::NoteCutInfo* info, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter);

        // [ALL-QOUNTERS]
        RegisterQounterType(CutQounter);
        RegisterQounterType(FailQounter);
        RegisterQounterType(MissedQounter);
        RegisterQounterType(NotesLeftQounter);
        RegisterQounterType(NotesQounter);
        RegisterQounterType(PBQounter);
        RegisterQounterType(ProgressQounter);
        RegisterQounterType(ScoreQounter);
        RegisterQounterType(SpeedQounter);
        RegisterQounterType(Spinometer);
        RegisterQounterType(PPQounter);
    };
};
