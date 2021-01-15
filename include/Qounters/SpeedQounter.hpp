#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "config.hpp"
#include "Qounter.hpp"
#include "config/SpeedQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, SpeedQounter, QountersMinus::Qounter,
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
