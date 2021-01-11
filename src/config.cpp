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
#define LoadConfigVarColor(_config, member, internalKey) \
    if (_config.HasMember(member) && _config[member].IsArray()) { \
        auto arrayVal = _config[member].GetArray(); \
        internalKey.r = arrayVal[0].GetDouble(); \
        internalKey.g = arrayVal[1].GetDouble(); \
        internalKey.b = arrayVal[2].GetDouble(); \
        internalKey.a = arrayVal[3].GetDouble(); \
    } else { \
        LOG_DEBUG("Didn't find " + member); \
        foundEverything = false; \
    }

rapidjson::Value WriteColor(UnityEngine::Color color, rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value colorValue(rapidjson::kArrayType);
    colorValue.PushBack(color.r, allocator);
    colorValue.PushBack(color.g, allocator);
    colorValue.PushBack(color.b, allocator);
    colorValue.PushBack(color.a, allocator);
    return colorValue;
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
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("missedQounter") && getConfig().config["missedQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["missedQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.missedQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.missedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "countBadCuts", config.missedQounterConfig.countBadCuts, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("notesQounter") && getConfig().config["notesQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["notesQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.notesQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.notesQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "showPercentage", config.notesQounterConfig.showPercentage, Bool);
        LoadConfigVar(qounterConfig, "decimalPrecision", config.notesQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("notesLeftQounter") && getConfig().config["notesLeftQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["notesLeftQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.notesLeftQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);

        LoadConfigVar(qounterConfig, "enabled", config.notesLeftQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "labelAboveCount", config.notesLeftQounterConfig.labelAboveCount, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("spinometer") && getConfig().config["spinometer"].IsObject()) {
        auto qounterConfig = getConfig().config["spinometer"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.spinometerConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        int tmpMode;
        LoadConfigVar(qounterConfig, "mode", tmpMode, Int);
        config.spinometerConfig.mode = static_cast<QountersMinus::SpinometerMode>(tmpMode);
        LoadConfigVar(qounterConfig, "enabled", config.spinometerConfig.enabled, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("speedQounter") && getConfig().config["speedQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["speedQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.speedQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        int tmpMode;
        LoadConfigVar(qounterConfig, "mode", tmpMode, Int);
        config.speedQounterConfig.mode = static_cast<QountersMinus::SpeedQounterMode>(tmpMode);
        LoadConfigVar(qounterConfig, "enabled", config.speedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "decimalPrecision", config.speedQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("scoreQounter") && getConfig().config["scoreQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["scoreQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.scoreQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        int tmpMode;
        LoadConfigVar(qounterConfig, "mode", tmpMode, Int);
        config.scoreQounterConfig.mode = static_cast<QountersMinus::ScoreQounterMode>(tmpMode);
        LoadConfigVar(qounterConfig, "enabled", config.scoreQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "customRankColors", config.scoreQounterConfig.customRankColors, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("pbQounter") && getConfig().config["pbQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["pbQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.pbQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        int tmpMode;
        LoadConfigVar(qounterConfig, "mode", tmpMode, Int);
        config.pbQounterConfig.mode = static_cast<QountersMinus::PBQounterMode>(tmpMode);
        LoadConfigVar(qounterConfig, "enabled", config.pbQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "decimalPrecision", config.pbQounterConfig.decimalPrecision, Int);
        LoadConfigVar(qounterConfig, "textSize", config.pbQounterConfig.textSize, Int);
        LoadConfigVar(qounterConfig, "underscore", config.pbQounterConfig.underscore, Bool);
        LoadConfigVar(qounterConfig, "hideFirstScore", config.pbQounterConfig.hideFirstScore, Bool);
        LoadConfigVarColor(qounterConfig, "betterColor", config.pbQounterConfig.betterColor);
        LoadConfigVarColor(qounterConfig, "defaultColor", config.pbQounterConfig.defaultColor);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("failQounter") && getConfig().config["failQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["failQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.failQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        LoadConfigVar(qounterConfig, "enabled", config.failQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "showRestartsInstead", config.failQounterConfig.showRestartsInstead, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("progressQounter") && getConfig().config["progressQounter"].IsObject()) {
        auto qounterConfig = getConfig().config["progressQounter"].GetObject();
        int tmpQounterPosition;
        LoadConfigVar(qounterConfig, "position", tmpQounterPosition, Int);
        config.progressQounterConfig.position = static_cast<QountersMinus::QounterPosition>(tmpQounterPosition);
        LoadConfigVar(qounterConfig, "enabled", config.progressQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "progressTimeLeft", config.progressQounterConfig.progressTimeLeft, Bool);
        LoadConfigVar(qounterConfig, "includeRing", config.progressQounterConfig.includeRing, Bool);
    } else {
        foundEverything = false;
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

    rapidjson::Value missedQounterConfig(rapidjson::kObjectType);
    missedQounterConfig.AddMember("enabled", config.missedQounterConfig.enabled, allocator);
    missedQounterConfig.AddMember("position", (int)config.missedQounterConfig.position, allocator);
    missedQounterConfig.AddMember("countBadCuts", config.missedQounterConfig.countBadCuts, allocator);
    getConfig().config.AddMember("missedQounter", missedQounterConfig, allocator);

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

    rapidjson::Value spinometerConfig(rapidjson::kObjectType);
    spinometerConfig.AddMember("enabled", config.spinometerConfig.enabled, allocator);
    spinometerConfig.AddMember("position", (int)config.spinometerConfig.position, allocator);
    spinometerConfig.AddMember("mode", (int)config.spinometerConfig.mode, allocator);
    getConfig().config.AddMember("spinometer", spinometerConfig, allocator);

    rapidjson::Value speedQounterConfig(rapidjson::kObjectType);
    speedQounterConfig.AddMember("enabled", config.speedQounterConfig.enabled, allocator);
    speedQounterConfig.AddMember("position", (int)config.speedQounterConfig.position, allocator);
    speedQounterConfig.AddMember("mode", (int)config.speedQounterConfig.mode, allocator);
    speedQounterConfig.AddMember("decimalPrecision", config.speedQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("speedQounter", speedQounterConfig, allocator);

    rapidjson::Value scoreQounterConfig(rapidjson::kObjectType);
    scoreQounterConfig.AddMember("enabled", config.scoreQounterConfig.enabled, allocator);
    scoreQounterConfig.AddMember("position", (int)config.scoreQounterConfig.position, allocator);
    scoreQounterConfig.AddMember("mode", (int)config.scoreQounterConfig.mode, allocator);
    scoreQounterConfig.AddMember("customRankColors", config.scoreQounterConfig.customRankColors, allocator);
    // TODO colors
    getConfig().config.AddMember("scoreQounter", scoreQounterConfig, allocator);

    rapidjson::Value pbQounterConfig(rapidjson::kObjectType);
    pbQounterConfig.AddMember("enabled", config.pbQounterConfig.enabled, allocator);
    pbQounterConfig.AddMember("position", (int)config.pbQounterConfig.position, allocator);
    pbQounterConfig.AddMember("mode", (int)config.pbQounterConfig.mode, allocator);
    pbQounterConfig.AddMember("decimalPrecision", config.pbQounterConfig.decimalPrecision, allocator);
    pbQounterConfig.AddMember("textSize", config.pbQounterConfig.textSize, allocator);
    pbQounterConfig.AddMember("underscore", config.pbQounterConfig.underscore, allocator);
    pbQounterConfig.AddMember("hideFirstScore", config.pbQounterConfig.hideFirstScore, allocator);
    pbQounterConfig.AddMember("betterColor", WriteColor(config.pbQounterConfig.betterColor, allocator), allocator);
    pbQounterConfig.AddMember("defaultColor", WriteColor(config.pbQounterConfig.defaultColor, allocator), allocator);
    getConfig().config.AddMember("pbQounter", pbQounterConfig, allocator);

    rapidjson::Value failQounterConfig(rapidjson::kObjectType);
    failQounterConfig.AddMember("enabled", config.failQounterConfig.enabled, allocator);
    failQounterConfig.AddMember("position", (int)config.failQounterConfig.position, allocator);
    failQounterConfig.AddMember("showRestartsInstead", config.failQounterConfig.showRestartsInstead, allocator);
    getConfig().config.AddMember("failQounter", failQounterConfig, allocator);

    rapidjson::Value progressQounterConfig(rapidjson::kObjectType);
    progressQounterConfig.AddMember("enabled", config.progressQounterConfig.enabled, allocator);
    progressQounterConfig.AddMember("position", (int)config.progressQounterConfig.position, allocator);
    progressQounterConfig.AddMember("progressTimeLeft", config.progressQounterConfig.progressTimeLeft, allocator);
    progressQounterConfig.AddMember("includeRing", config.progressQounterConfig.includeRing, allocator);
    getConfig().config.AddMember("progressQounter", progressQounterConfig, allocator);

    getConfig().Write();
}
