#pragma once

#include <map>
#include "util/logger.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Animator.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "TMPro/FontStyles.hpp"

namespace QountersMinus {
    class QounterRegistry {
        public:
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
            static const std::vector<EventHandlerSignature> eventHandlerSignatures;
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
                std::vector<std::shared_ptr<ConfigMetadata>> configMetadata;
                bool isBaseQounter = false;
            } RegistryEntry;
            static std::map<std::pair<std::string, std::string>, RegistryEntry> registry;
            static std::vector<std::pair<std::string, std::string>> registryInsertionOrder;
            template <typename T>
            static void Register(std::string shortName, std::string longName, std::string configKey, bool isBaseQounter) {
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
                registryInsertionOrder.push_back({typeInfo->getNamespace(), typeInfo->getName()});
            }

            template <typename T>
            static void Register(std::string shortName, std::string longName, std::string configKey) {
                Register<T>(shortName, longName, configKey, false);
            }

            template <typename T>
            static void RegisterConfig(ConfigMetadata config) {
                auto typeInfo = custom_types::name_registry<T>::get();
                auto ptr = std::make_shared<ConfigMetadata>(config);
                registry[{typeInfo->getNamespace(), typeInfo->getName()}].configMetadata.push_back(ptr);
            }

            static void Initialize();

            template <typename... TArgs>
            static void BroadcastEvent(Event event, TArgs&&... args) {
                for (auto def : registry) {
                    if (def.second.instance && def.second.eventHandlers[event]) {
                        il2cpp_utils::RunMethodUnsafe(def.second.instance, def.second.eventHandlers[event], args...);
                    }
                }
            }
    };
};
