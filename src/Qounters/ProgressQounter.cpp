#include "Qounters/ProgressQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ProgressQounter);

HMUI::ImageView* CreateRing(UnityEngine::Transform* parent) {
    auto imageGameObject = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("QountersMinusRingImage"));
    imageGameObject->AddComponent<UnityEngine::RectTransform*>();
    imageGameObject->get_transform()->SetParent(parent, false);
    HMUI::ImageView* newImage = imageGameObject->AddComponent<HMUI::ImageView*>();
    static UnityEngine::Material* noGlowMat;
    auto materials = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>();
    for (int i = 0; i < materials->Length(); i++) {
        if (to_utf8(csstrtostr(materials->values[i]->get_name())) == "UINoGlow") {
            noGlowMat = materials->values[i];
            break;
        }
    }
    newImage->set_enabled(false);
    newImage->set_material(noGlowMat);
    static UnityEngine::Sprite* multiplierImageSprite;
    auto sprites = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Sprite*>();
    for (int i = 0; i < sprites->Length(); i++) {
        if (to_utf8(csstrtostr(sprites->values[i]->get_name())) == "Circle") {
            multiplierImageSprite = sprites->values[i];
            break;
        }
    }
    newImage->set_sprite(multiplierImageSprite);
    newImage->set_type(UnityEngine::UI::Image::Type::Filled);
    newImage->set_fillClockwise(true);
    newImage->set_fillOrigin(2);
    newImage->set_fillAmount(1);
    newImage->set_fillMethod(UnityEngine::UI::Image::FillMethod::Radial360);
    newImage->set_enabled(true);
    return newImage;
}

void QountersMinus::Qounters::ProgressQounter::Configure(QountersMinus::ProgressQounterConfig config) {
    mode = (int)config.mode;
    progressTimeLeft = config.progressTimeLeft;
    includeRing = config.includeRing;

    CreateBasicText("0");

    audioTimeSyncController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::AudioTimeSyncController*>();
    length = audioTimeSyncController->get_songLength();

    auto gameplayCoreInstaller = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()->values[0];
    songBPM = gameplayCoreInstaller->sceneSetupData->difficultyBeatmap->get_level()->get_beatsPerMinute();

    auto coreGameHUDController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::CoreGameHUDController*>();
    UnityEngine::Object::Destroy(coreGameHUDController->songProgressPanelGO);

    if (mode != (int)QountersMinus::ProgressQounterMode::Percent) {
        auto backgroundImage = CreateRing(gameObject->get_transform());
        auto anchoredPosition = basicText->get_rectTransform()->get_anchoredPosition();
        backgroundImage->get_rectTransform()->set_anchoredPosition(anchoredPosition);
        backgroundImage->CrossFadeAlpha(0.05f, 1.0f, false);
        auto ringScale = UnityEngine::Vector3(1.0f, 1.0f, 1.0f); // 1.175f?
        backgroundImage->get_transform()->set_localScale(ringScale);
        backgroundImage->set_type(UnityEngine::UI::Image::Type::Simple);

        progressRing = CreateRing(gameObject->get_transform());
        progressRing->get_rectTransform()->set_anchoredPosition(anchoredPosition);
        progressRing->get_transform()->set_localScale(ringScale);
    }
}

void QountersMinus::Qounters::ProgressQounter::Update() {
    auto time = audioTimeSyncController->songTime;
    if (progressTimeLeft) time = length - time;
    if (time < 0.0f) return;
    if (mode == (int)QountersMinus::ProgressQounterMode::Original || mode == (int)QountersMinus::ProgressQounterMode::TimeInBeats) {
        if (mode == (int)QountersMinus::ProgressQounterMode::TimeInBeats) {
            auto beats = std::roundf(songBPM / 60 * time / 0.25f) * 0.25f;
            basicText->set_text(il2cpp_utils::createcsstr(FormatNumber(beats, 2)));
        } else {
            int minutes = std::floor((int)time / 60);
            int seconds = std::floor((int)time % 60);
            basicText->set_text(il2cpp_utils::createcsstr(
                (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                (seconds < 10 ? "0" : "") + std::to_string(seconds)
            ));
        }
        progressRing->set_fillAmount((includeRing ? time : audioTimeSyncController->songTime) / length);
        progressRing->SetVerticesDirty();
    } else {
        basicText->set_text(il2cpp_utils::createcsstr(FormatNumber(100.0f * time / length, 2) + "%"));
    }
}
