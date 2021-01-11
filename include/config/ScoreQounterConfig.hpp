#pragma once

#include "QounterConfig.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/RankModel_Rank.hpp"

namespace QountersMinus {
    enum class ScoreQounterMode {
        Original,
        LeavePoints,
        ScoreOnly,
        RankOnly
    };
    static int ScoreQounterModeCount = 4;
    static std::map<ScoreQounterMode, std::string> ScoreQounterModeNames = {
        {ScoreQounterMode::Original, "Original"},
        {ScoreQounterMode::LeavePoints, "Don't Move Points"},
        {ScoreQounterMode::ScoreOnly, "Remove Rank"},
        {ScoreQounterMode::RankOnly, "Remove Percentage"}
    };

    typedef struct _ScoreQounterConfig : QounterConfig {
        QounterPosition position = QounterPosition::BelowMultiplier;
        bool enabled = true;
        int distance = 0;
        ScoreQounterMode mode = ScoreQounterMode::Original;
        int decimalPrecision = 2;
        bool displayRank = true; // unused?
        bool customRankColors = true;
        UnityEngine::Color ssColor = UnityEngine::Color(0.0f, 1.0f, 1.0f, 1.0f);
        UnityEngine::Color sColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);
        UnityEngine::Color aColor = UnityEngine::Color(0.0f, 1.0f, 0.0f, 1.0f);
        UnityEngine::Color bColor = UnityEngine::Color(1.0f, 0.92f, 0.016f, 1.0f);
        UnityEngine::Color cColor = UnityEngine::Color(1.0f, 0.5f, 0.0f, 1.0f);
        UnityEngine::Color dColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);
        UnityEngine::Color eColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);

        // UnityEngine::Color GetColorFromRank(GlobalNamespace::RankModel::Rank rank) {
        //     switch (rank) {
        //         case GlobalNamespace::RankModel::Rank::S: return sColor;
        //         case GlobalNamespace::RankModel::Rank::A: return aColor;
        //         case GlobalNamespace::RankModel::Rank::B: return bColor;
        //         case GlobalNamespace::RankModel::Rank::C: return cColor;
        //         case GlobalNamespace::RankModel::Rank::D: return dColor;
        //         case GlobalNamespace::RankModel::Rank::E: return eColor;
        //         default: return ssColor;
        //     }
        // }
    } ScoreQounterConfig;
}
