#include "Qounters/Spinometer.hpp"

DEFINE_CLASS(QountersMinus::Qounters::Spinometer);

std::string SpeedToColor(float speed) {
    static auto orange = UnityEngine::Color(1.0f, 0.647f, 0.0f, 1.0f);
    auto color = UnityEngine::Color::Lerp(UnityEngine::Color::get_white(), orange, speed / 3600.0f);
    if (speed >= 3600) color = UnityEngine::Color::get_red();
    return FormatColorToHex(color.r, color.g, color.b);
}

int Sum(System::Collections::Generic::List_1<float>* list) {
    float sum = 0.0f;
    for (int i = 0; i < list->get_Count(); i++) {
        sum += list->get_Item(i);
    }
    return sum;
}

void QountersMinus::Qounters::Spinometer::Configure(QountersMinus::SpinometerConfig config) {
    mode = (int)config.mode;

    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "Spinometer", false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(20.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));

    text = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), "0", false);
    text->set_alignment(TMPro::TextAlignmentOptions::Center);
    text->set_fontSize(35.0f);
    text->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));

    leftQuaternions = il2cpp_utils::New<System::Collections::Generic::List_1<UnityEngine::Quaternion>*>().value();
    rightQuaternions = il2cpp_utils::New<System::Collections::Generic::List_1<UnityEngine::Quaternion>*>().value();
    leftAngles = il2cpp_utils::New<System::Collections::Generic::List_1<float>*>().value();
    rightAngles = il2cpp_utils::New<System::Collections::Generic::List_1<float>*>().value();

    saberManager = QuestUI::ArrayUtil::First<GlobalNamespace::SaberManager>(
        UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SaberManager*>(),
        [](GlobalNamespace::SaberManager* x) { return x->get_enabled(); }
    );
}

void QountersMinus::Qounters::Spinometer::Update() {
    timeSinceLastUpdate += UnityEngine::Time::get_deltaTime();
    leftQuaternions->Add(saberManager->leftSaber->get_transform()->get_rotation());
    rightQuaternions->Add(saberManager->rightSaber->get_transform()->get_rotation());
    auto leftQuaternionsCount = leftQuaternions->get_Count();
    auto rightQuaternionsCount = rightQuaternions->get_Count();
    if (leftQuaternionsCount >= 2 && rightQuaternionsCount >= 2) {
        leftAngles->Add(UnityEngine::Quaternion::Angle(
            leftQuaternions->get_Item(leftQuaternionsCount - 1),
            leftQuaternions->get_Item(leftQuaternionsCount - 2))
        );
        rightAngles->Add(UnityEngine::Quaternion::Angle(
            rightQuaternions->get_Item(rightQuaternionsCount - 1),
            rightQuaternions->get_Item(rightQuaternionsCount - 2))
        );
    }

    if (timeSinceLastUpdate < 1.0f) return;
    timeSinceLastUpdate = 0.0f;
    leftQuaternions->Clear();
    rightQuaternions->Clear();
    auto leftSpeed = Sum(leftAngles);
    auto rightSpeed = Sum(rightAngles);
    leftAngles->Clear();
    rightAngles->Clear();
    auto averageSpeed = (leftSpeed + rightSpeed) / 2.0f;
    if (leftSpeed > highestSpin) highestSpin = leftSpeed;
    if (rightSpeed > highestSpin) highestSpin = rightSpeed;

    std::string nextText;
    if (mode == (int)QountersMinus::SpinometerMode::Average) {
        nextText = "<color=#" + SpeedToColor(averageSpeed) + ">" + std::to_string((int)roundf(averageSpeed)) + "</color>";
    } else if (mode == (int)QountersMinus::SpinometerMode::Highest) {
        nextText = "<color=#" + SpeedToColor(highestSpin) + ">" + std::to_string((int)roundf(highestSpin)) + "</color>";
    } else if (mode == (int)QountersMinus::SpinometerMode::SplitAverage) {
        nextText = "<color=#" + SpeedToColor(leftSpeed) + ">" + std::to_string((int)roundf(leftSpeed)) + "</color> | " +
                   "<color=#" + SpeedToColor(rightSpeed) + ">" + std::to_string((int)roundf(rightSpeed)) + "</color>";
    }
    text->set_text(il2cpp_utils::createcsstr(nextText));
}
