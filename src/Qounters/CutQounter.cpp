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

    leftCutScores = il2cpp_utils::New<System::Collections::Generic::List_1<int>*>().value();
    rightCutScores = il2cpp_utils::New<System::Collections::Generic::List_1<int>*>().value();
    leftCutDistanceScores = il2cpp_utils::New<System::Collections::Generic::List_1<int>*>().value();
    rightCutDistanceScores = il2cpp_utils::New<System::Collections::Generic::List_1<int>*>().value();
    leftCutDelegate = il2cpp_utils::MakeDelegate<GlobalNamespace::SwingSaberRatingDidFinishDelegate*>(
        classof(GlobalNamespace::SwingSaberRatingDidFinishDelegate*),
        this,
        +[](QountersMinus::Qounters::CutQounter* self, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
            self->leftCutScores->Add(static_cast<int>(0.5f + (70.0f * swingRatingCounter->get_beforeCutRating())));
            self->leftCutScores->Add(static_cast<int>(0.5f + (30.0f * swingRatingCounter->get_afterCutRating())));
            self->UpdateCutScores();
        }
    );
    rightCutDelegate = il2cpp_utils::MakeDelegate<GlobalNamespace::SwingSaberRatingDidFinishDelegate*>(
        classof(GlobalNamespace::SwingSaberRatingDidFinishDelegate*),
        this,
        +[](QountersMinus::Qounters::CutQounter* self, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
            self->rightCutScores->Add(static_cast<int>(0.5f + (70.0f * swingRatingCounter->get_beforeCutRating())));
            self->rightCutScores->Add(static_cast<int>(0.5f + (30.0f * swingRatingCounter->get_afterCutRating())));
            self->UpdateCutScores();
        }
    );
}

void QountersMinus::Qounters::CutQounter::UpdateCutScores() {
    int leftBeforeSwingSum = 0, leftAfterSwingSum = 0, leftCutDistanceSum = 0, leftCount = 0,
        rightBeforeSwingSum = 0, rightAfterSwingSum = 0, rightCutDistanceSum = 0, rightCount = 0;
    auto leftCutScoresArr = leftCutScores->items, rightCutScoresArr = rightCutScores->items,
         leftCutDistanceScoresArr = leftCutDistanceScores->items, rightCutDistanceScoresArr = rightCutDistanceScores->items;
    for (int i = 0, j = leftCutScores->get_Count(); i < j; i += 2) {
        leftBeforeSwingSum += leftCutScoresArr->values[i];
        leftAfterSwingSum += leftCutScoresArr->values[i + 1];
        leftCount += 1;
    }
    for (int i = 0, j = leftCutDistanceScores->get_Count(); i < j; i++) {
        leftCutDistanceSum += leftCutDistanceScoresArr->values[i];
    }
    for (int i = 0, j = rightCutScores->get_Count(); i < j; i += 2) {
        rightBeforeSwingSum += rightCutScoresArr->values[i];
        rightAfterSwingSum += rightCutScoresArr->values[i + 1];
        rightCount += 1;
    }
    for (int i = 0, j = rightCutDistanceScores->get_Count(); i < j; i++) {
        rightCutDistanceSum += rightCutDistanceScoresArr->values[i];
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
    const int cutDistanceScore = static_cast<int>(0.5f + (15.0f * (1.0f - std::clamp(info->cutDistanceToCenter / 0.3f, 0.0f, 1.0f))));
    if ((int)info->saberType == 0) {
        leftCutDistanceScores->Add(cutDistanceScore);
        info->swingRatingCounter->add_didFinishEvent(leftCutDelegate);
    } else {
        rightCutDistanceScores->Add(cutDistanceScore);
        info->swingRatingCounter->add_didFinishEvent(rightCutDelegate);
    }
}
