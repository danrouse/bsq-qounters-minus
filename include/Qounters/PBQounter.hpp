#pragma once

#include "util/logger.hpp"
#include "util/format.hpp"
#include "util/note_count.hpp"
#include "Qounter.hpp"
#include "config/PBQounterConfig.hpp"

#include "custom-types/shared/macros.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/ScoreUIController.hpp"
#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerLevelStatsData.hpp"
#include "GlobalNamespace/RelativeScoreAndImmediateRankCounter.hpp"
#include "UnityEngine/Resources.hpp"

DECLARE_CLASS_CODEGEN(QountersMinus::Qounters, PBQounter, QountersMinus::Qounter,
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, pbText);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, maxPossibleScore, 0);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, highScore, 0);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::RelativeScoreAndImmediateRankCounter*, relativeScoreAndImmediateRankCounter);

    DECLARE_INSTANCE_FIELD(int, mode);
    DECLARE_INSTANCE_FIELD(int, decimalPrecision);
    DECLARE_INSTANCE_FIELD(bool, hideFirstScore);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, betterColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, defaultColor);

    DECLARE_METHOD(void, OnScoreUpdated, int modifiedScore);
    DECLARE_METHOD(void, SetPersonalBest, float ratioOfMaxScore);

    REGISTER_FUNCTION(PBQounter,
        REGISTER_FIELD(pbText);
        REGISTER_FIELD(maxPossibleScore);
        REGISTER_FIELD(highScore);
        REGISTER_FIELD(relativeScoreAndImmediateRankCounter);

        REGISTER_FIELD(mode);
        REGISTER_FIELD(decimalPrecision);
        REGISTER_FIELD(hideFirstScore);
        REGISTER_FIELD(betterColor);
        REGISTER_FIELD(defaultColor);

        REGISTER_METHOD(OnScoreUpdated);
        REGISTER_METHOD(SetPersonalBest);
    )

    public:
        void Configure(QountersMinus::PBQounterConfig config);
)
