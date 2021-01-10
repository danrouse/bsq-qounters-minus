#include "QounterRegistry.hpp"

using namespace QountersMinus;

#define DefineQounterInitializer(qounterType, configType, registryName) \
    void QountersMinus::QounterRegistry::Initialize(configType config) { \
        auto parent = GetParent(config.position); \
        auto qounter = parent->AddComponent<qounterType>(); \
        qounter->Configure(config); \
    }

#define DefineQounterEventHandler(type, handler) \
    auto all_##type = UnityEngine::Resources::FindObjectsOfTypeAll<Qounters::type*>(); \
    for (int i = 0; i < all_##type->Length(); i++) { all_##type->values[i]->handler; }

extern QountersMinus::ModConfig config;

struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector3 localPosition;
};

std::map<QounterPosition, QounterPositionData> QounterPositionParents = {
    {QounterPosition::BelowCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, -180.0f, 0.0f)}},
    {QounterPosition::AboveCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, 100.0f, 0.0f)}},
    {QounterPosition::BelowMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, -180.0f, 0.0f)}},
    {QounterPosition::AboveMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, 120.0f, 0.0f)}},
    {QounterPosition::BelowEnergy, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(300.0f, -180.0f, 0.0f)}},
    {QounterPosition::OverHighway, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(300.0f, 120.0f, 0.0f)}}
};

UnityEngine::GameObject* GetParent(QounterPosition position) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(QounterPositionParents[position].parentName));
        auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(parentGO->get_transform());
        layout->set_spacing(20.0f);
        containerGO = layout->get_gameObject();
        auto localPosition = QounterPositionParents[position].localPosition;
        if (position == QounterPosition::BelowCombo || position == QounterPosition::AboveCombo) {
            localPosition.y *= 1.0f + config.comboOffset;
        } else if (position == QounterPosition::BelowMultiplier || position == QounterPosition::AboveMultiplier) {
            localPosition.y *= 1.0f + config.multiplierOffset;
        }
        containerGO->get_transform()->set_localPosition(localPosition);
        containerGO->set_name(containerName);
    }
    return containerGO;
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
    custom_types::Register::RegisterType<Qounters::MissQounter>();
    custom_types::Register::RegisterType<Qounters::NotesQounter>();
    custom_types::Register::RegisterType<Qounters::NotesLeftQounter>();
    custom_types::Register::RegisterType<Qounters::Spinometer>();
    custom_types::Register::RegisterType<Qounters::SpeedQounter>();
}

#include "UnityEngine/Animator.hpp"
void QountersMinus::QounterRegistry::Initialize() {
    if (config.hideCombo) HideChildren("BasicGameHUD/LeftPanel/ComboPanel");
    if (config.hideMultiplier) {
        auto multiplierGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BasicGameHUD/RightPanel/MultiplierCanvas"));
        UnityEngine::Object::Destroy(multiplierGO->GetComponent<UnityEngine::Animator*>());
        HideChildren(multiplierGO);
    }

    // Initialize all enabled Qounters [ALL-QOUNTERS]
    if (config.cutQounterConfig.enabled) QounterRegistry::Initialize(config.cutQounterConfig);
    if (config.missQounterConfig.enabled) QounterRegistry::Initialize(config.missQounterConfig);
    if (config.notesQounterConfig.enabled) QounterRegistry::Initialize(config.notesQounterConfig);
    if (config.notesLeftQounterConfig.enabled) QounterRegistry::Initialize(config.notesLeftQounterConfig);
    if (config.spinometerConfig.enabled) QounterRegistry::Initialize(config.spinometerConfig);
    if (config.speedQounterConfig.enabled) QounterRegistry::Initialize(config.speedQounterConfig);

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
DefineQounterInitializer(Qounters::MissQounter*, MissQounterConfig, missQounter);
DefineQounterInitializer(Qounters::NotesQounter*, NotesQounterConfig, notesQounter);
DefineQounterInitializer(Qounters::NotesLeftQounter*, NotesLeftQounterConfig, notesLeftQounter);
DefineQounterInitializer(Qounters::Spinometer*, SpinometerConfig, spinometer);
DefineQounterInitializer(Qounters::SpeedQounter*, SpeedQounterConfig, speedQounter);


// Call event handlers for qounter types to each as necessary [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    DefineQounterEventHandler(CutQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(MissQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(NotesQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(NotesLeftQounter, OnNoteCut(data, info));
}

void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
    DefineQounterEventHandler(MissQounter, OnNoteMiss(data));
    DefineQounterEventHandler(NotesQounter, OnNoteMiss(data));
    DefineQounterEventHandler(NotesLeftQounter, OnNoteMiss(data));
}

void QountersMinus::QounterRegistry::OnScoreUpdated(int modifiedScore) {
}

void QountersMinus::QounterRegistry::OnMaxScoreUpdated(int maxModifiedScore) {
}
