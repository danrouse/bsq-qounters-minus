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

UnityEngine::GameObject* QountersMinus::QounterRegistry::GetParent(QounterPosition position) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(QounterPositionParents[position].parentName));
        auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(parentGO->get_transform());
        containerGO = layout->get_gameObject();
        containerGO->get_transform()->set_localPosition(QounterPositionParents[position].localPosition);
        containerGO->set_name(containerName);
    }
    return containerGO;
}


// Register all Qounter types with custom_types [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::RegisterTypes() {
    custom_types::Register::RegisterType<Qounter>();
    custom_types::Register::RegisterType<Qounters::CutQounter>();
    custom_types::Register::RegisterType<Qounters::MissQounter>();
    custom_types::Register::RegisterType<Qounters::NotesQounter>();
}


// Initialize all enabled Qounters [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::Initialize() {
    if (config.cutQounterConfig.enabled) QountersMinus::QounterRegistry::Initialize(config.cutQounterConfig);
    if (config.missQounterConfig.enabled) QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);
    if (config.notesQounterConfig.enabled) QountersMinus::QounterRegistry::Initialize(config.notesQounterConfig);

    // qounter position debugging

    // config.missQounterConfig.position = QountersMinus::QounterPosition::BelowCombo;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);

    // config.missQounterConfig.position = QountersMinus::QounterPosition::AboveCombo;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);

    // config.missQounterConfig.position = QountersMinus::QounterPosition::BelowMultiplier;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);

    // config.missQounterConfig.position = QountersMinus::QounterPosition::AboveMultiplier;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);

    // config.missQounterConfig.position = QountersMinus::QounterPosition::BelowEnergy;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);

    // config.missQounterConfig.position = QountersMinus::QounterPosition::OverHighway;
    // QountersMinus::QounterRegistry::Initialize(config.missQounterConfig);
}


// Define a typed initializer for all Qounter types [ALL-QOUNTERS]
DefineQounterInitializer(Qounters::CutQounter*, CutQounterConfig, cutQounter);
DefineQounterInitializer(Qounters::MissQounter*, MissQounterConfig, missQounter);
DefineQounterInitializer(Qounters::NotesQounter*, NotesQounterConfig, notesQounter);


// Call event handlers for qounter types to each as necessary [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    DefineQounterEventHandler(CutQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(MissQounter, OnNoteCut(data, info));
    DefineQounterEventHandler(NotesQounter, OnNoteCut(data, info));
}

void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
    DefineQounterEventHandler(MissQounter, OnNoteMiss(data));
    DefineQounterEventHandler(NotesQounter, OnNoteMiss(data));
}

void QountersMinus::QounterRegistry::OnScoreUpdated(int modifiedScore) {
}

void QountersMinus::QounterRegistry::OnMaxScoreUpdated(int maxModifiedScore) {
}
