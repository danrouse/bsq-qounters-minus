#include "Qounter.hpp"

DEFINE_CLASS(QountersMinus::Qounter);

bool QountersMinus::Qounter::Enabled = true;
bool QountersMinus::Qounter::HideCombo = false;
bool QountersMinus::Qounter::HideMultiplier = false;
float QountersMinus::Qounter::ComboOffset = 0.2f;
float QountersMinus::Qounter::MultiplierOffset = 0.4f;
bool QountersMinus::Qounter::ItalicText = false;

const float distanceUnit = 40.0f;
const float distanceUnitOffsetMult = 0.15f;


struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector2 anchoredPosition;
    bool distanceIsDown;
};

std::map<QountersMinus::QounterPosition, QounterPositionData> QounterPositionData = {
    {QountersMinus::QounterPosition::BelowCombo, {"ComboPanel", UnityEngine::Vector2(-4.0f, 12.0f), true}},
    {QountersMinus::QounterPosition::AboveCombo, {"ComboPanel", UnityEngine::Vector2(-4.0f, 40.0f), false}},
    {QountersMinus::QounterPosition::BelowMultiplier, {"MultiplierCanvas", UnityEngine::Vector2(0.0f, 12.0f), true}},
    {QountersMinus::QounterPosition::AboveMultiplier, {"MultiplierCanvas", UnityEngine::Vector2(0.0f, 40.0f), false}},
    {QountersMinus::QounterPosition::BelowEnergy, {"EnergyPanel", UnityEngine::Vector2(0.0f, -5.0f), true}},
    {QountersMinus::QounterPosition::AboveHighway, {"EnergyPanel", UnityEngine::Vector2(0.0f, 180.0f), false}}
};

void DeactivateChildren(UnityEngine::GameObject* gameObject) {
    auto parent = gameObject->get_transform();
    for (int i = 0; i < parent->get_childCount(); i++) {
        parent->GetChild(i)->get_gameObject()->SetActive(false);
    }
}

void DeactivateChildren(std::string gameObjectName) {
    DeactivateChildren(UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(gameObjectName)));
}

// super slow way to find inactive game objects
// sometimes, the position parent objects are not active immediately after CoreGameHUD.Start
UnityEngine::GameObject* GetGameObject(std::string name) {
    auto allObjects = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::GameObject*>();
    for (int i = 0; i < allObjects->Length(); i++) {
        if (to_utf8(csstrtostr(allObjects->values[i]->get_name())) == name) return allObjects->values[i];
    }
    return nullptr;
}

UnityEngine::GameObject* GetParent(QountersMinus::QounterPosition position) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = GetGameObject(QounterPositionData[position].parentName);
        if (!parentGO->get_activeSelf()) {
            DeactivateChildren(parentGO);
            parentGO->SetActive(true);
        }
        containerGO = UnityEngine::GameObject::New_ctor(containerName);
        auto rect = containerGO->AddComponent<UnityEngine::RectTransform*>();
        containerGO->get_transform()->SetParent(parentGO->get_transform(), false);
        auto anchoredPosition = QounterPositionData[position].anchoredPosition;
        if (position == QountersMinus::QounterPosition::BelowCombo || position == QountersMinus::QounterPosition::AboveCombo) {
            anchoredPosition.y *= 1.0f + (QountersMinus::Qounter::ComboOffset * distanceUnit * distanceUnitOffsetMult * (QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f));
        } else if (position == QountersMinus::QounterPosition::BelowMultiplier || position == QountersMinus::QounterPosition::AboveMultiplier) {
            anchoredPosition.y *= 1.0f + (QountersMinus::Qounter::MultiplierOffset * distanceUnit * distanceUnitOffsetMult * (QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f));
        } else {
            rect->set_localPosition(UnityEngine::Vector3(0.0f, 0.0f, 5.0f));
            rect->set_localScale(UnityEngine::Vector3(0.8f, 0.8f, 0.8f));
        }
        rect->set_anchoredPosition(anchoredPosition);
    }
    return containerGO;
}

void SetPosition(UnityEngine::Transform* transform, QountersMinus::QounterPosition position, int distance) {
    const auto mult = QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f;
    const auto pivot = UnityEngine::Vector2(0.5f, QounterPositionData[position].distanceIsDown ? 1.0f : 0.0f);
    const auto anchoredPosition = UnityEngine::Vector2(0.0f, distance * distanceUnit * mult);
    reinterpret_cast<UnityEngine::RectTransform*>(transform)->set_pivot(pivot);
    reinterpret_cast<UnityEngine::RectTransform*>(transform)->set_anchoredPosition(anchoredPosition);
}

void QountersMinus::Qounter::Awake() {
    static auto gameObjectName = il2cpp_utils::createcsstr("QountersMinus_Qounter", il2cpp_utils::StringType::Manual);
    gameObject = UnityEngine::GameObject::New_ctor(gameObjectName);
    gameObject->get_transform()->SetParent(get_transform(), false);
    gameObject->AddComponent<UnityEngine::RectTransform*>();
    refs = gameObject->AddComponent<QountersMinus::InjectedComponents*>();
}

void QountersMinus::Qounter::OnDestroy() {
    UnityEngine::GameObject::Destroy(gameObject);
}

TMPro::TextMeshProUGUI* QountersMinus::Qounter::CreateBasicTitle(std::string text) {
    auto titleText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), text, false);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(27.0f);
    titleText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
    return titleText;
}

void QountersMinus::Qounter::CreateBasicText(std::string text) {
    basicText = QuestUI::BeatSaberUI::CreateText(gameObject->get_transform(), text, false);
    basicText->set_alignment(TMPro::TextAlignmentOptions::Center);
    basicText->set_fontSize(35.0f);
    basicText->get_rectTransform()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -30.0f));
}
