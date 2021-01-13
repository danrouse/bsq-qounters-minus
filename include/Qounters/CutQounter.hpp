#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "Qounter.hpp"
#include "config/CutQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "System/Collections/Generic/List_1.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, CutQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, leftCutText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rightCutText);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, cutScores);

    DECLARE_INSTANCE_FIELD(bool, separateCutValues);
    DECLARE_INSTANCE_FIELD(bool, separateSaberCounts);
    DECLARE_INSTANCE_FIELD(int, averagePrecision);

    DECLARE_METHOD(void, OnSwingRatingFinished, GlobalNamespace::NoteCutInfo* info, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter);
    DECLARE_METHOD(void, UpdateCutScores);

    REGISTER_FUNCTION(CutQounter,
        REGISTER_FIELD(leftCutText);
        REGISTER_FIELD(rightCutText);
        REGISTER_FIELD(cutScores);

        REGISTER_FIELD(separateCutValues);
        REGISTER_FIELD(separateSaberCounts);
        REGISTER_FIELD(averagePrecision);

        REGISTER_METHOD(OnSwingRatingFinished);
        REGISTER_METHOD(UpdateCutScores);
    )

    public:
        void Configure(QountersMinus::CutQounterConfig config);
)
