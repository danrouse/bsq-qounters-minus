#pragma once

#include <map>
#include "util/logger.hpp"
#include "Qounter.hpp"
#include "InjectedComponents.hpp"
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

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

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
            struct EventHandlerSignature {
                Event event;
                const char* methodName;
                int numArgs;
            };
            static const std::vector<EventHandlerSignature> eventHandlerSignatures;
            struct ConfigMetadata {
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
                std::unordered_map<int, std::string> enumDisplayNames;
                std::unordered_map<std::string, int> enumSerializedNames;
                void* uiElementPtr; // yuck yuck ew yuck
            };
            struct RegistryEntry {
                QountersMinus::Qounter* instance = nullptr;
                std::unordered_map<Event, const MethodInfo*> eventHandlers;
                std::string shortName;
                std::string longName;
                std::string configKey;
                std::vector<std::shared_ptr<ConfigMetadata>> configMetadata;
                std::unordered_map<std::string, void*> staticFieldRefs;
                bool isBaseQounter = false;
            };
            static std::unordered_map<std::pair<std::string, std::string>, RegistryEntry, pair_hash> registry;
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
                std::unordered_map<Event, const MethodInfo*> eventHandlers;
                for (auto sig : eventHandlerSignatures) {
                    eventHandlers[sig.event] = il2cpp_functions::class_get_method_from_name(klass, sig.methodName, sig.numArgs);
                }
                std::unordered_map<std::string, void*> staticFieldRefs;
                if constexpr (!std::is_same_v<T, QountersMinus::Qounter>) {
                    staticFieldRefs = {
                        {"Enabled", &T::Enabled},
                        {"Position", &T::Position},
                        {"Distance", &T::Distance}
                    };
                }
                registry[{typeInfo->getNamespace(), typeInfo->getName()}] = {
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
                custom_types::_logger().disable(); // please forgive me
                auto typeInfo = custom_types::name_registry<T>::get();
                custom_types::_logger().enable(); // i am very sorry
                auto ptr = std::make_shared<ConfigMetadata>(config);
                registry[{typeInfo->getNamespace(), typeInfo->getName()}].configMetadata.emplace_back(ptr);
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
