#pragma once

#include "QounterConfig.hpp"

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
        ScoreQounterMode mode = ScoreQounterMode::Original;
        bool customRankColors = true;
    } ScoreQounterConfig;
}
