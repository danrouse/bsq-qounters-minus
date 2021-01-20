#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"

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
    static std::map<SpeedQounterMode, std::string> SpeedQounterModeNames = {
        {SpeedQounterMode::Average, "Average"},
        {SpeedQounterMode::Top5Sec, "Top from 5 Seconds"},
        {SpeedQounterMode::Both, "Both Metrics"},
        {SpeedQounterMode::SplitAverage, "Split Average"},
        {SpeedQounterMode::SplitBoth, "Split Both Metrics"}
    };
    static std::map<std::string, SpeedQounterMode> SpeedQounterModeLookup = {
        {"Average", SpeedQounterMode::Average},
        {"Top5Sec", SpeedQounterMode::Top5Sec},
        {"Both", SpeedQounterMode::Both},
        {"SplitAverage", SpeedQounterMode::SplitAverage},
        {"SplitBoth", SpeedQounterMode::SplitBoth}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, SpeedQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(int, Distance);
    DECLARE_STATIC_FIELD(int, Mode);
    DECLARE_STATIC_FIELD(bool, SeparateCutValues);
    DECLARE_STATIC_FIELD(int, DecimalPrecision);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, averageText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, fastestText);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, leftSpeeds);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, rightSpeeds);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, fastestSpeeds);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, lastUpdated, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, lastUpdatedFastest, 0.0f);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(SpeedQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(Mode);
        REGISTER_FIELD(SeparateCutValues);
        REGISTER_FIELD(DecimalPrecision);

        REGISTER_FIELD(averageText);
        REGISTER_FIELD(fastestText);
        REGISTER_FIELD(leftSpeeds);
        REGISTER_FIELD(rightSpeeds);
        REGISTER_FIELD(fastestSpeeds);
        REGISTER_FIELD(lastUpdated);
        REGISTER_FIELD(lastUpdatedFastest);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
