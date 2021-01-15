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

void QountersMinus::QounterRegistry::Register(std::string _namespace, std::string _class) {
    auto initialize = il2cpp_utils::FindMethodUnsafe(_namespace, _class, "Initialize", 0);
    if (!initialize) throw std::runtime_error("Qounter types must have a static void Initialize()");
    std::map<QountersMinus::QounterRegistry::Event, const MethodInfo*> eventHandlers;
    for (auto sig : eventHandlerSignatures) {
        eventHandlers[sig.event] = il2cpp_utils::FindMethodUnsafe(_namespace, _class, sig.methodName, sig.numArgs);
    }
    registry.push_back({
        _namespace,
        _class,
        (Qounter*)nullptr,
        initialize,
        eventHandlers
    });
}

void QountersMinus::QounterRegistry::Initialize() {
    for (auto&& def : registry) def.instance = nullptr;
    if (!config.enabled) return;
    if (config.hideCombo) _DeactivateChildren("LeftPanel/ComboPanel");
    if (config.hideMultiplier) {
        auto multiplierGO = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("RightPanel/MultiplierCanvas"));
        multiplierGO->GetComponent<UnityEngine::Animator*>()->set_enabled(false);
        _DeactivateChildren(multiplierGO);
    }

    for (auto&& def : registry) {
        def.instance = il2cpp_utils::RunStaticMethodUnsafe<Qounter*>(def.initializer).value();
    }

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
