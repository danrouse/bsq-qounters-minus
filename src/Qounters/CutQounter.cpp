#include "Qounters/CutQounter.hpp"

extern QountersMinus::ModConfig config;

DEFINE_CLASS(QountersMinus::Qounters::CutQounter);

QountersMinus::Qounter* QountersMinus::Qounters::CutQounter::Initialize() {
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::CutQounter*>(
        config.CutQounterConfig.position, config.CutQounterConfig.distance
    );
}

void QountersMinus::Qounters::CutQounter::Start() {
    CreateBasicTitle("Average Cut");

    auto defaultText = FormatNumber(0.0f, config.CutQounterConfig.averagePrecision);
    if (config.CutQounterConfig.separateCutValues) {
        defaultText = defaultText + "\n" + defaultText + "\n" + defaultText;
    }
    auto fontSize = config.CutQounterConfig.separateCutValues ? 28.0f : 35.0f;
    auto xOffset = config.CutQounterConfig.separateSaberCounts ? 20.0f + (12.0f * config.CutQounterConfig.averagePrecision) : 0.0f;
    auto yOffset = config.CutQounterConfig.separateCutValues ? -60.0f : -30.0f;

    leftCutText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), defaultText, false);
    leftCutText->set_alignment(TMPro::TextAlignmentOptions::Center);
    leftCutText->set_fontSize(fontSize);
    leftCutText->set_lineSpacing(-40.0f);
    leftCutText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(xOffset * -1.0f, yOffset));
    if (config.CutQounterConfig.separateSaberCounts) {
        rightCutText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), defaultText, false);
        rightCutText->set_alignment(TMPro::TextAlignmentOptions::Center);
        rightCutText->set_fontSize(fontSize);
        rightCutText->set_lineSpacing(-40.0f);
        rightCutText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(xOffset, yOffset));
    }

    cutScores = il2cpp_utils::New<System::Collections::Generic::List_1<int>*>().value();
}

void QountersMinus::Qounters::CutQounter::UpdateCutScores() {
    int leftBeforeSwingSum = 0, leftAfterSwingSum = 0, leftCutDistanceSum = 0, leftCount = 0,
        rightBeforeSwingSum = 0, rightAfterSwingSum = 0, rightCutDistanceSum = 0, rightCount = 0;
    auto cutScoresArr = cutScores->items;
    for (int i = 0, j = cutScores->get_Count(); i < j; i += 4) {
        if (cutScoresArr->values[i] == 0) {
            leftBeforeSwingSum += cutScoresArr->values[i + 1];
            leftAfterSwingSum += cutScoresArr->values[i + 2];
            leftCutDistanceSum += cutScoresArr->values[i + 3];
            leftCount += 1;
        } else {
            rightBeforeSwingSum += cutScoresArr->values[i + 1];
            rightAfterSwingSum += cutScoresArr->values[i + 2];
            rightCutDistanceSum += cutScoresArr->values[i + 3];
            rightCount += 1;
        }
    }
    if (leftCount == 0) leftCount++;
    if (rightCount == 0) rightCount++;

    if (config.CutQounterConfig.separateCutValues) {
        if (config.CutQounterConfig.separateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)leftBeforeSwingSum / leftCount, config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)leftAfterSwingSum / leftCount, config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)leftCutDistanceSum / leftCount, config.CutQounterConfig.averagePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)rightBeforeSwingSum / rightCount, config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)rightAfterSwingSum / rightCount, config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)rightCutDistanceSum / rightCount, config.CutQounterConfig.averagePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + rightBeforeSwingSum) / (leftCount + rightCount), config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)(leftAfterSwingSum + rightAfterSwingSum) / (leftCount + rightCount), config.CutQounterConfig.averagePrecision) + "\n" +
                FormatNumber((float)(leftCutDistanceSum + rightCutDistanceSum) / (leftCount + rightCount), config.CutQounterConfig.averagePrecision)
            ));
        }
    } else {
        if (config.CutQounterConfig.separateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum) / leftCount, config.CutQounterConfig.averagePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / rightCount, config.CutQounterConfig.averagePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum + rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / (leftCount + rightCount), config.CutQounterConfig.averagePrecision)
            ));
        }
    }
}

void QountersMinus::Qounters::CutQounter::OnSwingRatingFinished(GlobalNamespace::NoteCutInfo* info, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
    int beforeCutScore = 0, afterCutScore = 0, cutDistanceScore = 0;
    GlobalNamespace::ScoreModel::RawScoreWithoutMultiplier(info, beforeCutScore, afterCutScore, cutDistanceScore);
    cutScores->Add((int)info->saberType);
    cutScores->Add(beforeCutScore);
    cutScores->Add(afterCutScore);
    cutScores->Add(cutDistanceScore);
    UpdateCutScores();
}
