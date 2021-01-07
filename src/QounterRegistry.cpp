#include "QounterRegistry.hpp"

struct QounterPositionData {
    std::string parentName;
    UnityEngine::Vector3 localPosition;
};

std::map<QountersMinus::QounterPosition, QounterPositionData> QounterPositionParents = {
    {QountersMinus::QounterPosition::BelowCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, 20.0f, 0.0f)}},
    {QountersMinus::QounterPosition::AboveCombo, {"BasicGameHUD/LeftPanel/ComboPanel", UnityEngine::Vector3(0.0f, -20.0f, 0.0f)}},
    {QountersMinus::QounterPosition::BelowMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, 20.0f, 0.0f)}},
    {QountersMinus::QounterPosition::AboveMultiplier, {"BasicGameHUD/RightPanel/MultiplierCanvas", UnityEngine::Vector3(0.0f, -20.0f, 0.0f)}},
    {QountersMinus::QounterPosition::BelowEnergy, {"BasicGameHUD/EnergyPanel", UnityEngine::Vector3(0.0f, -20.0f, 0.0f)}},
    {QountersMinus::QounterPosition::OverHighway, {"", UnityEngine::Vector3(0.0f, 0.0f, 0.0f)}}
};


void QountersMinus::QounterRegistry::RegisterTypes() {
    custom_types::Register::RegisterType<QountersMinus::Qounter>();
    custom_types::Register::RegisterType<QountersMinus::Qounters::CutQounter>();
}

void QountersMinus::QounterRegistry::Initialize(QountersMinus::QounterConfig config) {
    LOG_CALLER;
    UnityEngine::GameObject* parentGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(
        QounterPositionParents[config.position].parentName
    ));
    if (!parentGO) {
        LOG_DEBUG("Failed to initialize Qounter: could not find parent \"" + QounterPositionParents[config.position].parentName + "\" for position %d", config.position);
        return;
    }

    QountersMinus::Qounter* qounter;
    switch (config.type) {
        case QountersMinus::QounterType::CutQounter:
            qounter = parentGO->AddComponent<QountersMinus::Qounters::CutQounter*>();
            break;
        case QountersMinus::QounterType::FailQounter:
        case QountersMinus::QounterType::MissedQounter:
        case QountersMinus::QounterType::NotesQounter:
        case QountersMinus::QounterType::NotesLeftQounter:
        case QountersMinus::QounterType::PBQounter:
        case QountersMinus::QounterType::ProgressBaseGameQounter:
        case QountersMinus::QounterType::ProgressQounter:
        case QountersMinus::QounterType::ScoreQounter:
        case QountersMinus::QounterType::SpeedQounter:
        default:
            LOG_DEBUG("Failed to initialize Qounter with unknown type %d", config.type);
            return;
    }

    if (!qounter->gameObject) {
        LOG_DEBUG("Failed to initialize Qounter which did not create a GameObject (type %d)", config.type);
        return;
    }

    qounter->gameObject->get_transform()->set_localPosition(QounterPositionParents[config.position].localPosition);
    
    registry.push_back(qounter);
}

void QountersMinus::QounterRegistry::DestroyAll() {
    LOG_CALLER;
    for (auto qounter : registry) qounter->Destroy();
    registry.clear();
}
void QountersMinus::QounterRegistry::OnNoteCut(GlobalNamespace::NoteData* data, GlobalNamespace::NoteCutInfo* info) {
    LOG_CALLER;
    for (auto qounter : registry) qounter->OnNoteCut(data, info);
}
void QountersMinus::QounterRegistry::OnNoteMiss(GlobalNamespace::NoteData* data) {
    LOG_CALLER;
    for (auto qounter : registry) qounter->OnNoteMiss(data);
}
void QountersMinus::QounterRegistry::ScoreUpdated(int modifiedScore) {
    LOG_CALLER;
    for (auto qounter : registry) qounter->ScoreUpdated(modifiedScore);
}
void QountersMinus::QounterRegistry::MaxScoreUpdated(int maxModifiedScore) {
    LOG_CALLER;
    for (auto qounter : registry) qounter->MaxScoreUpdated(maxModifiedScore);
}
