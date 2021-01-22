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
            void* uiElementPtr; // yuck yuck ew yuck
        } ConfigMetadata;
        typedef struct _RegistryEntry {
            QountersMinus::Qounter* instance;
            const MethodInfo* initializer;
            std::map<Event, const MethodInfo*> eventHandlers;
            std::string shortName;
            std::string longName;
            std::string configKey;
            bool isBaseQounter = false;
            std::vector<std::shared_ptr<ConfigMetadata>> configMetadata;
        } RegistryEntry;
        inline std::map<std::pair<std::string, std::string>, RegistryEntry> registry;

        template <typename T>
        void Register(std::string shortName, std::string longName, std::string configKey, bool isBaseQounter) {
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
                .shortName = shortName,
                .longName = longName,
                .configKey = configKey,
                .isBaseQounter = isBaseQounter
            };
        }

        template <typename T>
        void Register(std::string shortName, std::string longName, std::string configKey) {
            Register<T>(shortName, longName, configKey, false);
        }

        template <typename T>
        void RegisterConfig(ConfigMetadata config) {
            auto typeInfo = custom_types::name_registry<T>::get();
            auto ptr = std::make_shared<ConfigMetadata>(config);
            registry[{typeInfo->getNamespace(), typeInfo->getName()}].configMetadata.push_back(ptr);
        }
        template <typename T>
        void RegisterConfig(std::vector<ConfigMetadata> configs) {
            for (auto c : configs) RegisterConfig<T>(c);
        }

        void Initialize();
        void DestroyAll();

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
