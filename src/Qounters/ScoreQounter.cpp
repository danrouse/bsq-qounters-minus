#include "Qounters/ScoreQounter.hpp"

DEFINE_CLASS(QountersMinus::Qounters::ScoreQounter);

bool QountersMinus::Qounters::ScoreQounter::Enabled = true;
int QountersMinus::Qounters::ScoreQounter::Position = static_cast<int>(QountersMinus::QounterPosition::BelowMultiplier);
int QountersMinus::Qounters::ScoreQounter::Distance = 0;
int QountersMinus::Qounters::ScoreQounter::Mode = static_cast<int>(QountersMinus::ScoreQounterMode::Original);
int QountersMinus::Qounters::ScoreQounter::DecimalPrecision = 2;
bool QountersMinus::Qounters::ScoreQounter::DisplayRank = true;
bool QountersMinus::Qounters::ScoreQounter::CustomRankColors = true;
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::SSColor = UnityEngine::Color(0.0f, 1.0f, 1.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::SColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::AColor = UnityEngine::Color(0.0f, 1.0f, 0.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::BColor = UnityEngine::Color(1.0f, 0.92f, 0.016f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::CColor = UnityEngine::Color(1.0f, 0.5f, 0.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::DColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);
UnityEngine::Color QountersMinus::Qounters::ScoreQounter::EColor = UnityEngine::Color(1.0f, 0.0f, 0.0f, 1.0f);

void QountersMinus::Qounters::ScoreQounter::Register() {
    QounterRegistry::Register<ScoreQounter>("Score Qounter", "ScoreConfig");
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &Enabled,
        .field = "Enabled",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &Position,
        .field = "Position",
        .enumNumElements = QounterPositionCount,
        .enumDisplayNames = QounterPositionNames,
        .enumSerializedNames = QounterPositionLookup,
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &Distance,
        .field = "Distance",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &Mode,
        .field = "Mode",
        .enumNumElements = ScoreQounterModeCount,
        .enumDisplayNames = ScoreQounterModeNames,
        .enumSerializedNames = ScoreQounterModeLookup,
        .helpText = "How should this Qounter display data?",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &DecimalPrecision,
        .field = "DecimalPrecision",
        .displayName = "Percentage Precision",
        .helpText = "How precise should the percentage be?",
        .intMin = 0,
        .intMax = 5,
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &CustomRankColors,
        .field = "CustomRankColors",
        .displayName = "Custom Rank Colors",
        .helpText = "Colors your Score Qounter depending on the rank you have in a song.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &SSColor,
        .field = "SSColor",
        .displayName = "SS Color",
        .helpText = "Change the rank color for the SS rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &SColor,
        .field = "SColor",
        .displayName = "S Color",
        .helpText = "Change the rank color for the S rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &AColor,
        .field = "AColor",
        .displayName = "A Color",
        .helpText = "Change the rank color for the A rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &BColor,
        .field = "BColor",
        .displayName = "B Color",
        .helpText = "Change the rank color for the B rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &CColor,
        .field = "CColor",
        .displayName = "C Color",
        .helpText = "Change the rank color for the C rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &DColor,
        .field = "DColor",
        .displayName = "D Color",
        .helpText = "Change the rank color for the D rank.",
    });
    QounterRegistry::RegisterConfig<ScoreQounter>({
        .ptr = &EColor,
        .field = "EColor",
        .displayName = "E Color",
        .helpText = "Change the rank color for the E rank.",
    });
}

QountersMinus::Qounter* QountersMinus::Qounters::ScoreQounter::Initialize() {
    if (!Enabled) return nullptr;
    return QountersMinus::Qounter::Initialize<QountersMinus::Qounters::ScoreQounter*>(
        static_cast<QountersMinus::QounterPosition>(Position), Distance
    );
}

void QountersMinus::Qounters::ScoreQounter::Start() {
    relativeScoreText = refs->coreGameHUDController->relativeScoreGO->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
    relativeScoreText->set_color(UnityEngine::Color::get_white());
    rankText = refs->coreGameHUDController->immediateRankGO->GetComponent<TMPro::TextMeshProUGUI*>();
    rankText->set_color(UnityEngine::Color::get_white());

    auto scoreUIController = refs->coreGameHUDController->GetComponentInChildren<GlobalNamespace::ScoreUIController*>();
    auto scoreUIText = scoreUIController->scoreText;
    scoreUIText->get_transform()->SetParent(gameObject->get_transform(), true);
    refs->coreGameHUDController->relativeScoreGO->get_transform()->SetParent(scoreUIText->get_transform(), true);
    refs->coreGameHUDController->immediateRankGO->get_transform()->SetParent(scoreUIText->get_transform(), true);

    if (!QountersMinus::Qounter::ItalicText) {
        scoreUIText->set_fontStyle(TMPro::FontStyles::Normal);
        relativeScoreText->set_fontStyle(TMPro::FontStyles::Normal);
        rankText->set_fontStyle(TMPro::FontStyles::Normal);
        auto localPosition1 = relativeScoreText->get_rectTransform()->get_localPosition();
        relativeScoreText->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, localPosition1.y, localPosition1.z));
        auto localPosition2 = rankText->get_rectTransform()->get_localPosition();
        rankText->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, localPosition2.y, localPosition2.z));
    }

    if (Mode == static_cast<int>(QountersMinus::ScoreQounterMode::RankOnly))
        UnityEngine::Object::Destroy(refs->coreGameHUDController->relativeScoreGO);
    if (Mode == static_cast<int>(QountersMinus::ScoreQounterMode::ScoreOnly))
        UnityEngine::Object::Destroy(refs->coreGameHUDController->immediateRankGO);

    // instead of calculating original text position based on canvas like counters+,
    // just slap that bad boy right on our unpopulated gameobject
    auto basePosition = gameObject->get_transform()->get_position();
    scoreUIText->get_transform()->set_position(basePosition);

    UnityEngine::Object::Destroy(refs->coreGameHUDController->GetComponentInChildren<GlobalNamespace::ImmediateRankUIPanel*>());

    refs->relativeScoreAndImmediateRankCounter->add_relativeScoreOrImmediateRankDidChangeEvent(il2cpp_utils::MakeDelegate<System::Action*>(
        classof(System::Action*), this, +[](QountersMinus::Qounters::ScoreQounter* self) {
            self->UpdateText();
        }
    ));
    UpdateText();
}

UnityEngine::Color QountersMinus::Qounters::ScoreQounter::GetRankColor(GlobalNamespace::RankModel::Rank rank) {
    switch (rank) {
        case GlobalNamespace::RankModel::Rank::S: return SColor;
        case GlobalNamespace::RankModel::Rank::A: return AColor;
        case GlobalNamespace::RankModel::Rank::B: return BColor;
        case GlobalNamespace::RankModel::Rank::C: return CColor;
        case GlobalNamespace::RankModel::Rank::D: return DColor;
        case GlobalNamespace::RankModel::Rank::E: return EColor;
        default: return SSColor;
    }
}

void QountersMinus::Qounters::ScoreQounter::UpdateText() {
    auto immediateRank = refs->relativeScoreAndImmediateRankCounter->immediateRank;
    if (immediateRank != prevImmediateRank) {
        rankText->set_text(GlobalNamespace::RankModel::GetRankName(immediateRank));
        prevImmediateRank = immediateRank;
        rankText->set_color(CustomRankColors ? GetRankColor(immediateRank) : UnityEngine::Color::get_white());
    }
    float relativeScore = refs->relativeScoreAndImmediateRankCounter->relativeScore * 100.0f;
    relativeScoreText->set_text(il2cpp_utils::createcsstr(FormatNumber(relativeScore, DecimalPrecision) + "%"));
}
