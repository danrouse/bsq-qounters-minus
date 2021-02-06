#include "components/SettingsButtonsViewController.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"

#include "UnityEngine/UI/Button.hpp"
#include "components/QounterSettingsViewController.hpp"
#include "HMUI/ScrollView.hpp"
#include "util/logger.hpp"
DEFINE_CLASS(QountersMinus::SettingsButtonsViewController);

void QountersMinus::SettingsButtonsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    LOG_DEBUG("firstActivation %d, addedToHierarchy %d, screenSystemEnabling %d", firstActivation, addedToHierarchy, screenSystemEnabling);
    if (!firstActivation) return;
    get_transform()->set_eulerAngles(UnityEngine::Vector3(45.0f, 0.0f, 0.0f)); // get up, get on up
    get_transform()->set_localPosition(UnityEngine::Vector3(0.0f, 5.0f, 5.0f)); // get up, get on up

    // auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(get_transform());
    // container->get_transform()->set_eulerAngles(UnityEngine::Vector3(0.0f, 0.0f, 90.0f));
    auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(get_transform());
    auto container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    auto containerRect = container->GetComponent<QuestUI::ExternalComponents*>()->GetComponent<UnityEngine::RectTransform*>();
    containerRect->set_sizeDelta(UnityEngine::Vector2(20.0f, 120.0f));
    containerRect->get_parent()->get_parent()->get_parent()->GetComponent<UnityEngine::RectTransform*>()->set_pivot(UnityEngine::Vector2(0.5f, 0.5f));
    containerRect->get_parent()->get_parent()->get_parent()->set_localEulerAngles(UnityEngine::Vector3(0.0f, 0.0f, 90.0f));
    // // container->get_transform()->set_localEulerAngles(UnityEngine::Vector3(0.0f, 0.0f, -90.0f));
    // // container->get_transform()->get_parent()->get_parent()->get_parent()->get_transform()->set_localEulerAngles(UnityEngine::Vector3(0.0f, 0.0f, -90.0f));

    for (auto key : QountersMinus::QounterRegistry::registryInsertionOrder) {
        auto def = QountersMinus::QounterRegistry::registry[key];
        auto context = new NavigationButtonContext({
            .parent = get_transform(),
            .title = def.longName,
            ._namespace = key.first,
            ._class = key.second,
            .configMetadata = def.configMetadata,
        });
        context->klass = classof(System::Object*);
        UnityEngine::UI::Button* button = QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), def.shortName, UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector2(5.0f, 10.0f), il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
            classof(UnityEngine::Events::UnityAction*), context, +[](NavigationButtonContext* context) {
                auto controller = UnityEngine::Object::FindObjectOfType<QountersMinus::QounterSettingsViewController*>();
                controller->ReplaceQounterConfig(context->title, context->configMetadata);

                // auto existingContainer = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("QountersMinusSettingsContainer"));
                // if (existingContainer) UnityEngine::Object::Destroy(existingContainer);
                // CreateQounterConfigView(context->parent, context->title, context->_namespace, context->_class, context->configMetadata);
            }
        ));
        // button->get_transform()->set_localEulerAngles(UnityEngine::Vector3(0.0f, 0.0f, 90.0f));
    }
}
