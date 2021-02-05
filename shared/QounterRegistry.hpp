#pragma once

#include <map>
#include "util/logger.hpp"
#include "Qounter.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/Animator.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/MultiplayerLocalActivePlayerFacade.hpp"
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
                const char* methodName;
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
                float floatMin = -100.0f;
                float floatMax = 100.0f;
                float floatStep = 1.0f;
                int intMin = -1024;
                int intMax = 1024;
                int intStep = 1;
                int enumNumElements = 0;
                std::map<int, std::string> enumDisplayNames;
                std::map<std::string, int> enumSerializedNames;
                void* uiElementPtr; // yuck yuck ew yuck
            } ConfigMetadata;
            typedef struct _RegistryEntry {
                QountersMinus::Qounter* instance;
                std::map<Event, const MethodInfo*> eventHandlers;
                std::string shortName;
                std::string longName;
                std::string configKey;
                std::vector<std::shared_ptr<ConfigMetadata>> configMetadata;
                std::map<std::string, void*> staticFieldRefs;
                bool isBaseQounter = false;
            } RegistryEntry;
            static std::map<std::pair<std::string, std::string>, RegistryEntry> registry;
            static std::vector<std::pair<std::string, std::string>> registryInsertionOrder;
            template <typename T>
            static void Register(std::string shortName, std::string longName, std::string configKey, bool isBaseQounter) {
                auto typeInfo = custom_types::name_registry<T>::get();
                const Il2CppClass* klass;
                for (auto& classWrapper : custom_types::Register::classes) {
                    auto _klass = classWrapper->get();
                    if (_klass->namespaze == typeInfo->getNamespace() && _klass->name == typeInfo->getName()) {
                        klass = _klass;
                        break;
                    }
                }
                CRASH_UNLESS(klass);
                std::map<Event, const MethodInfo*> eventHandlers;
                for (auto sig : eventHandlerSignatures) {
                    eventHandlers[sig.event] = il2cpp_functions::class_get_method_from_name(klass, sig.methodName, sig.numArgs);
                }
                std::map<std::string, void*> staticFieldRefs;
                if constexpr (!std::is_same_v<T, QountersMinus::Qounter>) {
                    staticFieldRefs = {
                        {"Enabled", &T::Enabled},
                        {"Position", &T::Position},
                        {"Distance", &T::Distance}
                    };
                }
                registry[{typeInfo->getNamespace(), typeInfo->getName()}] = {
                    .instance = (Qounter*)nullptr,
                    .eventHandlers = eventHandlers,
                    .shortName = shortName,
                    .longName = longName,
                    .configKey = configKey,
                    .isBaseQounter = isBaseQounter,
                    .staticFieldRefs = staticFieldRefs
                };
                if constexpr (!std::is_same_v<T, QountersMinus::Qounter>) {
                    RegisterConfig<T>({
                        .ptr = staticFieldRefs["Enabled"],
                        .field = "Enabled",
                    });
                    RegisterConfig<T>({
                        .ptr = staticFieldRefs["Position"],
                        .field = "Position",
                        .enumNumElements = QounterPositionCount,
                        .enumDisplayNames = QounterPositionNames,
                        .enumSerializedNames = QounterPositionLookup,
                    });
                    RegisterConfig<T>({
                        .ptr = staticFieldRefs["Distance"],
                        .field = "Distance",
                    });
                }
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
