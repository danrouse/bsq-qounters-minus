#include "QounterRegistry.hpp"

using namespace QountersMinus;

#define DefineQounterInitializer(qounterType, configType, registryName) \
    void QountersMinus::QounterRegistry::Initialize(configType config) { \
        auto parent = GetParent(config.position); \
        auto qounter = parent->AddComponent<qounterType>(); \
        SetPosition(qounter->gameObject->get_transform(), config.position, config.distance); \
        qounter->Configure(config); \
    }

#define DefineQounterEventHandler(type, handler) \
    auto all_##type = UnityEngine::Resources::FindObjectsOfTypeAll<Qounters::type*>(); \
    for (int i = 0; i < all_##type->Length(); i++) { all_##type->values[i]->handler; }

extern QountersMinus::ModConfig config;

struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector3 localPosition;
    bool distanceIsDown;
};

std::map<QounterPosition, QounterPositionData> QounterPositionData = {
    {QounterPosition::BelowCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(-5.0f, -122.0f, 0.0f), true}},
    {QounterPosition::AboveCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(-5.0f, 28.0f, 0.0f), false}},
    {QounterPosition::BelowMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, -90.0f, 0.0f), true}},
    {QounterPosition::AboveMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, 20.0f, 0.0f), false}},
    {QounterPosition::BelowEnergy, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(320.0f, -220.0f, 0.0f), true}},
    {QounterPosition::AboveHighway, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(320.0f, 160.0f, 0.0f), false}}
};

UnityEngine::GameObject* GetParent(QounterPosition position) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(QounterPositionData[position].parentName));
        containerGO = UnityEngine::GameObject::New_ctor(containerName);
        containerGO->AddComponent<UnityEngine::RectTransform*>();
        containerGO->get_transform()->SetParent(parentGO->get_transform(), false);
        auto localPosition = QounterPositionData[position].localPosition;
        if (position == QounterPosition::BelowCombo || position == QounterPosition::AboveCombo) {
            localPosition.y *= 1.0f + config.comboOffset;
        } else if (position == QounterPosition::BelowMultiplier || position == QounterPosition::AboveMultiplier) {
            localPosition.y *= 1.0f + config.multiplierOffset;
        }
        containerGO->get_transform()->set_localPosition(localPosition);
    }
    return containerGO;
}

void SetPosition(UnityEngine::Transform* transform, QounterPosition position, int distance) {
    static const float distanceUnit = 62.0f;
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

    // Initialize all enabled Qounters [ALL-QOUNTERS]
    if (config.cutQounterConfig.enabled) QounterRegistry::Initialize(config.cutQounterConfig);
    if (config.missedQounterConfig.enabled) QounterRegistry::Initialize(config.missedQounterConfig);
    if (config.notesQounterConfig.enabled) QounterRegistry::Initialize(config.notesQounterConfig);
    if (config.notesLeftQounterConfig.enabled) QounterRegistry::Initialize(config.notesLeftQounterConfig);
    if (config.spinometerConfig.enabled) QounterRegistry::Initialize(config.spinometerConfig);
    if (config.speedQounterConfig.enabled) QounterRegistry::Initialize(config.speedQounterConfig);
    if (config.scoreQounterConfig.enabled) QounterRegistry::Initialize(config.scoreQounterConfig);
    if (config.pbQounterConfig.enabled) QounterRegistry::Initialize(config.pbQounterConfig);
    if (config.failQounterConfig.enabled) QounterRegistry::Initialize(config.failQounterConfig);
    if (config.progressQounterConfig.enabled) QounterRegistry::Initialize(config.progressQounterConfig);

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

// Define a typed initializer for all Qounter types [ALL-QOUNTERS]
DefineQounterInitializer(Qounters::CutQounter*, CutQounterConfig, cutQounter);
DefineQounterInitializer(Qounters::MissedQounter*, MissedQounterConfig, missedQounter);
DefineQounterInitializer(Qounters::NotesQounter*, NotesQounterConfig, notesQounter);
DefineQounterInitializer(Qounters::NotesLeftQounter*, NotesLeftQounterConfig, notesLeftQounter);
DefineQounterInitializer(Qounters::Spinometer*, SpinometerConfig, spinometer);
DefineQounterInitializer(Qounters::SpeedQounter*, SpeedQounterConfig, speedQounter);
DefineQounterInitializer(Qounters::ScoreQounter*, ScoreQounterConfig, scoreQounter);
DefineQounterInitializer(Qounters::PBQounter*, PBQounterConfig, pbQounter);
DefineQounterInitializer(Qounters::FailQounter*, FailQounterConfig, failQounter);
DefineQounterInitializer(Qounters::ProgressQounter*, ProgressQounterConfig, progressQounter);


// Call event handlers for qounter types to each as necessary [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    DefineQounterEventHandler(CutQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(MissedQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(NotesQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(NotesLeftQounter, OnNoteCut(data, info));
}

void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
    DefineQounterEventHandler(MissedQounter, OnNoteMiss(data));
    DefineQounterEventHandler(NotesQounter, OnNoteMiss(data));
    DefineQounterEventHandler(NotesLeftQounter, OnNoteMiss(data));
}

void QountersMinus::QounterRegistry::OnScoreUpdated(int modifiedScore) {
    DefineQounterEventHandler(PBQounter, OnScoreUpdated(modifiedScore));
}

void QountersMinus::QounterRegistry::OnMaxScoreUpdated(int maxModifiedScore) {
}
