#include "QounterSettingsViewController.hpp"

DEFINE_CLASS(QountersMinus::QounterSettingsViewController);

using namespace QountersMinus;

void StartTestLevel(QountersMinus::QounterSettingsViewController* self) {
    auto simpleLevelStarters = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleLevelStarter*>();
    for (int i = 0; i < simpleLevelStarters->Length(); i++) {
        auto starter = simpleLevelStarters->values[i];
        if (starter->get_gameObject()->get_name()->Contains(il2cpp_utils::createcsstr("PerformanceTestLevelButton"))) {
            starter->level->set_name(il2cpp_utils::createcsstr("Qounters- Test"));
            starter->gameplayModifiers->demoNoObstacles = true;
            starter->StartLevel();
            return;
        }
    }
}

UnityEngine::GameObject* CreateContentView(UnityEngine::Transform* parent) {
    static auto name = il2cpp_utils::createcsstr("QountersMinusSettingsContainer", il2cpp_utils::StringType::Manual);
    auto scrollContainer = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(parent);
    auto scrollContainerScrollerRect = scrollContainer->get_transform()->get_parent()->get_parent()->get_parent()->GetComponent<UnityEngine::RectTransform*>();
    scrollContainerScrollerRect->set_anchoredPosition(UnityEngine::Vector2(22.0f, 0.0f));
    scrollContainer->get_transform()->get_parent()->get_parent()->get_parent()->get_gameObject()->set_name(name);
    return scrollContainer;
}

void QountersMinus::QounterSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation || !addedToHierarchy) return;

    auto navigationContainer = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    navigationContainer->GetComponent<UnityEngine::UI::VerticalLayoutGroup*>()->set_spacing(-0.5f);

    auto navigationContainerRect = navigationContainer->get_transform()->get_parent()->get_parent()->get_parent()->GetComponent<UnityEngine::RectTransform*>();
    navigationContainerRect->set_sizeDelta(UnityEngine::Vector2(-112.0f, -12.0f));
    navigationContainerRect->set_anchoredPosition(UnityEngine::Vector2(-52.0f, 6.0f));

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
        QuestUI::BeatSaberUI::CreateUIButton(navigationContainer->get_transform(), def.shortName, il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
            classof(UnityEngine::Events::UnityAction*), context, +[](NavigationButtonContext* context) {
                auto existingContainer = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("QountersMinusSettingsContainer"));
                if (existingContainer) UnityEngine::Object::Destroy(existingContainer);
                CreateQounterConfigView(context->parent, context->title, context->_namespace, context->_class, context->configMetadata);
            }
        ));
    }

    // Select "Main" by default
    CreateQounterConfigView(get_transform(),
        QountersMinus::QounterRegistry::registry[{"QountersMinus", "Qounter"}].longName,
        "QountersMinus",
        "Qounter",
        QountersMinus::QounterRegistry::registry[{"QountersMinus", "Qounter"}].configMetadata
    );

    auto testButton = QuestUI::BeatSaberUI::CreateUIButton(get_transform(), "Test", "PlayButton", il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
        classof(UnityEngine::Events::UnityAction*), this, StartTestLevel
    ));
    testButton->GetComponent<UnityEngine::RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(-52.0f, -27.5f));
    testButton->GetComponent<UnityEngine::RectTransform*>()->set_sizeDelta(UnityEngine::Vector2(27.0f, 10.0f));
}

void HandleBoolSettingChanged(System::Reflection::Pointer* csptr, bool val) {
    auto field = reinterpret_cast<QountersMinus::QounterRegistry::ConfigMetadata*>(csptr->ptr);
    *(bool*)field->ptr = val;
    QountersMinus::SaveConfig();
}
void HandleFloatSettingChanged(System::Reflection::Pointer* csptr, float val) {
    auto field = reinterpret_cast<QountersMinus::QounterRegistry::ConfigMetadata*>(csptr->ptr);
    *(float*)field->ptr = val;
    QountersMinus::SaveConfig();
}
void HandleIntSettingChanged(System::Reflection::Pointer* csptr, float val) {
    auto field = reinterpret_cast<QountersMinus::QounterRegistry::ConfigMetadata*>(csptr->ptr);
    *(int*)field->ptr = static_cast<int>(val);
    QountersMinus::SaveConfig();
}
void HandleEnumSettingChanged(System::Reflection::Pointer* csptr, float rawVal) {
    auto field = reinterpret_cast<QountersMinus::QounterRegistry::ConfigMetadata*>(csptr->ptr);
    auto intVal = static_cast<int>(rawVal) % field->enumNumElements;
    if (intVal < 0) intVal = field->enumNumElements - (intVal * -1);
    *(int*)field->ptr = intVal;
    QountersMinus::SaveConfig();
    reinterpret_cast<QuestUI::IncrementSetting*>(field->uiElementPtr)->Text->SetText(
        il2cpp_utils::createcsstr(field->enumDisplayNames[intVal])
    );
}
void HandleColorSettingChanged(System::Reflection::Pointer* csptr, UnityEngine::Color val, GlobalNamespace::ColorChangeUIEventType eventType) {
    auto field = reinterpret_cast<QountersMinus::QounterRegistry::ConfigMetadata*>(csptr->ptr);
    *(UnityEngine::Color*)field->ptr = val;
    QountersMinus::SaveConfig();
}

UnityEngine::GameObject* QountersMinus::QounterSettingsViewController::CreateQounterConfigView(
    UnityEngine::Transform* parent,
    std::string title,
    std::string namespaze,
    std::string klass,
    std::vector<std::shared_ptr<QountersMinus::QounterRegistry::ConfigMetadata>> configMetadata
) {
    auto container = CreateContentView(parent);
    auto titleText = QuestUI::BeatSaberUI::CreateText(container->get_transform(), title);
    titleText->set_alignment(TMPro::TextAlignmentOptions::Center);
    titleText->set_fontSize(6.0f);

    for (auto fieldConfig : configMetadata) {
        UnityEngine::GameObject* gameObject;
        auto label = fieldConfig->displayName == "" ? fieldConfig->field : fieldConfig->displayName;
        auto fieldInfo = il2cpp_utils::FindField(namespaze, klass, fieldConfig->field);
        auto fieldTypeName = std::string(il2cpp_utils::TypeGetSimpleName(fieldInfo->type));
        // nasty hack to access field data inside delegates
        auto csptr = il2cpp_utils::New<System::Reflection::Pointer*>().value();
        csptr->ptr = fieldConfig.get();

        if (fieldTypeName == "bool") {
            auto toggle = QuestUI::BeatSaberUI::CreateToggle(
                container->get_transform(),
                label,
                *(bool*)fieldConfig->ptr,
                il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(classof(UnityEngine::Events::UnityAction_1<bool>*), csptr, HandleBoolSettingChanged)
            );
            gameObject = toggle->get_gameObject();
        } else if (fieldTypeName == "float") {
            auto increment = QuestUI::BeatSaberUI::CreateIncrementSetting(
                container->get_transform(),
                label,
                1,
                fieldConfig->floatStep,
                *(float*)fieldConfig->ptr,
                true,
                true,
                fieldConfig->floatMin,
                fieldConfig->floatMax,
                UnityEngine::Vector2(0.0f, 0.0f),
                il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(classof(UnityEngine::Events::UnityAction_1<float>*), csptr, HandleFloatSettingChanged)
            );
            gameObject = increment->get_gameObject();
        } else if (fieldTypeName == "int") {
            if (fieldConfig->enumNumElements == 0) {
                auto increment = QuestUI::BeatSaberUI::CreateIncrementSetting(
                    container->get_transform(),
                    label,
                    0,
                    static_cast<float>(fieldConfig->intStep),
                    static_cast<float>(*(int*)fieldConfig->ptr),
                    true,
                    true,
                    static_cast<float>(fieldConfig->intMin),
                    static_cast<float>(fieldConfig->intMax),
                    UnityEngine::Vector2(0.0f, 0.0f),
                    il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(classof(UnityEngine::Events::UnityAction_1<float>*), csptr, HandleIntSettingChanged)
                );
                gameObject = increment->get_gameObject();
            } else {
                auto increment = QuestUI::BeatSaberUI::CreateIncrementSetting(
                    container->get_transform(),
                    label,
                    0,
                    1.0f,
                    static_cast<float>(*(int*)fieldConfig->ptr),
                    UnityEngine::Vector2(0.0f, 0.0f),
                    nullptr
                );
                increment->OnValueChange = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(classof(UnityEngine::Events::UnityAction_1<float>*), csptr, HandleEnumSettingChanged);
                fieldConfig->uiElementPtr = increment;
                increment->Text->SetText(il2cpp_utils::createcsstr(fieldConfig->enumDisplayNames[*(int*)fieldConfig->ptr]));
                gameObject = increment->get_gameObject();
            }
        } else if (fieldTypeName == "UnityEngine.Color") {
            gameObject = CreateColorPickerButton(
                container->get_transform(),
                label,
                *(UnityEngine::Color*)fieldConfig->ptr,
                il2cpp_utils::MakeDelegate<ColorChangeDelegate>(classof(ColorChangeDelegate), csptr, HandleColorSettingChanged)
            );
        } else {
            LOG_DEBUG("Cannot create setting UI for unknown type \"" + fieldTypeName + "\"");
        }
        if (fieldConfig->helpText != "" && gameObject != nullptr) {
            QuestUI::BeatSaberUI::AddHoverHint(gameObject, fieldConfig->helpText);
        }
    }

    return container;
}
