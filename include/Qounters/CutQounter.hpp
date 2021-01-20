#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "Qounter.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "System/Collections/Generic/List_1.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, CutQounter, QountersMinus::Qounter,
    DECLARE_STATIC_FIELD(bool, Enabled);
    DECLARE_STATIC_FIELD(int, Position);
    DECLARE_STATIC_FIELD(int, Distance);
    DECLARE_STATIC_FIELD(bool, SeparateSaberCounts);
    DECLARE_STATIC_FIELD(bool, SeparateCutValues);
    DECLARE_STATIC_FIELD(int, AveragePrecision);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, leftCutText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rightCutText);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, cutScores);

    DECLARE_METHOD(static Qounter*, Initialize);
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, OnSwingRatingFinished, GlobalNamespace::NoteCutInfo* info, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter);
    DECLARE_METHOD(void, UpdateCutScores);

    REGISTER_FUNCTION(CutQounter,
        REGISTER_FIELD(Enabled);
        REGISTER_FIELD(Position);
        REGISTER_FIELD(Distance);
        REGISTER_FIELD(SeparateSaberCounts);
        REGISTER_FIELD(SeparateCutValues);
        REGISTER_FIELD(AveragePrecision);

        REGISTER_FIELD(leftCutText);
        REGISTER_FIELD(rightCutText);
        REGISTER_FIELD(cutScores);

        REGISTER_METHOD(Initialize);
        REGISTER_METHOD(Start);
        REGISTER_METHOD(OnSwingRatingFinished);
        REGISTER_METHOD(UpdateCutScores);
    )
)
