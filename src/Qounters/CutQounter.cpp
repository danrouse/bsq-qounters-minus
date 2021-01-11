#include "Qounters/CutQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::CutQounter);

void QountersMinus::Qounters::CutQounter::Configure(QountersMinus::CutQounterConfig config) {
    averagePrecision = config.averagePrecision;
    separateCutValues = config.separateCutValues;
    separateSaberCounts = config.separateSaberCounts;

    CreateBasicTitle("Average Cut");

    auto defaultText = FormatNumber(0.0f, averagePrecision);
    if (separateCutValues) {
        defaultText = defaultText + "\n" + defaultText + "\n" + defaultText;
    }
    auto fontSize = separateCutValues ? 28.0f : 35.0f;
    auto xOffset = separateSaberCounts ? 32.0f : 0.0f;
    auto yOffset = separateCutValues ? -60.0f : -30.0f;

    leftCutText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), defaultText, false);
    leftCutText->set_alignment(TMPro::TextAlignmentOptions::Center);
    leftCutText->set_fontSize(fontSize);
    leftCutText->set_lineSpacing(-40.0f);
    leftCutText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(xOffset * -1.0f, yOffset));
    if (separateSaberCounts) {
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
    for (int i = 0; i < cutScoresArr->Length(); i += 4) {
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

    if (separateCutValues) {
        if (separateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)leftBeforeSwingSum / leftCount, averagePrecision) + "\n" +
                FormatNumber((float)leftAfterSwingSum / leftCount, averagePrecision) + "\n" +
                FormatNumber((float)leftCutDistanceSum / leftCount, averagePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)rightBeforeSwingSum / rightCount, averagePrecision) + "\n" +
                FormatNumber((float)rightAfterSwingSum / rightCount, averagePrecision) + "\n" +
                FormatNumber((float)rightCutDistanceSum / rightCount, averagePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + rightBeforeSwingSum) / (leftCount + rightCount), averagePrecision) + "\n" +
                FormatNumber((float)(leftAfterSwingSum + rightAfterSwingSum) / (leftCount + rightCount), averagePrecision) + "\n" +
                FormatNumber((float)(leftCutDistanceSum + rightCutDistanceSum) / (leftCount + rightCount), averagePrecision)
            ));
        }
    } else {
        if (separateSaberCounts) {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum) / leftCount, averagePrecision)
            ));
            rightCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / rightCount, averagePrecision)
            ));
        } else {
            leftCutText->set_text(il2cpp_utils::createcsstr(
                FormatNumber((float)(leftBeforeSwingSum + leftAfterSwingSum + leftCutDistanceSum + rightBeforeSwingSum + rightAfterSwingSum + rightCutDistanceSum) / (leftCount + rightCount), averagePrecision)
            ));
        }
    }
}

void QountersMinus::Qounters::CutQounter::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (!info->get_allIsOK()) return;
    prevNoteCutInfo = info;
    info->swingRatingCounter->add_didFinishEvent(il2cpp_utils::MakeDelegate<GlobalNamespace::SwingSaberRatingDidFinishDelegate*>(
        classof(GlobalNamespace::SwingSaberRatingDidFinishDelegate*),
        this,
        +[](QountersMinus::Qounters::CutQounter* self) {
            int beforeCutScore, afterCutScore, cutDistanceScore;
            GlobalNamespace::ScoreModel::RawScoreWithoutMultiplier(self->prevNoteCutInfo, beforeCutScore, afterCutScore, cutDistanceScore);
            self->cutScores->Add((int)self->prevNoteCutInfo->saberType);
            self->cutScores->Add(beforeCutScore);
            self->cutScores->Add(afterCutScore);
            self->cutScores->Add(cutDistanceScore);
            self->UpdateCutScores();
        }
    ));
}
