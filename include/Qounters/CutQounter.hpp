#pragma once

#include "logger.hpp"
#include "format.hpp"
#include "Qounter.hpp"
#include "config/CutQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "GlobalNamespace/SwingSaberRatingDidFinishDelegate.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"

typedef System::Collections::Generic::Dictionary_2<GlobalNamespace::ISaberSwingRatingCounter*, GlobalNamespace::NoteCutInfo*>* NoteCutInfosDictionary;

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, CutQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, leftCutText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, rightCutText);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, leftCutScores);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, rightCutScores);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, leftCutDistanceScores);
    DECLARE_INSTANCE_FIELD(System::Collections::Generic::List_1<int>*, rightCutDistanceScores);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::SwingSaberRatingDidFinishDelegate*, leftCutDelegate);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::SwingSaberRatingDidFinishDelegate*, rightCutDelegate);

    DECLARE_INSTANCE_FIELD(bool, separateCutValues);
    DECLARE_INSTANCE_FIELD(bool, separateSaberCounts);
    DECLARE_INSTANCE_FIELD(int, averagePrecision);

    DECLARE_METHOD(void, OnNoteCut, GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info);
    DECLARE_METHOD(void, UpdateCutScores);

    REGISTER_FUNCTION(CutQounter,
        REGISTER_FIELD(leftCutText);
        REGISTER_FIELD(rightCutText);
        REGISTER_FIELD(leftCutScores);
        REGISTER_FIELD(rightCutScores);
        REGISTER_FIELD(leftCutDistanceScores);
        REGISTER_FIELD(rightCutDistanceScores);
        REGISTER_FIELD(leftCutDelegate);
        REGISTER_FIELD(rightCutDelegate);

        REGISTER_FIELD(separateCutValues);
        REGISTER_FIELD(separateSaberCounts);
        REGISTER_FIELD(averagePrecision);

        REGISTER_METHOD(OnNoteCut);
        REGISTER_METHOD(UpdateCutScores);
    )

    public:
        void Configure(QountersMinus::CutQounterConfig config);
)
