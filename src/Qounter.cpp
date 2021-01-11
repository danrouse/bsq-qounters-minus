#include "Qounter.hpp"

DEFINE_CLASS(QountersMinus::Qounter);

void QountersMinus::Qounter::Awake() {
    static auto gameObjectName = il2cpp_utils::createcsstr("QountersMinus_Qounter", il2cpp_utils::StringType::Manual);
    gameObject = UnityEngine::GameObject::New_ctor(gameObjectName);
    gameObject->get_transform()->SetParent(get_transform(), false);
    auto rect = gameObject->AddComponent<UnityEngine::RectTransform*>();
    rect->set_sizeDelta(UnityEngine::Vector2(0.0f, 300.0f));
}

void QountersMinus::Qounter::OnDestroy() {
    UnityEngine::GameObject::Destroy(gameObject);
}
