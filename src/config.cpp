#include "config.hpp"
#include "util/logger.hpp"

QountersMinus::MainConfig mainConfig;

Configuration& getConfig() {
    static Configuration _config((ModInfo){ID, VERSION});
    _config.Load();
    return _config;
}

#define LoadConfigVar(_config, member, internalKey, type) \
    if (_config.HasMember(member) && _config[member].Is##type()) { \
        internalKey = _config[member].Get##type(); \
    } else { \
        LOG_DEBUG("Didn't find " + member); \
        foundEverything = false; \
    }
#define LoadConfigVarColor(_config, member, internalKey) \
    if (_config.HasMember(member) && _config[member].IsString()) { \
        auto hexVal = _config[member].GetString(); \
        internalKey = ParseHexColor(hexVal); \
    } else { \
        LOG_DEBUG("Didn't find " + member); \
        foundEverything = false; \
    }

template<typename T>
std::string LookupEnumString(T value, std::map<std::string, T> lookupTable) {
    for (auto kv : lookupTable) {
        if (kv.second == value) return kv.first;
    }
    return "";
}

UnityEngine::Color ParseHexColor(std::string hexString) {
    int r, g, b;
    sscanf(hexString.substr(1).c_str(), "%02x%02x%02x", &r, &g, &b);
    return UnityEngine::Color((float)r/255, (float)g/255, (float)b/255, 1.0f);
}

bool QountersMinus::LoadConfig() {
    bool foundEverything = true;
    getConfig().Load();

    LoadConfigVar(getConfig().config, "Enabled", mainConfig.enabled, Bool);
    LoadConfigVar(getConfig().config, "HideCombo", mainConfig.hideCombo, Bool);
    LoadConfigVar(getConfig().config, "HideMultiplier", mainConfig.hideMultiplier, Bool);
    LoadConfigVar(getConfig().config, "ItalicText", mainConfig.italicText, Bool);
    LoadConfigVar(getConfig().config, "ComboOffset", mainConfig.comboOffset, Double);
    LoadConfigVar(getConfig().config, "MultiplierOffset", mainConfig.multiplierOffset, Double);

    for (auto def : QountersMinus::QounterRegistry::registry) {
        LOG_DEBUG("Load for class " + def.first.first + "::" + def.first.second);
        if (getConfig().config.HasMember(def.second.configKey) && getConfig().config[def.second.configKey].IsObject()) {
            auto jsonConfigObj = getConfig().config[def.second.configKey].GetObject();
            for (auto config : def.second.configMetadata) {
                auto jsonKey = config.jsonKey == "" ? config.field : config.jsonKey;
                if (!jsonConfigObj.HasMember(jsonKey)) {
                    LOG_DEBUG("Config key not found: " + def.second.configKey + "." + jsonKey);
                    foundEverything = false;
                    continue;
                }
                auto fieldInfo = il2cpp_utils::FindField(def.first.first, def.first.second, config.field);
                switch (fieldInfo->type->type) {
                    case Il2CppTypeEnum::IL2CPP_TYPE_BOOLEAN: {
                        if (!jsonConfigObj[jsonKey].IsBool()) {
                            LOG_DEBUG("Config key is wrong type (expected bool): " + def.second.configKey + "." + jsonKey);
                            foundEverything = false;
                            continue;
                        }
                        *(bool*)config.ptr = jsonConfigObj[jsonKey].GetBool();
                        break;
                    }
                    case Il2CppTypeEnum::IL2CPP_TYPE_I4: {
                        if (config.enumNumElements == 0) {
                            // actual int
                            if (!jsonConfigObj[jsonKey].IsInt()) {
                                LOG_DEBUG("Config key is wrong type (expected int): " + def.second.configKey + "." + jsonKey);
                                foundEverything = false;
                                continue;
                            }
                            *(int*)config.ptr = jsonConfigObj[jsonKey].GetInt();
                        } else {
                            // serialized enum
                            if (!jsonConfigObj[jsonKey].IsString()) {
                                LOG_DEBUG("Config key is wrong type (expected string): " + def.second.configKey + "." + jsonKey);
                                foundEverything = false;
                                continue;
                            }
                            auto val = jsonConfigObj[jsonKey].GetString();
                            if (!config.enumSerializedNames.contains(val)) {
                                LOG_DEBUG("Config key is unknown for enum: \"" + val + "\", " + def.second.configKey + "." + jsonKey);
                                foundEverything = false;
                                continue;
                            }
                            *(int*)config.ptr = config.enumSerializedNames[val];
                        }
                        break;
                    }
                    default:
                        LOG_DEBUG("Unknown config type %d (" + def.second.configKey + "." + jsonKey + ")", fieldInfo->type->type);
                        foundEverything = false;
                }
            }
        } else {
            LOG_DEBUG("Config object not found: " + def.second.configKey);
            foundEverything = false;
        }
    }
    LOG_DEBUG("Config found all: %d", foundEverything);
    return foundEverything;
}

void QountersMinus::SaveConfig() {
    LOG_CALLER;

    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    getConfig().config.AddMember("Enabled", mainConfig.enabled, allocator);
    getConfig().config.AddMember("HideCombo", mainConfig.hideCombo, allocator);
    getConfig().config.AddMember("HideMultiplier", mainConfig.hideMultiplier, allocator);
    getConfig().config.AddMember("ItalicText", mainConfig.italicText, allocator);
    getConfig().config.AddMember("ComboOffset", mainConfig.comboOffset, allocator);
    getConfig().config.AddMember("MultiplierOffset", mainConfig.multiplierOffset, allocator);

    for (auto&& def : QountersMinus::QounterRegistry::registry) {
        rapidjson::Value childConfig(rapidjson::kObjectType);
        for (auto&& config : def.second.configMetadata) {
            auto _jsonKey = config.jsonKey == "" ? config.field : config.jsonKey;
            LOG_DEBUG("Save key " + _jsonKey);
            rapidjson::Value jsonKey(_jsonKey, allocator);
            auto fieldInfo = il2cpp_utils::FindField(def.first.first, def.first.second, config.field);
            switch (fieldInfo->type->type) {
                case Il2CppTypeEnum::IL2CPP_TYPE_BOOLEAN: {
                    childConfig.AddMember(jsonKey, *(bool*)config.ptr, allocator);
                    break;
                }
                case Il2CppTypeEnum::IL2CPP_TYPE_I4: {
                    if (config.enumNumElements == 0) {
                        childConfig.AddMember(jsonKey, *(int*)config.ptr, allocator);
                    } else {
                        std::string serializedEnumVal;
                        for (auto pair : config.enumSerializedNames) {
                            if (pair.second == *(int*)config.ptr) {
                                serializedEnumVal = pair.first;
                                break;
                            }
                        }
                        if (serializedEnumVal == "") {
                            LOG_DEBUG("Config could not find string for enum val %d (" + def.second.configKey + "." + _jsonKey + ")", *(int*)config.ptr);
                            continue;
                        }
                        childConfig.AddMember(jsonKey, serializedEnumVal, allocator);
                    }
                    break;
                }
                default:
                    //FormatColorToHex
                    LOG_DEBUG("Unknown config type %d (" + def.second.configKey + "." + _jsonKey + ")", fieldInfo->type->type);
            }
        }

        getConfig().config.AddMember(rapidjson::StringRef(def.second.configKey), childConfig, allocator);
    }

    getConfig().Write();
}
