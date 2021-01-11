#include "Qounter.hpp"

DEFINE_CLASS(QountersMinus::Qounter);

void QountersMinus::Qounter::Awake() {
    static auto gameObjectName = il2cpp_utils::createcsstr("QountersMinus_Qounter", il2cpp_utils::StringType::Manual);
    gameObject = UnityEngine::GameObject::New_ctor(gameObjectName);
    gameObject->get_transform()->SetParent(get_transform(), false);
    gameObject->AddComponent<UnityEngine::RectTransform*>();
}

void QountersMinus::Qounter::OnDestroy() {
    UnityEngine::GameObject::Destroy(gameObject);
}

TMPro::TextMeshProUGUI* QountersMinus::Qounter::CreateBasicTitle(std::string text) {
    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), text, false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(20.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
    return titleText;
}

void QountersMinus::Qounter::CreateBasicText(std::string text) {
    basicText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), text, false);
    basicText->set_alignment(TMPro::TextAlignmentOptions::Center);
    basicText->set_fontSize(35.0f);
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
}
