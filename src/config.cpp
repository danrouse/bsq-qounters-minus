#include "config.hpp"
#include "util/logger.hpp"

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
        config.CutQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.CutQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.CutQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "SeparateSaberCounts", config.CutQounterConfig.separateSaberCounts, Bool);
        LoadConfigVar(qounterConfig, "SeparateCutValues", config.CutQounterConfig.separateCutValues, Bool);
        LoadConfigVar(qounterConfig, "AveragePrecision", config.CutQounterConfig.averagePrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("MissedConfig") && getConfig().config["MissedConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["MissedConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.MissedQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.MissedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.MissedQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "CountBadCuts", config.MissedQounterConfig.countBadCuts, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("NoteConfig") && getConfig().config["NoteConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["NoteConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.NotesQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.NotesQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.NotesQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ShowPercentage", config.NotesQounterConfig.showPercentage, Bool);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.NotesQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("NotesLeftConfig") && getConfig().config["NotesLeftConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["NotesLeftConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.NotesLeftQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];

        LoadConfigVar(qounterConfig, "Enabled", config.NotesLeftQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.NotesLeftQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "LabelAboveCount", config.NotesLeftQounterConfig.labelAboveCount, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("SpinometerConfig") && getConfig().config["SpinometerConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["SpinometerConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.SpinometerConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.SpinometerConfig.mode = QountersMinus::SpinometerModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.SpinometerConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.SpinometerConfig.distance, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("SpeedConfig") && getConfig().config["SpeedConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["SpeedConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.SpeedQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.SpeedQounterConfig.mode = QountersMinus::SpeedQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.SpeedQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.SpeedQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.SpeedQounterConfig.decimalPrecision, Int);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("ScoreConfig") && getConfig().config["ScoreConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["ScoreConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.ScoreQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.ScoreQounterConfig.mode = QountersMinus::ScoreQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.ScoreQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.ScoreQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.ScoreQounterConfig.decimalPrecision, Int);
        LoadConfigVar(qounterConfig, "DisplayRank", config.ScoreQounterConfig.displayRank, Bool);
        LoadConfigVar(qounterConfig, "CustomRankColors", config.ScoreQounterConfig.customRankColors, Bool);
        LoadConfigVarColor(qounterConfig, "SSColor", config.ScoreQounterConfig.ssColor);
        LoadConfigVarColor(qounterConfig, "SColor", config.ScoreQounterConfig.sColor);
        LoadConfigVarColor(qounterConfig, "AColor", config.ScoreQounterConfig.aColor);
        LoadConfigVarColor(qounterConfig, "BColor", config.ScoreQounterConfig.bColor);
        LoadConfigVarColor(qounterConfig, "CColor", config.ScoreQounterConfig.cColor);
        LoadConfigVarColor(qounterConfig, "DColor", config.ScoreQounterConfig.dColor);
        LoadConfigVarColor(qounterConfig, "EColor", config.ScoreQounterConfig.eColor);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("PBConfig") && getConfig().config["PBConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["PBConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.PBQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.PBQounterConfig.mode = QountersMinus::PBQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.PBQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.PBQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "DecimalPrecision", config.PBQounterConfig.decimalPrecision, Int);
        LoadConfigVar(qounterConfig, "TextSize", config.PBQounterConfig.textSize, Int);
        LoadConfigVar(qounterConfig, "UnderScore", config.PBQounterConfig.underScore, Bool);
        LoadConfigVar(qounterConfig, "HideFirstScore", config.PBQounterConfig.hideFirstScore, Bool);
        LoadConfigVarColor(qounterConfig, "BetterColor", config.PBQounterConfig.betterColor);
        LoadConfigVarColor(qounterConfig, "DefaultColor", config.PBQounterConfig.defaultColor);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("FailsConfig") && getConfig().config["FailsConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["FailsConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.FailQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        LoadConfigVar(qounterConfig, "Enabled", config.FailQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.FailQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ShowRestartsInstead", config.FailQounterConfig.showRestartsInstead, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("ProgressConfig") && getConfig().config["ProgressConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["ProgressConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.ProgressQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        std::string tmpMode;
        LoadConfigVar(qounterConfig, "Mode", tmpMode, String);
        config.ProgressQounterConfig.mode = QountersMinus::ProgressQounterModeLookup[tmpMode];
        LoadConfigVar(qounterConfig, "Enabled", config.ProgressQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.ProgressQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "ProgressTimeLeft", config.ProgressQounterConfig.progressTimeLeft, Bool);
        LoadConfigVar(qounterConfig, "IncludeRing", config.ProgressQounterConfig.includeRing, Bool);
    } else {
        foundEverything = false;
    }
    if (getConfig().config.HasMember("PPConfig") && getConfig().config["PPConfig"].IsObject()) {
        auto qounterConfig = getConfig().config["PPConfig"].GetObject();
        std::string tmpQounterPosition;
        LoadConfigVar(qounterConfig, "Position", tmpQounterPosition, String);
        config.PPQounterConfig.position = QountersMinus::QounterPositionLookup[tmpQounterPosition];
        LoadConfigVar(qounterConfig, "Enabled", config.PPQounterConfig.enabled, Bool);
        LoadConfigVar(qounterConfig, "Distance", config.PPQounterConfig.distance, Int);
        LoadConfigVar(qounterConfig, "HideWhenUnranked", config.PPQounterConfig.hideWhenUnranked, Bool);
    } else {
        foundEverything = false;
    }

    LOG_DEBUG("Found all: %d", foundEverything);
    return foundEverything;
}

void QountersMinus::SaveConfig() {
    LOG_CALLER;

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
    cutQounterConfig.AddMember("Enabled", config.CutQounterConfig.enabled, allocator);
    cutQounterConfig.AddMember("Distance", config.CutQounterConfig.distance, allocator);
    cutQounterConfig.AddMember("Position", LookupEnumString(config.CutQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    cutQounterConfig.AddMember("SeparateSaberCounts", config.CutQounterConfig.separateSaberCounts, allocator);
    cutQounterConfig.AddMember("SeparateCutValues", config.CutQounterConfig.separateCutValues, allocator);
    cutQounterConfig.AddMember("AveragePrecision", config.CutQounterConfig.averagePrecision, allocator);
    getConfig().config.AddMember("CutConfig", cutQounterConfig, allocator);

    rapidjson::Value missedQounterConfig(rapidjson::kObjectType);
    missedQounterConfig.AddMember("Enabled", config.MissedQounterConfig.enabled, allocator);
    missedQounterConfig.AddMember("Distance", config.MissedQounterConfig.distance, allocator);
    missedQounterConfig.AddMember("Position", LookupEnumString(config.MissedQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    missedQounterConfig.AddMember("CountBadCuts", config.MissedQounterConfig.countBadCuts, allocator);
    getConfig().config.AddMember("MissedConfig", missedQounterConfig, allocator);

    rapidjson::Value notesQounterConfig(rapidjson::kObjectType);
    notesQounterConfig.AddMember("Enabled", config.NotesQounterConfig.enabled, allocator);
    notesQounterConfig.AddMember("Distance", config.NotesQounterConfig.distance, allocator);
    notesQounterConfig.AddMember("Position", LookupEnumString(config.NotesQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    notesQounterConfig.AddMember("ShowPercentage", config.NotesQounterConfig.showPercentage, allocator);
    notesQounterConfig.AddMember("DecimalPrecision", config.NotesQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("NoteConfig", notesQounterConfig, allocator);

    rapidjson::Value notesLeftQounterConfig(rapidjson::kObjectType);
    notesLeftQounterConfig.AddMember("Enabled", config.NotesLeftQounterConfig.enabled, allocator);
    notesLeftQounterConfig.AddMember("Distance", config.NotesLeftQounterConfig.distance, allocator);
    notesLeftQounterConfig.AddMember("Position", LookupEnumString(config.NotesLeftQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    notesLeftQounterConfig.AddMember("LabelAboveCount", config.NotesLeftQounterConfig.labelAboveCount, allocator);
    getConfig().config.AddMember("NotesLeftConfig", notesLeftQounterConfig, allocator);

    rapidjson::Value spinometerConfig(rapidjson::kObjectType);
    spinometerConfig.AddMember("Enabled", config.SpinometerConfig.enabled, allocator);
    spinometerConfig.AddMember("Distance", config.SpinometerConfig.distance, allocator);
    spinometerConfig.AddMember("Position", LookupEnumString(config.SpinometerConfig.position, QountersMinus::QounterPositionLookup), allocator);
    spinometerConfig.AddMember("Mode", LookupEnumString(config.SpinometerConfig.mode, QountersMinus::SpinometerModeLookup), allocator);
    getConfig().config.AddMember("SpinometerConfig", spinometerConfig, allocator);

    rapidjson::Value speedQounterConfig(rapidjson::kObjectType);
    speedQounterConfig.AddMember("Enabled", config.SpeedQounterConfig.enabled, allocator);
    speedQounterConfig.AddMember("Distance", config.SpeedQounterConfig.distance, allocator);
    speedQounterConfig.AddMember("Position", LookupEnumString(config.SpeedQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    speedQounterConfig.AddMember("Mode", LookupEnumString(config.SpeedQounterConfig.mode, QountersMinus::SpeedQounterModeLookup), allocator);
    speedQounterConfig.AddMember("DecimalPrecision", config.SpeedQounterConfig.decimalPrecision, allocator);
    getConfig().config.AddMember("SpeedConfig", speedQounterConfig, allocator);

    rapidjson::Value scoreQounterConfig(rapidjson::kObjectType);
    scoreQounterConfig.AddMember("Enabled", config.ScoreQounterConfig.enabled, allocator);
    scoreQounterConfig.AddMember("Distance", config.ScoreQounterConfig.distance, allocator);
    scoreQounterConfig.AddMember("Position", LookupEnumString(config.ScoreQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    scoreQounterConfig.AddMember("Mode", LookupEnumString(config.ScoreQounterConfig.mode, QountersMinus::ScoreQounterModeLookup), allocator);
    scoreQounterConfig.AddMember("DecimalPrecision", config.ScoreQounterConfig.decimalPrecision, allocator);
    scoreQounterConfig.AddMember("DisplayRank", config.ScoreQounterConfig.displayRank, allocator);
    scoreQounterConfig.AddMember("CustomRankColors", config.ScoreQounterConfig.customRankColors, allocator);
    scoreQounterConfig.AddMember("SSColor", FormatColorToHex(config.ScoreQounterConfig.ssColor), allocator);
    scoreQounterConfig.AddMember("SColor", FormatColorToHex(config.ScoreQounterConfig.sColor), allocator);
    scoreQounterConfig.AddMember("AColor", FormatColorToHex(config.ScoreQounterConfig.aColor), allocator);
    scoreQounterConfig.AddMember("BColor", FormatColorToHex(config.ScoreQounterConfig.bColor), allocator);
    scoreQounterConfig.AddMember("CColor", FormatColorToHex(config.ScoreQounterConfig.cColor), allocator);
    scoreQounterConfig.AddMember("DColor", FormatColorToHex(config.ScoreQounterConfig.dColor), allocator);
    scoreQounterConfig.AddMember("EColor", FormatColorToHex(config.ScoreQounterConfig.eColor), allocator);
    getConfig().config.AddMember("ScoreConfig", scoreQounterConfig, allocator);

    rapidjson::Value pbQounterConfig(rapidjson::kObjectType);
    pbQounterConfig.AddMember("Enabled", config.PBQounterConfig.enabled, allocator);
    pbQounterConfig.AddMember("Distance", config.PBQounterConfig.distance, allocator);
    pbQounterConfig.AddMember("Position", LookupEnumString(config.PBQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    pbQounterConfig.AddMember("Mode", LookupEnumString(config.PBQounterConfig.mode, QountersMinus::PBQounterModeLookup), allocator);
    pbQounterConfig.AddMember("DecimalPrecision", config.PBQounterConfig.decimalPrecision, allocator);
    pbQounterConfig.AddMember("TextSize", config.PBQounterConfig.textSize, allocator);
    pbQounterConfig.AddMember("UnderScore", config.PBQounterConfig.underScore, allocator);
    pbQounterConfig.AddMember("HideFirstScore", config.PBQounterConfig.hideFirstScore, allocator);
    pbQounterConfig.AddMember("BetterColor", FormatColorToHex(config.PBQounterConfig.betterColor), allocator);
    pbQounterConfig.AddMember("DefaultColor", FormatColorToHex(config.PBQounterConfig.defaultColor), allocator);
    getConfig().config.AddMember("PBConfig", pbQounterConfig, allocator);

    rapidjson::Value failQounterConfig(rapidjson::kObjectType);
    failQounterConfig.AddMember("Enabled", config.FailQounterConfig.enabled, allocator);
    failQounterConfig.AddMember("Distance", config.FailQounterConfig.distance, allocator);
    failQounterConfig.AddMember("Position", LookupEnumString(config.FailQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    failQounterConfig.AddMember("ShowRestartsInstead", config.FailQounterConfig.showRestartsInstead, allocator);
    getConfig().config.AddMember("FailsConfig", failQounterConfig, allocator);

    rapidjson::Value progressQounterConfig(rapidjson::kObjectType);
    progressQounterConfig.AddMember("Enabled", config.ProgressQounterConfig.enabled, allocator);
    progressQounterConfig.AddMember("Distance", config.ProgressQounterConfig.distance, allocator);
    progressQounterConfig.AddMember("Position", LookupEnumString(config.ProgressQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    progressQounterConfig.AddMember("Mode", LookupEnumString(config.ProgressQounterConfig.mode, QountersMinus::ProgressQounterModeLookup), allocator);
    progressQounterConfig.AddMember("ProgressTimeLeft", config.ProgressQounterConfig.progressTimeLeft, allocator);
    progressQounterConfig.AddMember("IncludeRing", config.ProgressQounterConfig.includeRing, allocator);
    getConfig().config.AddMember("ProgressConfig", progressQounterConfig, allocator);

    rapidjson::Value ppQounterConfig(rapidjson::kObjectType);
    ppQounterConfig.AddMember("Enabled", config.PPQounterConfig.enabled, allocator);
    ppQounterConfig.AddMember("Distance", config.PPQounterConfig.distance, allocator);
    ppQounterConfig.AddMember("Position", LookupEnumString(config.PPQounterConfig.position, QountersMinus::QounterPositionLookup), allocator);
    ppQounterConfig.AddMember("HideWhenUnranked", config.PPQounterConfig.hideWhenUnranked, allocator);
    getConfig().config.AddMember("PPConfig", ppQounterConfig, allocator);

    getConfig().Write();
}
