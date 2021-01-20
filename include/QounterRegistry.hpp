#pragma once

#include <map>
#include "util/logger.hpp"
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
        typedef struct _ConfigMetadata {
            void* ptr;
            std::string field;
            std::string jsonKey;
            std::string displayName;
            std::string helpText;
            // hahaha unions you say? nay, i want the memory all for myself
            float floatMin = FLT_MIN;
            float floatMax = FLT_MAX;
            float floatStep = 1.0f;
            int intMin = INT_MIN;
            int intMax = INT_MAX;
            int intStep = 1;
            int enumNumElements = 0;
            std::map<int, std::string> enumDisplayNames;
            std::map<std::string, int> enumSerializedNames;
        } ConfigMetadata;
        typedef struct _RegistryEntry {
            QountersMinus::Qounter* instance;
            const MethodInfo* initializer;
            std::map<Event, const MethodInfo*> eventHandlers;
            std::string displayName;
            std::string configKey;
            std::vector<ConfigMetadata> configMetadata;
        } RegistryEntry;
        inline std::map<std::pair<std::string, std::string>, RegistryEntry> registry;

        void Initialize(bool enabled, bool hideCombo, bool hideMultiplier, bool italicText);
        void DestroyAll();

        template <typename T>
        void Register(std::string displayName, std::string configKey) {
            auto typeInfo = custom_types::name_registry<T>::get();
            auto initialize = il2cpp_utils::FindMethodUnsafe(typeInfo->getNamespace(), typeInfo->getName(), "Initialize", 0);
            std::map<Event, const MethodInfo*> eventHandlers;
            for (auto sig : eventHandlerSignatures) {
                eventHandlers[sig.event] = il2cpp_utils::FindMethodUnsafe(typeInfo->getNamespace(), typeInfo->getName(), sig.methodName, sig.numArgs);
            }
            registry[{typeInfo->getNamespace(), typeInfo->getName()}] = {
                .instance = (Qounter*)nullptr,
                .initializer = initialize,
                .eventHandlers = eventHandlers,
                .displayName = displayName,
                .configKey = configKey
            };
        }

        template <typename T>
        void RegisterConfig(ConfigMetadata config) {
            auto typeInfo = custom_types::name_registry<T>::get();
            registry[{typeInfo->getNamespace(), typeInfo->getName()}].configMetadata.push_back(config);
        }
        template <typename T>
        void RegisterConfig(std::vector<ConfigMetadata> configs) {
            for (auto c : configs) RegisterConfig<T>(c);
        }

        template <typename... TArgs>
        void BroadcastEvent(Event event, TArgs&&... args) {
            for (auto def : registry) {
                if (def.second.instance && def.second.eventHandlers[event]) {
                    il2cpp_utils::RunMethodUnsafe(def.second.instance, def.second.eventHandlers[event], args...);
                }
            }
        }
    };
};
