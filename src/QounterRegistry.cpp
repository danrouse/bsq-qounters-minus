#include "QounterRegistry.hpp"

using namespace QountersMinus;

const std::vector<QounterRegistry::EventHandlerSignature> QounterRegistry::eventHandlerSignatures = {
    {QounterRegistry::Event::NoteCut, "OnNoteCut", 2},
    {QounterRegistry::Event::NoteMiss, "OnNoteMiss", 1},
    {QounterRegistry::Event::ScoreUpdated, "OnScoreUpdated", 1},
    {QounterRegistry::Event::MaxScoreUpdated, "OnMaxScoreUpdated", 1},
    {QounterRegistry::Event::SwingRatingFinished, "OnSwingRatingFinished", 2},
};
std::map<std::pair<std::string, std::string>, QounterRegistry::RegistryEntry> QounterRegistry::registry;
std::vector<std::pair<std::string, std::string>> QounterRegistry::registryInsertionOrder;

void _DeactivateChildren(UnityEngine::GameObject* gameObject) {
    auto parent = gameObject->get_transform();
    for (int i = 0; i < parent->get_childCount(); i++) {
        parent->GetChild(i)->get_gameObject()->SetActive(false);
    }
}

void _DeactivateChildren(std::string gameObjectName) {
    _DeactivateChildren(UnityEngine::GameObject::Find(il2cpp_utils::createcsstr(gameObjectName)));
}

void QountersMinus::QounterRegistry::Initialize() {
    for (auto&& def : registry) def.second.instance = nullptr;
    if (!Qounter::Enabled) return;
    if (UnityEngine::Object::FindObjectOfType<PlayerDataModel*>()->playerData->playerSpecificSettings->noTextsAndHuds) return;
    if (Qounter::HideCombo) _DeactivateChildren("LeftPanel/ComboPanel");
    if (Qounter::HideMultiplier) {
        auto multiplierGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("RightPanel/MultiplierCanvas"));
        multiplierGO->GetComponent<UnityEngine::Animator*>()->set_enabled(false);
        _DeactivateChildren(multiplierGO);
    }

    for (auto key : registryInsertionOrder) {
        auto&& def = registry[key];
        if (def.initializer) {
            LOG_DEBUG("Initialize " + key.first + "::" + key.second);
            def.instance = il2cpp_utils::RunStaticMethodUnsafe<Qounter*>(def.initializer).value();
        }
    }

    if (Qounter::ItalicText) {
        auto qounters = UnityEngine::Resources::FindObjectsOfTypeAll<Qounter*>();
        for (int i = 0; i < qounters->Length(); i++) {
            auto texts = qounters->values[i]->GetComponentsInChildren<TMPro::TextMeshProUGUI*>();
            for (int j = 0; j < texts->Length(); j++) {
                texts->values[j]->set_fontStyle(TMPro::FontStyles::Italic);
            }
        }
    }
}
