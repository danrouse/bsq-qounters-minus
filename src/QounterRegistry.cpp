#include "QounterRegistry.hpp"

using namespace QountersMinus;

#define DefineQounterInitializer(qounterType, configType, registryName) void QountersMinus::QounterRegistry::Initialize(configType config) { \
    auto qounter = GetParent(config)->AddComponent<qounterType>(); \
    qounter->Configure(config); \
    registry.registryName = qounter; \
}

extern QountersMinus::ModConfig config;
QounterRegistry::registry_t registry;

struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector3 localPosition;
};

std::map<QounterPosition, QounterPositionData> QounterPositionParents = {
    {QounterPosition::BelowCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, -180.0f, 0.0f)}},
    {QounterPosition::AboveCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, 100.0f, 0.0f)}},
    {QounterPosition::BelowMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, 20.0f, 0.0f)}},
    {QounterPosition::AboveMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, -20.0f, 0.0f)}},
    {QounterPosition::BelowEnergy, {"BasicGameHUD/EnergyPanel", UnityEngine::Vector3(0.0f, -20.0f, 0.0f)}},
    {QounterPosition::OverHighway, {"", UnityEngine::Vector3(0.0f, 0.0f, 0.0f)}}
};

UnityEngine::GameObject* QountersMinus::QounterRegistry::GetParent(QounterConfig config) {
    auto containerName = il2cpp_utils::createcsstr("QountersMinus_Container" + std::to_string((int)config.position));
    auto containerGO = UnityEngine::GameObject::Find(containerName);
    if (!containerGO) {
        auto parentGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(QounterPositionParents[config.position].parentName));
        auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(parentGO->get_transform());
        containerGO = layout->get_gameObject();
        containerGO->get_transform()->set_localPosition(QounterPositionParents[config.position].localPosition);
        containerGO->set_name(containerName);
    }
    return containerGO;
}


// Register all Qounter types with custom_types [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::RegisterTypes() {
    custom_types::Register::RegisterType<Qounter>();
    custom_types::Register::RegisterType<Qounters::CutQounter>();
}


// Initialize all enabled Qounters [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::Initialize() {
    if (config.cutQounterConfig.enabled) QountersMinus::QounterRegistry::Initialize(config.cutQounterConfig);
}


// Define a typed initializer for all Qounter types [ALL-QOUNTERS]
DefineQounterInitializer(Qounters::CutQounter*, CutQounterConfig, cutQounter);


// Call event handlers for qounter types to each as necessary [ALL-QOUNTERS]
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    if (registry.cutQounter) registry.cutQounter->OnNoteCut(data, info);
}

void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
}

void QountersMinus::QounterRegistry::OnScoreUpdated(int modifiedScore) {
}

void QountersMinus::QounterRegistry::OnMaxScoreUpdated(int maxModifiedScore) {
}
