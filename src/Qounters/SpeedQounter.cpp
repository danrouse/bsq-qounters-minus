#include "Qounters/SpeedQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::SpeedQounter);

float Max(System::Collections::Generic::List_1<float>* list) {
    float max = 0.0f;
    for (int i = 0; i < list->get_Count(); i++) {
        auto val = list->get_Item(i);
        if (val > max) max = val;
    }
    return max;
}
float Average(System::Collections::Generic::List_1<float>* list) {
    float sum = 0.0f;
    int count = list->get_Count();
    for (int i = 0; i < count; i++) {
        sum += list->get_Item(i);
    }
    return sum / count;
}

void QountersMinus::Qounters::SpeedQounter::Configure(QountersMinus::SpeedQounterConfig config) {
    mode = (int)config.mode;
    decimalPrecision = config.decimalPrecision;

    if (config.mode != QountersMinus::SpeedQounterMode::Top5Sec) {
        CreateBasicTitle("Average Speed");

        averageText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "0", false);
        averageText->set_alignment(TMPro::TextAlignmentOptions::Center);
        averageText->set_fontSize(35.0f);
        averageText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
    }
    if (config.mode != QountersMinus::SpeedQounterMode::Average && config.mode != QountersMinus::SpeedQounterMode::SplitAverage) {
        auto titleText = CreateBasicTitle("Recent Top Speed");
        auto titleYOffset = 0.0f;
        auto textYOffset = -30.0f;
        if (config.mode == QountersMinus::SpeedQounterMode::Both || config.mode == QountersMinus::SpeedQounterMode::SplitBoth) {
            titleYOffset = -60.0f;
            textYOffset = -90.0f;
        }
        titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, titleYOffset));

        fastestText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "0", false);
        fastestText->set_alignment(TMPro::TextAlignmentOptions::Center);
        fastestText->set_fontSize(35.0f);
        fastestText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, textYOffset));
    }

    leftSpeeds = il2cpp_utils::New<System::Collections::Generic::List_1<float>*>().value();
    rightSpeeds = il2cpp_utils::New<System::Collections::Generic::List_1<float>*>().value();
    fastestSpeeds = il2cpp_utils::New<System::Collections::Generic::List_1<float>*>().value();

    saberManager = UnityEngine::Object::FindObjectOfType<GlobalNamespace::SaberManager*>();
}

void QountersMinus::Qounters::SpeedQounter::Update() {
    auto dt = UnityEngine::Time::get_deltaTime();
    lastUpdated += dt;
    if (lastUpdated > 0.25f) {
        lastUpdated = 0.0f;
        switch (mode) {
            case (int)QountersMinus::SpeedQounterMode::Average:
                rightSpeeds->Add((saberManager->rightSaber->get_bladeSpeed() + saberManager->leftSaber->get_bladeSpeed()) / 2.0f);
                averageText->set_text(il2cpp_utils::createcsstr(FormatNumber(Average(rightSpeeds), decimalPrecision)));
                break;
            case (int)QountersMinus::SpeedQounterMode::Top5Sec:
                fastestSpeeds->Add((saberManager->rightSaber->get_bladeSpeed() + saberManager->leftSaber->get_bladeSpeed()) / 2.0f);
                break;
            case (int)QountersMinus::SpeedQounterMode::Both:
                fastestSpeeds->Add((saberManager->rightSaber->get_bladeSpeed() + saberManager->leftSaber->get_bladeSpeed()) / 2.0f);
                rightSpeeds->Add((saberManager->rightSaber->get_bladeSpeed() + saberManager->leftSaber->get_bladeSpeed()) / 2.0f);
                averageText->set_text(il2cpp_utils::createcsstr(FormatNumber(Average(rightSpeeds), decimalPrecision)));
                break;
            case (int)QountersMinus::SpeedQounterMode::SplitAverage:
                rightSpeeds->Add(saberManager->rightSaber->get_bladeSpeed());
                leftSpeeds->Add(saberManager->leftSaber->get_bladeSpeed());
                averageText->set_text(il2cpp_utils::createcsstr(FormatNumber(Average(leftSpeeds), decimalPrecision) + " | " + FormatNumber(Average(rightSpeeds), decimalPrecision)));
                break;
            case (int)QountersMinus::SpeedQounterMode::SplitBoth:
                fastestSpeeds->Add((saberManager->rightSaber->get_bladeSpeed() + saberManager->leftSaber->get_bladeSpeed()) / 2.0f);
                rightSpeeds->Add(saberManager->rightSaber->get_bladeSpeed());
                leftSpeeds->Add(saberManager->leftSaber->get_bladeSpeed());
                averageText->set_text(il2cpp_utils::createcsstr(FormatNumber(Average(leftSpeeds), decimalPrecision) + " | " + FormatNumber(Average(rightSpeeds), decimalPrecision)));
                break;
        }
    }

    lastUpdatedFastest += dt;
    if (lastUpdatedFastest >= 5.0f) {
        lastUpdatedFastest = 0.0f;
        if (fastestText) {
            auto top = Max(fastestSpeeds);
            fastestSpeeds->Clear();
            fastestText->set_text(il2cpp_utils::createcsstr(FormatNumber(top, decimalPrecision)));
        }
    }
}
