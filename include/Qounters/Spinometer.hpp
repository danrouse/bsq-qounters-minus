#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"
#include "QounterRegistry.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "System/Collections/Generic/List_1.hpp"

namespace QountersMinus {
    enum class SpinometerMode {
        Average,
        SplitAverage,
        Highest
    };
    static int SpinometerModeCount = 3;
    static std::unordered_map<int, std::string> SpinometerModeNames = {
        {static_cast<int>(SpinometerMode::Average), "Average"},
        {static_cast<int>(SpinometerMode::SplitAverage), "Split Average"},
        {static_cast<int>(SpinometerMode::Highest), "Highest"}
    };
    static std::unordered_map<std::string, int> SpinometerModeLookup = {
        {"Average", static_cast<int>(SpinometerMode::Average)},
        {"SplitAverage", static_cast<int>(SpinometerMode::SplitAverage)},
        {"Highest", static_cast<int>(SpinometerMode::Highest)}
    };
}

DECLARE_CLASS_CUSTOM(QountersMinus::Qounters, Spinometer, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static int Mode;

    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, leftQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, rightQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, leftAngles);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, rightAngles);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, timeSinceLastUpdate, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, highestSpin, 0.0f);

    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, Update);
)
