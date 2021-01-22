#include "QounterRegistry.hpp"

using namespace QountersMinus;

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
    if (Qounter::HideCombo) _DeactivateChildren("LeftPanel/ComboPanel");
    if (Qounter::HideMultiplier) {
        auto multiplierGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("RightPanel/MultiplierCanvas"));
        multiplierGO->GetComponent<UnityEngine::Animator*>()->set_enabled(false);
        _DeactivateChildren(multiplierGO);
    }

    for (auto&& def : registry) {
        if (def.second.initializer) {
            def.second.instance = il2cpp_utils::RunStaticMethodUnsafe<Qounter*>(def.second.initializer).value();
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
