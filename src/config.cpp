#include "config.hpp"
#include "logger.hpp"

QountersMinus::ModConfig config;

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

bool QountersMinus::LoadConfig() {
    bool foundEverything = true;
    getConfig().Load();
    
    LoadConfigVar(getConfig().config, "hideCombo", config.hideCombo, Bool);
    LoadConfigVar(getConfig().config, "hideMultiplier", config.hideMultiplier, Bool);
    LoadConfigVar(getConfig().config, "italicText", config.italicText, Bool);
    LoadConfigVar(getConfig().config, "comboOffset", config.comboOffset, Double);
    LoadConfigVar(getConfig().config, "multiplierOffset", config.multiplierOffset, Double);

    // Qounter-specific settings [ALL-QOUNTERS]
    if (getConfig().config.HasMember("cutQounter") && getConfig().config["cutQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["cutQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.cutQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.cutQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "separateSaberCounts", config.cutQounterConfig.separateSaberCounts, Bool);
        LoadConfigVar(qounterConfig, "separateCutValues", config.cutQounterConfig.separateCutValues, Bool);
        LoadConfigVar(qounterConfig, "averagePrecision", config.cutQounterConfig.averagePrecision, Int);
    }
    if (getConfig().config.HasMember("missQounter") && getConfig().config["missQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["missQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.missQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.missQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "countBadCuts", config.missQounterConfig.countBadCuts, Bool);
    }
    if (getConfig().config.HasMember("notesQounter") && getConfig().config["notesQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["notesQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.notesQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.notesQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "showPercentage", config.notesQounterConfig.showPercentage, Bool);
        LoadConfigVar(qounterConfig, "decimalPrecision", config.notesQounterConfig.decimalPrecision, Int);
    }
    if (getConfig().config.HasMember("notesLeftQounter") && getConfig().config["notesLeftQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["notesLeftQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.notesLeftQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.notesLeftQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "labelAboveCount", config.notesLeftQounterConfig.labelAboveCount, Bool);
    }

    // LOG_DEBUG("Everything found? %d", foundEverything);
    return foundEverything;
}

void QountersMinus::SaveConfig() {
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    getConfig().config.AddMember("hideCombo", config.hideCombo, allocator);
    getConfig().config.AddMember("hideMultiplier", config.hideMultiplier, allocator);
    getConfig().config.AddMember("italicText", config.italicText, allocator);
    getConfig().config.AddMember("comboOffset", config.comboOffset, allocator);
    getConfig().config.AddMember("multiplierOffset", config.multiplierOffset, allocator);

    // [ALL-QOUNTERS]
    rapidjson::Value cutQounterConfig(rapidjson::kObjectType);
    cutQounterConfig.AddMember("enabled", config.cutQounterConfig.enabled, allocator);
    cutQounterConfig.AddMember("position", (int)config.cutQounterConfig.position, allocator);
    cutQounterConfig.AddMember("separateSaberCounts", config.cutQounterConfig.separateSaberCounts, allocator);
    cutQounterConfig.AddMember("separateCutValues", config.cutQounterConfig.separateCutValues, allocator);
    cutQounterConfig.AddMember("averagePrecision", config.cutQounterConfig.averagePrecision, allocator);
    getConfig().config.AddMember("cutQounter", cutQounterConfig, allocator);

    rapidjson::Value missQounterConfig(rapidjson::kObjectType);
    missQounterConfig.AddMember("enabled", config.missQounterConfig.enabled, allocator);
    missQounterConfig.AddMember("position", (int)config.missQounterConfig.position, allocator);
    missQounterConfig.AddMember("countBadCuts", config.missQounterConfig.countBadCuts, allocator);
    getConfig().config.AddMember("missQounter", missQounterConfig, allocator);

    rapidjson::Value notesQounterConfig(rapidjson::kObjectType);
    notesQounterConfig.AddMember("enabled", config.notesQounterConfig.enabled, allocator);
    notesQounterConfig.AddMember("position", (int)config.notesQounterConfig.position, allocator);
    notesQounterConfig.AddMember("showPercentage", config.notesQounterConfig.showPercentage, allocator);
    notesQounterConfig.AddMember("decimalPrecision", config.notesQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("notesQounter", notesQounterConfig, allocator);
    
    rapidjson::Value notesLeftQounterConfig(rapidjson::kObjectType);
    notesLeftQounterConfig.AddMember("enabled", config.notesLeftQounterConfig.enabled, allocator);
    notesLeftQounterConfig.AddMember("position", (int)config.notesLeftQounterConfig.position, allocator);
    notesLeftQounterConfig.AddMember("labelAboveCount", config.notesLeftQounterConfig.labelAboveCount, allocator);
    getConfig().config.AddMember("notesLeftQounter", notesLeftQounterConfig, allocator);
    
    getConfig().Write();
}
