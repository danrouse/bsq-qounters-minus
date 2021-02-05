#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "components/Qounter.hpp"
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
    static std::map<int, std::string> SpinometerModeNames = {
        {static_cast<int>(SpinometerMode::Average), "Average"},
        {static_cast<int>(SpinometerMode::SplitAverage), "Split Average"},
        {static_cast<int>(SpinometerMode::Highest), "Highest"}
    };
    static std::map<std::string, int> SpinometerModeLookup = {
        {"Average", static_cast<int>(SpinometerMode::Average)},
        {"SplitAverage", static_cast<int>(SpinometerMode::SplitAverage)},
        {"Highest", static_cast<int>(SpinometerMode::Highest)}
    };
}

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, Spinometer, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(float, Distance);
    DECLARE_STATIC_FIELD(int, Mode);

    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, leftQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, rightQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, leftAngles);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, rightAngles);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, timeSinceLastUpdate, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, highestSpin, 0.0f);

    DECLARE_METHOD(static void, Register);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(Spinometer,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(Mode);

        REGISTER_FIELD(leftQuaternions);
        REGISTER_FIELD(rightQuaternions);
        REGISTER_FIELD(leftAngles);
        REGISTER_FIELD(rightAngles);
        REGISTER_FIELD(timeSinceLastUpdate);
        REGISTER_FIELD(highestSpin);

        REGISTER_METHOD(Register);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
