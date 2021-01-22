#include "Qounters/ProgressQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ProgressQounter);

bool QountersMinus::Qounters::ProgressQounter::Enabled = true;
int QountersMinus::Qounters::ProgressQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowEnergy);
int QountersMinus::Qounters::ProgressQounter::Distance = 0;
int QountersMinus::Qounters::ProgressQounter::Mode = static_cast<int>(QountersMinus::ProgressQounterMode::Original);
bool QountersMinus::Qounters::ProgressQounter::ProgressTimeLeft = false;
bool QountersMinus::Qounters::ProgressQounter::IncludeRing = false;

void QountersMinus::Qounters::ProgressQounter::Register() {
    QounterRegistry::Register<ProgressQounter>("Progress", "Progress Qounter", "ProgressConfig", true);
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &Enabled,
        .field = "Enabled",
    });
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &Position,
        .field = "Position",
        .enumNumElements = QounterPositionCount,
        .enumDisplayNames = QounterPositionNames,
        .enumSerializedNames = QounterPositionLookup,
    });
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &Distance,
        .field = "Distance",
    });
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &ProgressTimeLeft,
        .field = "ProgressTimeLeft",
        .displayName = "Show Time Left",
        .helpText = "Starts the counter from the end of the song and decreases while the song is played.",
    });
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &Mode,
        .field = "Mode",
        .enumNumElements = ProgressQounterModeCount,
        .enumDisplayNames = ProgressQounterModeNames,
        .enumSerializedNames = ProgressQounterModeLookup,
        .helpText = "How should this Qounter display data?",
    });
    QounterRegistry::RegisterConfig<ProgressQounter>({
        .ptr = &IncludeRing,
        .field = "IncludeRing",
        .displayName = "Include Progress Ring",
        .helpText = "Whether or not the Progress Ring will also be affected by the \"Show Time Left\" setting. Only active in \"Original\" mode.",
    });
}

QountersMinus::Qounter* QountersMinus::Qounters::ProgressQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::ProgressQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

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

void ConfigureBaseGameObject(UnityEngine::Transform* parent) {
    auto songProgressUIController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::SongProgressUIController*>();
    songProgressUIController->get_gameObject()->SetActive(true);
    songProgressUIController->get_transform()->set_position(parent->get_position());
}

void QountersMinus::Qounters::ProgressQounter::Start() {
    if (Mode == static_cast<int>(QountersMinus::ProgressQounterMode::BaseGame)) return ConfigureBaseGameObject(get_transform());

    CreateBasicText("0");

    audioTimeSyncController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::AudioTimeSyncController*>();
    length = audioTimeSyncController->get_songLength();

    songBPM = il2cpp_utils::RunMethod<float>(refs->difficultyBeatmap->get_level(), "get_beatsPerMinute").value();

    // for compatibility with Intro Skip, avoid actually destroying the original element
    refs->coreGameHUDController->songProgressPanelGO->get_transform()->set_localScale(UnityEngine::Vector3(0.0f, 0.0f, 0.0f));
    // UnityEngine::Object::Destroy(coreGameHUDController->songProgressPanelGO);

    if (Mode != static_cast<int>(QountersMinus::ProgressQounterMode::Percent)) {
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
    if (Mode == static_cast<int>(QountersMinus::ProgressQounterMode::BaseGame)) return;
    auto time = audioTimeSyncController->songTime;
    if (ProgressTimeLeft) time = length - time;
    if (time < 0.0f) return;
    if (
        Mode == static_cast<int>(QountersMinus::ProgressQounterMode::Original) ||
        Mode == static_cast<int>(QountersMinus::ProgressQounterMode::TimeInBeats)
    ) {
        if (Mode == static_cast<int>(QountersMinus::ProgressQounterMode::TimeInBeats)) {
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
        progressRing->set_fillAmount((IncludeRing ? time : audioTimeSyncController->songTime) / length);
        progressRing->SetVerticesDirty();
    } else {
        basicText->set_text(il2cpp_utils::createcsstr(FormatNumber(100.0f * time / length, 2) + "%"));
    }
}
