#pragma once

#include <map>
#include "util/logger.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Animator.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "TMPro/FontStyles.hpp"

namespace QountersMinus {
    namespace QounterRegistry {
        enum Event {
            NoteCut,
            NoteMiss,
            ScoreUpdated,
            MaxScoreUpdated,
            SwingRatingFinished,
        };
        typedef struct _EventHandlerSignature {
            Event event;
            std::string methodName;
            int numArgs;
        } EventHandlerSignature;
        inline const std::vector<EventHandlerSignature> eventHandlerSignatures = {
            {Event::NoteCut, "OnNoteCut", 2},
            {Event::NoteMiss, "OnNoteMiss", 1},
            {Event::ScoreUpdated, "OnScoreUpdated", 1},
            {Event::MaxScoreUpdated, "OnMaxScoreUpdated", 1},
            {Event::SwingRatingFinished, "OnSwingRatingFinished", 2},
        };
        typedef struct _RegistryEntry {
            std::string namespaze;
            std::string klass;
            QountersMinus::Qounter* instance;
            const MethodInfo* initializer;
            std::map<Event, const MethodInfo*> eventHandlers;
        } RegistryEntry;
        inline std::vector<RegistryEntry> registry;

        void Register(std::string _namespace, std::string type);
        void Initialize();
        void DestroyAll();

        template <typename... TArgs>
        void BroadcastEvent(Event event, TArgs&&... args) {
            for (auto def : registry) {
                if (def.instance && def.eventHandlers[event]) {
                    il2cpp_utils::RunMethodUnsafe(def.instance, def.eventHandlers[event], args...);
                }
            }
        }
    };
};
