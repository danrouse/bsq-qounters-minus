#include "QounterRegistry.hpp"

using namespace QountersMinus;

#define DefineQounterInitializer(type) \
    void QountersMinus::QounterRegistry::Initialize(type##Config config) { \
        if (!config.enabled) return; \
        auto parent = GetParent(config.position); \
        type = parent->AddComponent<QountersMinus::Qounters::type*>(); \
        SetPosition(type->gameObject->get_transform(), config.position, config.distance); \
        type->Configure(config); \
    }

extern QountersMinus::ModConfig config;
static const float distanceUnit = 40.0f;

struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector2 anchoredPosition;
    bool distanceIsDown;
};

std::map<QounterPosition, QounterPositionData> QounterPositionData = {
    {QounterPosition::BelowCombo, {"ComboPanel", UnityEngine::Vector2(-4.0f, 12.0f), true}},
    {QounterPosition::AboveCombo, {"ComboPanel", UnityEngine::Vector2(-4.0f, 50.0f), false}},
    {QounterPosition::BelowMultiplier, {"MultiplierCanvas", UnityEngine::Vector2(0.0f, 12.0f), true}},
    {QounterPosition::AboveMultiplier, {"MultiplierCanvas", UnityEngine::Vector2(0.0f, 50.0f), false}},
    {QounterPosition::BelowEnergy, {"ComboPanel", UnityEngine::Vector2(310.0f, -120.0f), true}},
    {QounterPosition::AboveHighway, {"ComboPanel", UnityEngine::Vector2(310.0f, 120.0f), false}}
};

// super slow way to find inactive game objects
// sometimes, the parent objects are not active immediately after CoreGameHUD.Start
UnityEngine::GameObject* GetGameObject(std::string name) {
    auto allObjects = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::GameObject*>();
    for (int i = 0; i < allObjects->Length(); i++) {
        if (to_utf8(csstrtostr(allObjects->values[i]->get_name())) == name) return allObjects->values[i];
    }
    return nullptr;
}

UnityEngine::GameObject* GetParent(QounterPosition position) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = GetGameObject(QounterPositionData[position].parentName);
        containerGO = UnityEngine::GameObject::New_ctor(containerName);
        auto rect = containerGO->AddComponent<UnityEngine::RectTransform*>();
        containerGO->get_transform()->SetParent(parentGO->get_transform(), false);
        auto anchoredPosition = QounterPositionData[position].anchoredPosition;
        if (position == QounterPosition::BelowCombo || position == QounterPosition::AboveCombo) {
            anchoredPosition.y *= 1.0f + (config.comboOffset * (distanceUnit * 0.2f) * (QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f));
        } else if (position == QounterPosition::BelowMultiplier || position == QounterPosition::AboveMultiplier) {
            anchoredPosition.y *= 1.0f + (config.multiplierOffset * (distanceUnit * 0.2f) * (QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f));
        }
        rect->set_anchoredPosition(anchoredPosition);
    }
    return containerGO;
}

void SetPosition(UnityEngine::Transform* transform, QounterPosition position, int distance) {
    const auto mult = QounterPositionData[position].distanceIsDown ? -1.0f : 1.0f;
    const auto pivot = UnityEngine::Vector2(0.5f, QounterPositionData[position].distanceIsDown ? 1.0f : 0.0f);
    const auto anchoredPosition = UnityEngine::Vector2(0.0f, distance * distanceUnit * mult);
    reinterpret_cast<UnityEngine::RectTransform*>(transform)->set_pivot(pivot);
    reinterpret_cast<UnityEngine::RectTransform*>(transform)->set_anchoredPosition(anchoredPosition);
}

void HideChildren(UnityEngine::GameObject* gameObject) {
    auto parent = gameObject->get_transform();
    for (int i = 0; i < parent->get_childCount(); i++) {
        parent->GetChild(i)->get_gameObject()->SetActive(false);
    }
}

void HideChildren(std::string gameObjectName) {
    HideChildren(UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(gameObjectName)));
}


// Register all Qounter types with custom_types [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::RegisterTypes() {
    custom_types::Register::RegisterType<Qounter>();
    custom_types::Register::RegisterType<Qounters::CutQounter>();
    custom_types::Register::RegisterType<Qounters::MissedQounter>();
    custom_types::Register::RegisterType<Qounters::NotesQounter>();
    custom_types::Register::RegisterType<Qounters::NotesLeftQounter>();
    custom_types::Register::RegisterType<Qounters::Spinometer>();
    custom_types::Register::RegisterType<Qounters::SpeedQounter>();
    custom_types::Register::RegisterType<Qounters::ScoreQounter>();
    custom_types::Register::RegisterType<Qounters::PBQounter>();
    custom_types::Register::RegisterType<Qounters::FailQounter>();
    custom_types::Register::RegisterType<Qounters::ProgressQounter>();
}

void QountersMinus::QounterRegistry::Initialize() {
    if (!config.enabled) return;
    if (config.hideCombo) HideChildren("BasicGameHUD/LeftPanel/ComboPanel");
    if (config.hideMultiplier) {
        auto multiplierGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BasicGameHUD/RightPanel/MultiplierCanvas"));
        UnityEngine::Object::Destroy(multiplierGO->GetComponent<UnityEngine::Animator*>());
        HideChildren(multiplierGO);
    }

    // [ALL-QOUNTERS]
    QounterRegistry::Initialize(config.CutQounterConfig);
    QounterRegistry::Initialize(config.MissedQounterConfig);
    QounterRegistry::Initialize(config.NotesQounterConfig);
    QounterRegistry::Initialize(config.NotesLeftQounterConfig);
    QounterRegistry::Initialize(config.SpinometerConfig);
    QounterRegistry::Initialize(config.SpeedQounterConfig);
    QounterRegistry::Initialize(config.ScoreQounterConfig);
    QounterRegistry::Initialize(config.PBQounterConfig);
    QounterRegistry::Initialize(config.FailQounterConfig);
    QounterRegistry::Initialize(config.ProgressQounterConfig);

    if (config.italicText) {
        auto qounters = UnityEngine::Resources::FindObjectsOfTypeAll<Qounter*>();
        for (int i = 0; i < qounters->Length(); i++) {
            auto texts = qounters->values[i]->GetComponentsInChildren<TMPro::TextMeshProUGUI*>();
            for (int j = 0; j < texts->Length(); j++) {
                texts->values[j]->set_fontStyle(TMPro::FontStyles::Italic);
            }
        }
    }
}

// [ALL-QOUNTERS]
DefineQounterInitializer(CutQounter);
DefineQounterInitializer(MissedQounter);
DefineQounterInitializer(NotesQounter);
DefineQounterInitializer(NotesLeftQounter);
DefineQounterInitializer(Spinometer);
DefineQounterInitializer(SpeedQounter);
DefineQounterInitializer(ScoreQounter);
DefineQounterInitializer(PBQounter);
DefineQounterInitializer(FailQounter);
DefineQounterInitializer(ProgressQounter);


// Call event handlers for qounter types to each as necessary [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (MissedQounter) MissedQounter->OnNoteCut(data, info);
    if (NotesQounter) NotesQounter->OnNoteCut(data, info);
    if (NotesLeftQounter) NotesLeftQounter->OnNoteCut(data, info);
}

void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
    if (MissedQounter) MissedQounter->OnNoteMiss(data);
    if (NotesQounter) NotesQounter->OnNoteMiss(data);
    if (NotesLeftQounter) NotesLeftQounter->OnNoteMiss(data);
}

void QountersMinus::QounterRegistry::OnScoreUpdated(int modifiedScore) {
    if (PBQounter) PBQounter->OnScoreUpdated(modifiedScore);
}

void QountersMinus::QounterRegistry::OnMaxScoreUpdated(int maxModifiedScore) {
}

void QountersMinus::QounterRegistry::OnSwingRatingFinished(GlobalNamespace::NoteCutInfo* info, GlobalNamespace::ISaberSwingRatingCounter* swingRatingCounter) {
    if (CutQounter) CutQounter->OnSwingRatingFinished(info, swingRatingCounter);
}
