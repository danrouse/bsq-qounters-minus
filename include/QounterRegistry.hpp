#pragma once

#include <map>
#include "logger.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/Transform.hpp"

#include "Qounters/CutQounter.hpp"

namespace QountersMinus {
    namespace QounterRegistry {
        typedef struct _registry_t {
            // Store a reference to one of each enabled Qounter [ALL-QOUNTERS]
            Qounters::CutQounter* cutQounter;
        } registry_t;
        
        void RegisterTypes();
        void Initialize();
        void DestroyAll();
        
        UnityEngine::GameObject* GetParent(QounterConfig config);

        void OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
        void OnNoteMiss(GlobalNamespace::NoteData* data);
        void OnScoreUpdated(int modifiedScore);
        void OnMaxScoreUpdated(int maxModifiedScore);
        
        // Typed initializer for each Qounter type [ALL-QOUNTERS]
        void Initialize(CutQounterConfig config);
    };
};
