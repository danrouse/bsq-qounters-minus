#include "config.hpp"

Configuration& getConfig() {
    static Configuration _config((ModInfo){ID, VERSION});
    _config.Load();
    return _config;
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

    for (auto def : QountersMinus::QounterRegistry::registry) {
        rapidjson::GenericValue<rapidjson::UTF8<>> _childConfig = getConfig().config[def.second.configKey].GetObject();
        auto&& jsonConfigObj = def.second.configKey == "" ? getConfig().config : _childConfig;
        if (def.second.configKey != "" && (!getConfig().config.HasMember(def.second.configKey) || !getConfig().config[def.second.configKey].IsObject())) {
            LOG_DEBUG("Config object not found: " + def.second.configKey);
            foundEverything = false;
            continue;
        }
        // TODO: handle nesting of custom qounter configs
        for (auto fieldConfig : def.second.configMetadata) {
            auto jsonKey = fieldConfig->jsonKey == "" ? fieldConfig->field : fieldConfig->jsonKey;
            if (!jsonConfigObj.HasMember(jsonKey)) {
                LOG_DEBUG("Config key not found: " + def.second.configKey + "." + jsonKey);
                foundEverything = false;
                continue;
            }
            auto fieldInfo = il2cpp_utils::FindField(def.first.first, def.first.second, fieldConfig->field);
            auto fieldTypeName = std::string(il2cpp_utils::TypeGetSimpleName(fieldInfo->type));
            if (fieldTypeName == "bool") {
                if (jsonConfigObj[jsonKey].IsBool()) {
                    *(bool*)fieldConfig->ptr = jsonConfigObj[jsonKey].GetBool();
                } else {
                    LOG_DEBUG("Config key is wrong type (expected bool): " + def.second.configKey + "." + jsonKey);
                    foundEverything = false;
                }
            } else if (fieldTypeName == "float") {
                if (jsonConfigObj[jsonKey].IsFloat()) {
                    *(float*)fieldConfig->ptr = jsonConfigObj[jsonKey].GetFloat();
                } else {
                    LOG_DEBUG("Config key is wrong type (expected float): " + def.second.configKey + "." + jsonKey);
                    foundEverything = false;
                }
            } else if (fieldTypeName == "int") {
                if (fieldConfig->enumNumElements == 0) {
                    // actual int
                    if (jsonConfigObj[jsonKey].IsInt()) {
                        *(int*)fieldConfig->ptr = jsonConfigObj[jsonKey].GetInt();
                    } else {
                        LOG_DEBUG("Config key is wrong type (expected int): " + def.second.configKey + "." + jsonKey);
                        foundEverything = false;
                    }
                } else {
                    if (jsonConfigObj[jsonKey].IsString()) {
                        auto val = jsonConfigObj[jsonKey].GetString();
                        if (fieldConfig->enumSerializedNames.contains(val)) {
                            *(int*)fieldConfig->ptr = fieldConfig->enumSerializedNames[val];
                        } else {
                            LOG_DEBUG("Config key is unknown for enum: \"" + val + "\", " + def.second.configKey + "." + jsonKey);
                            foundEverything = false;
                        }
                    } else {
                        LOG_DEBUG("Config key is wrong type (expected string): " + def.second.configKey + "." + jsonKey);
                        foundEverything = false;
                    }
                }
            } else if (fieldTypeName == "UnityEngine.Color") {
                if (jsonConfigObj[jsonKey].IsString()) {
                    *(UnityEngine::Color*)fieldConfig->ptr = ParseHexColor(jsonConfigObj[jsonKey].GetString());
                } else {
                    LOG_DEBUG("Config key is wrong type (expected string): " + def.second.configKey + "." + jsonKey);
                    foundEverything = false;
                }
            } else {
                LOG_DEBUG("JSON field " + def.second.configKey + "." + jsonKey + " has unknown type \"" + fieldTypeName + "\"");
                foundEverything = false;
            }
        }
    }
    LOG_DEBUG("Config found all: %d", foundEverything);
    return foundEverything;
}

void QountersMinus::SaveConfig() {
    LOG_CALLER;

    // TODO: handle not removing custom qounter data, or re-adding
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    for (auto def : QountersMinus::QounterRegistry::registry) {
        rapidjson::Value _childConfig(rapidjson::kObjectType);
        auto&& childConfig = def.second.configKey == "" ? getConfig().config : _childConfig;
        for (auto fieldConfig : def.second.configMetadata) {
            auto _jsonKey = fieldConfig->jsonKey == "" ? fieldConfig->field : fieldConfig->jsonKey;
            rapidjson::Value jsonKey(_jsonKey, allocator);
            auto fieldInfo = il2cpp_utils::FindField(def.first.first, def.first.second, fieldConfig->field);
            auto fieldTypeName = std::string(il2cpp_utils::TypeGetSimpleName(fieldInfo->type));
            if (fieldTypeName == "bool") {
                childConfig.AddMember(jsonKey, *(bool*)fieldConfig->ptr, allocator);
            } else if (fieldTypeName == "float") {
                childConfig.AddMember(jsonKey, *(float*)fieldConfig->ptr, allocator);
            } else if (fieldTypeName == "int") {
                if (fieldConfig->enumNumElements == 0) {
                    childConfig.AddMember(jsonKey, *(int*)fieldConfig->ptr, allocator);
                } else {
                    std::string serializedEnumVal;
                    for (auto pair : fieldConfig->enumSerializedNames) {
                        if (pair.second == *(int*)fieldConfig->ptr) {
                            serializedEnumVal = pair.first;
                            break;
                        }
                    }
                    if (serializedEnumVal == "") {
                        LOG_DEBUG("Config could not find string for enum val %d (" + def.second.configKey + "." + _jsonKey + ")", *(int*)fieldConfig->ptr);
                    } else {
                        childConfig.AddMember(jsonKey, serializedEnumVal, allocator);
                    }
                }
            } else if (fieldTypeName == "UnityEngine.Color") {
                std::string hex = FormatColorToHex(*(UnityEngine::Color*)fieldConfig->ptr);
                childConfig.AddMember(jsonKey, hex, allocator);
            } else {
                LOG_DEBUG("JSON field " + def.second.configKey + "." + _jsonKey + " has unknown type \"" + fieldTypeName + "\"");
            }
        }
        if (def.second.configKey != "") {
            rapidjson::Value configKey(def.second.configKey, allocator);
            getConfig().config.AddMember(configKey, childConfig, allocator);
        }
    }

    getConfig().Write();
}
