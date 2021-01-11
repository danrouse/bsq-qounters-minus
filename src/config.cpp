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

    LoadConfigVar(getConfig().config, "Enabled", config.enabled, Bool);
    LoadConfigVar(getConfig().config, "HideCombo", config.hideCombo, Bool);
    LoadConfigVar(getConfig().config, "HideMultiplier", config.hideMultiplier, Bool);
    LoadConfigVar(getConfig().config, "ItalicText", config.italicText, Bool);
    LoadConfigVar(getConfig().config, "ComboOffset", config.comboOffset, Double);
    LoadConfigVar(getConfig().config, "MultiplierOffset", config.multiplierOffset, Double);

    // Qounter-specific settings [ALL-QOUNTERS]
    if (getConfig().config.HasMember("CutConfig") && getConfig().config["CutConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["CutConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.cutQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.cutQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.cutQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "SeparateSaberCounts", config.cutQounterConfig.separateSaberCounts, Bool);
        LoadConfigVar(qounterConfig, "SeparateCutValues", config.cutQounterConfig.separateCutValues, Bool);
        LoadConfigVar(qounterConfig, "AveragePrecision", config.cutQounterConfig.averagePrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("MissedConfig") && getConfig().config["MissedConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["MissedConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.missedQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.missedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.missedQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "CountBadCuts", config.missedQounterConfig.countBadCuts, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("NoteConfig") && getConfig().config["NoteConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["NoteConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.notesQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.notesQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.notesQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ShowPercentage", config.notesQounterConfig.showPercentage, Bool);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.notesQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("NotesLeftConfig") && getConfig().config["NotesLeftConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["NotesLeftConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.notesLeftQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.notesLeftQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.notesLeftQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "LabelAboveCount", config.notesLeftQounterConfig.labelAboveCount, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("SpinometerConfig") && getConfig().config["SpinometerConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["SpinometerConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.spinometerConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.spinometerConfig.mode = QountersMinus::SpinometerModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.spinometerConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.spinometerConfig.distance, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("SpeedConfig") && getConfig().config["SpeedConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["SpeedConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.speedQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.speedQounterConfig.mode = QountersMinus::SpeedQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.speedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.speedQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.speedQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("ScoreConfig") && getConfig().config["ScoreConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["ScoreConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.scoreQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.scoreQounterConfig.mode = QountersMinus::ScoreQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.scoreQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.scoreQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.scoreQounterConfig.decimalPrecision, Int);
        LoadConfigVar(qounterConfig, "DisplayRank", config.scoreQounterConfig.displayRank, Bool);
        LoadConfigVar(qounterConfig, "CustomRankColors", config.scoreQounterConfig.customRankColors, Bool);
        LoadConfigVarColor(qounterConfig, "SSColor", config.scoreQounterConfig.ssColor);
        LoadConfigVarColor(qounterConfig, "SColor", config.scoreQounterConfig.sColor);
        LoadConfigVarColor(qounterConfig, "AColor", config.scoreQounterConfig.aColor);
        LoadConfigVarColor(qounterConfig, "BColor", config.scoreQounterConfig.bColor);
        LoadConfigVarColor(qounterConfig, "CColor", config.scoreQounterConfig.cColor);
        LoadConfigVarColor(qounterConfig, "DColor", config.scoreQounterConfig.dColor);
        LoadConfigVarColor(qounterConfig, "EColor", config.scoreQounterConfig.eColor);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("PBConfig") && getConfig().config["PBConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["PBConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.pbQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.pbQounterConfig.mode = QountersMinus::PBQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.pbQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.pbQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.pbQounterConfig.decimalPrecision, Int);
        LoadConfigVar(qounterConfig, "TextSize", config.pbQounterConfig.textSize, Int);
        LoadConfigVar(qounterConfig, "UnderScore", config.pbQounterConfig.underscore, Bool);
        LoadConfigVar(qounterConfig, "HideFirstScore", config.pbQounterConfig.hideFirstScore, Bool);
        LoadConfigVarColor(qounterConfig, "BetterColor", config.pbQounterConfig.betterColor);
        LoadConfigVarColor(qounterConfig, "DefaultColor", config.pbQounterConfig.defaultColor);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("FailsConfig") && getConfig().config["FailsConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["FailsConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.failQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        LoadConfigVar(qounterConfig, "Enabled", config.failQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.failQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ShowRestartsInstead", config.failQounterConfig.showRestartsInstead, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("ProgressConfig") && getConfig().config["ProgressConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["ProgressConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.progressQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        LoadConfigVar(qounterConfig, "Enabled", config.progressQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.progressQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ProgressTimeLeft", config.progressQounterConfig.progressTimeLeft, Bool);
        LoadConfigVar(qounterConfig, "IncludeRing", config.progressQounterConfig.includeRing, Bool);
    } else {
        foundEverything = false;
    }

    return foundEverything;
}

void QountersMinus::SaveConfig() {
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    getConfig().config.AddMember("Enabled", config.enabled, allocator);
    getConfig().config.AddMember("HideCombo", config.hideCombo, allocator);
    getConfig().config.AddMember("HideMultiplier", config.hideMultiplier, allocator);
    getConfig().config.AddMember("ItalicText", config.italicText, allocator);
    getConfig().config.AddMember("ComboOffset", config.comboOffset, allocator);
    getConfig().config.AddMember("MultiplierOffset", config.multiplierOffset, allocator);

    // [ALL-QOUNTERS]
    rapidjson::Value cutQounterConfig(rapidjson::kObjectType);
    cutQounterConfig.AddMember("Enabled", config.cutQounterConfig.enabled, allocator);
    cutQounterConfig.AddMember("Distance", config.cutQounterConfig.distance, allocator);
    cutQounterConfig.AddMember("Position", LookupEnumString(config.cutQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    cutQounterConfig.AddMember("SeparateSaberCounts", config.cutQounterConfig.separateSaberCounts, allocator);
    cutQounterConfig.AddMember("SeparateCutValues", config.cutQounterConfig.separateCutValues, allocator);
    cutQounterConfig.AddMember("AveragePrecision", config.cutQounterConfig.averagePrecision, allocator);
    getConfig().config.AddMember("CutConfig", cutQounterConfig, allocator);

    rapidjson::Value missedQounterConfig(rapidjson::kObjectType);
    missedQounterConfig.AddMember("Enabled", config.missedQounterConfig.enabled, allocator);
    missedQounterConfig.AddMember("Distance", config.missedQounterConfig.distance, allocator);
    missedQounterConfig.AddMember("Position", LookupEnumString(config.missedQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    missedQounterConfig.AddMember("CountBadCuts", config.missedQounterConfig.countBadCuts, allocator);
    getConfig().config.AddMember("MissedConfig", missedQounterConfig, allocator);

    rapidjson::Value notesQounterConfig(rapidjson::kObjectType);
    notesQounterConfig.AddMember("Enabled", config.notesQounterConfig.enabled, allocator);
    notesQounterConfig.AddMember("Distance", config.notesQounterConfig.distance, allocator);
    notesQounterConfig.AddMember("Position", LookupEnumString(config.notesQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    notesQounterConfig.AddMember("ShowPercentage", config.notesQounterConfig.showPercentage, allocator);
    notesQounterConfig.AddMember("DecimalPrecision", config.notesQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("NoteConfig", notesQounterConfig, allocator);

    rapidjson::Value notesLeftQounterConfig(rapidjson::kObjectType);
    notesLeftQounterConfig.AddMember("Enabled", config.notesLeftQounterConfig.enabled, allocator);
    notesLeftQounterConfig.AddMember("Distance", config.notesLeftQounterConfig.distance, allocator);
    notesLeftQounterConfig.AddMember("Position", LookupEnumString(config.notesLeftQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    notesLeftQounterConfig.AddMember("LabelAboveCount", config.notesLeftQounterConfig.labelAboveCount, allocator);
    getConfig().config.AddMember("NotesLeftConfig", notesLeftQounterConfig, allocator);

    rapidjson::Value spinometerConfig(rapidjson::kObjectType);
    spinometerConfig.AddMember("Enabled", config.spinometerConfig.enabled, allocator);
    spinometerConfig.AddMember("Distance", config.spinometerConfig.distance, allocator);
    spinometerConfig.AddMember("Position", LookupEnumString(config.spinometerConfig.position, QountersMinus::QounterPositionLookup), allocator);
    spinometerConfig.AddMember("Mode", LookupEnumString(config.spinometerConfig.mode, QountersMinus::SpinometerModeLookup), allocator);
    getConfig().config.AddMember("SpinometerConfig", spinometerConfig, allocator);

    rapidjson::Value speedQounterConfig(rapidjson::kObjectType);
    speedQounterConfig.AddMember("Enabled", config.speedQounterConfig.enabled, allocator);
    speedQounterConfig.AddMember("Distance", config.speedQounterConfig.distance, allocator);
    speedQounterConfig.AddMember("Position", LookupEnumString(config.speedQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    speedQounterConfig.AddMember("Mode", LookupEnumString(config.speedQounterConfig.mode, QountersMinus::SpeedQounterModeLookup), allocator);
    speedQounterConfig.AddMember("DecimalPrecision", config.speedQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("SpeedConfig", speedQounterConfig, allocator);

    rapidjson::Value scoreQounterConfig(rapidjson::kObjectType);
    scoreQounterConfig.AddMember("Enabled", config.scoreQounterConfig.enabled, allocator);
    scoreQounterConfig.AddMember("Distance", config.scoreQounterConfig.distance, allocator);
    scoreQounterConfig.AddMember("Position", LookupEnumString(config.scoreQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    scoreQounterConfig.AddMember("Mode", LookupEnumString(config.scoreQounterConfig.mode, QountersMinus::ScoreQounterModeLookup), allocator);
    scoreQounterConfig.AddMember("DecimalPrecision", config.scoreQounterConfig.decimalPrecision, allocator);
    scoreQounterConfig.AddMember("DisplayRank", config.scoreQounterConfig.displayRank, allocator);
    scoreQounterConfig.AddMember("CustomRankColors", config.scoreQounterConfig.customRankColors, allocator);
    scoreQounterConfig.AddMember("SsColor", FormatColorToHex(config.scoreQounterConfig.ssColor), allocator);
    scoreQounterConfig.AddMember("SColor", FormatColorToHex(config.scoreQounterConfig.sColor), allocator);
    scoreQounterConfig.AddMember("AColor", FormatColorToHex(config.scoreQounterConfig.aColor), allocator);
    scoreQounterConfig.AddMember("BColor", FormatColorToHex(config.scoreQounterConfig.bColor), allocator);
    scoreQounterConfig.AddMember("CColor", FormatColorToHex(config.scoreQounterConfig.cColor), allocator);
    scoreQounterConfig.AddMember("DColor", FormatColorToHex(config.scoreQounterConfig.dColor), allocator);
    scoreQounterConfig.AddMember("EColor", FormatColorToHex(config.scoreQounterConfig.eColor), allocator);
    getConfig().config.AddMember("ScoreConfig", scoreQounterConfig, allocator);

    rapidjson::Value pbQounterConfig(rapidjson::kObjectType);
    pbQounterConfig.AddMember("Enabled", config.pbQounterConfig.enabled, allocator);
    pbQounterConfig.AddMember("Distance", config.pbQounterConfig.distance, allocator);
    pbQounterConfig.AddMember("Position", LookupEnumString(config.pbQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    pbQounterConfig.AddMember("Mode", LookupEnumString(config.pbQounterConfig.mode, QountersMinus::PBQounterModeLookup), allocator);
    pbQounterConfig.AddMember("DecimalPrecision", config.pbQounterConfig.decimalPrecision, allocator);
    pbQounterConfig.AddMember("TextSize", config.pbQounterConfig.textSize, allocator);
    pbQounterConfig.AddMember("Underscore", config.pbQounterConfig.underscore, allocator);
    pbQounterConfig.AddMember("HideFirstScore", config.pbQounterConfig.hideFirstScore, allocator);
    pbQounterConfig.AddMember("BetterColor", FormatColorToHex(config.pbQounterConfig.betterColor), allocator);
    pbQounterConfig.AddMember("DefaultColor", FormatColorToHex(config.pbQounterConfig.defaultColor), allocator);
    getConfig().config.AddMember("PBConfig", pbQounterConfig, allocator);

    rapidjson::Value failQounterConfig(rapidjson::kObjectType);
    failQounterConfig.AddMember("Enabled", config.failQounterConfig.enabled, allocator);
    failQounterConfig.AddMember("Distance", config.failQounterConfig.distance, allocator);
    failQounterConfig.AddMember("Position", LookupEnumString(config.failQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    failQounterConfig.AddMember("ShowRestartsInstead", config.failQounterConfig.showRestartsInstead, allocator);
    getConfig().config.AddMember("FailsConfig", failQounterConfig, allocator);

    rapidjson::Value progressQounterConfig(rapidjson::kObjectType);
    progressQounterConfig.AddMember("Enabled", config.progressQounterConfig.enabled, allocator);
    progressQounterConfig.AddMember("Distance", config.progressQounterConfig.distance, allocator);
    progressQounterConfig.AddMember("Position", LookupEnumString(config.progressQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    progressQounterConfig.AddMember("ProgressTimeLeft", config.progressQounterConfig.progressTimeLeft, allocator);
    progressQounterConfig.AddMember("IncludeRing", config.progressQounterConfig.includeRing, allocator);
    getConfig().config.AddMember("ProgressConfig", progressQounterConfig, allocator);

    getConfig().Write();
}
