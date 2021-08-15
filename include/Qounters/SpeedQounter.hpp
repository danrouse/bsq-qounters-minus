#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

namespace QountersMinus {
    enum class SpeedQounterMode {
        Average,
        Top5Sec,
        Both,
        SplitAverage,
        SplitBoth
    };
    static int SpeedQounterModeCount = 5;
    static std::unordered_map<int, std::string> SpeedQounterModeNames = {
        {static_cast<int>(SpeedQounterMode::Average), "Average"},
        {static_cast<int>(SpeedQounterMode::Top5Sec), "Top from 5 Seconds"},
        {static_cast<int>(SpeedQounterMode::Both), "Both Metrics"},
        {static_cast<int>(SpeedQounterMode::SplitAverage), "Split Average"},
        {static_cast<int>(SpeedQounterMode::SplitBoth), "Split Both Metrics"}
    };
    static std::unordered_map<std::string, int> SpeedQounterModeLookup = {
        {"Average", static_cast<int>(SpeedQounterMode::Average)},
        {"Top5Sec", static_cast<int>(SpeedQounterMode::Top5Sec)},
        {"Both", static_cast<int>(SpeedQounterMode::Both)},
        {"SplitAverage", static_cast<int>(SpeedQounterMode::SplitAverage)},
        {"SplitBoth", static_cast<int>(SpeedQounterMode::SplitBoth)}
    };
}

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, SpeedQounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static int Mode;
    static bool SeparateCutValues;
    static int DecimalPrecision;

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, averageText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, fastestText);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, leftSpeeds);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, rightSpeeds);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, fastestSpeeds);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, lastUpdated, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, lastUpdatedFastest, 0.0f);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, Update);
)
