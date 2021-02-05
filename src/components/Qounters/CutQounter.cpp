#include "components/Qounters/CutQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::CutQounter);

bool QountersMinus::Qounters::CutQounter::Enabled = false;
int QountersMinus::Qounters::CutQounter::Position = static_cast<int>(QountersMinus::QounterPosition::AboveHighway);
float QountersMinus::Qounters::CutQounter::Distance = 1.0f;
bool QountersMinus::Qounters::CutQounter::SeparateSaberCounts = false;
bool QountersMinus::Qounters::CutQounter::SeparateCutValues = false;
int QountersMinus::Qounters::CutQounter::AveragePrecision = 1;

void QountersMinus::Qounters::CutQounter::Register() {
    QounterRegistry::Register<CutQounter>("Cut", "Cut Qounter", "CutConfig", true);
    QounterRegistry::RegisterConfig<CutQounter>({
        .ptr = &SeparateSaberCounts,
        .field = "SeparateSaberCounts",
        .displayName = "Separate Saber Cuts",
        .helpText = "Shows the average cut for the left and right sabers separately.",
    });
    QounterRegistry::RegisterConfig<CutQounter>({
        .ptr = &SeparateCutValues,
        .field = "SeparateCutValues",
        .displayName = "Separate Cut Values",
        .helpText = "Show separate averages for angle before cut (0-70), angle after cut (0-30) and distance to center (0-15).",
    });
    QounterRegistry::RegisterConfig<CutQounter>({
        .ptr = &AveragePrecision,
        .field = "AveragePrecision",
        .displayName = "Average Cut Precision",
        .helpText = "How many decimals should be shown on the average cuts?",
        .intMin = 0,
        .intMax = 4,
    });
}

void QountersMinus::Qounters::CutQounter::Start() {
    CreateBasicTitle("Average Cut");

    auto defaultText = FormatNumber(0.0f, AveragePrecision);
    if (SeparateCutValues) {
        defaultText = defaultText + "\n" + defaultText + "\n" + defaultText;
    }
    auto fontSize = SeparateCutValues ? 28.0f : 35.0f;
    auto xOffset = SeparateSaberCounts ? 20.0f + (12.0f * AveragePrecision) : 0.0f;
    auto yOffset = SeparateCutValues ? -60.0f : -30.0f;

    leftCutText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), defaultText, false);
    leftCutText->set_alignment(TMPro::TextAlignmentOptions::Center);
    leftCutText->set_fontSize(fontSize);
    leftCutText->set_lineSpacing(-40.0f);
    leftCutText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(xOffset * -1.0f, yOffset));
    if (SeparateSaberCounts) {
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

    if (SeparateCutValues) {
        if (SeparateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)leftBeforeSwingSum / leftCount, AveragePrecision) + "\n" +
                FormatNumber((float)leftAfterSwingSum / leftCount, AveragePrecision) + "\n" +
                FormatNumber((float)leftCutDistanceSum / leftCount, AveragePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)rightBeforeSwingSum / rightCount, AveragePrecision) + "\n" +
                FormatNumber((float)rightAfterSwingSum / rightCount, AveragePrecision) + "\n" +
                FormatNumber((float)rightCutDistanceSum / rightCount, AveragePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + rightBeforeSwingSum) / (leftCount + rightCount), AveragePrecision) + "\n" +
                FormatNumber((float)(leftAfterSwingSum + rightAfterSwingSum) / (leftCount + rightCount), AveragePrecision) + "\n" +
                FormatNumber((float)(leftCutDistanceSum + rightCutDistanceSum) / (leftCount + rightCount), AveragePrecision)
            ));
        }
    } else {
        if (SeparateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum) / leftCount, AveragePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / rightCount, AveragePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum + rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / (leftCount + rightCount), AveragePrecision)
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
