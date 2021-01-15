#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/SpinometerConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "System/Collections/Generic/List_1.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, Spinometer, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, leftQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<UnityEngine::Quaternion>*, rightQuaternions);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, leftAngles);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<float>*, rightAngles);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, timeSinceLastUpdate, 0.0f);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, highestSpin, 0.0f);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, Update);

    REGISTER_FUNCTION(Spinometer,
        REGISTER_FIELD(leftQuaternions);
        REGISTER_FIELD(rightQuaternions);
        REGISTER_FIELD(leftAngles);
        REGISTER_FIELD(rightAngles);
        REGISTER_FIELD(timeSinceLastUpdate);
        REGISTER_FIELD(highestSpin);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(Update);
    )
)
